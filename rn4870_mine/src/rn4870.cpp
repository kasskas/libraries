#include "rn4870.h"
#include "rn4870Model.h"
#include "HardwareSerial.h"
#include "struct_def.h"

void RN4870::begin(char *buffer, int bufferLen, HardwareSerial *_antenna, long baudrate) {
    setStatus(dataMode);
    uartBuffer = buffer;
    uartBufferLen = bufferLen;
    this->antenna = _antenna;
    antenna->begin(baudrate);
	if(connected_rst_pin)
	{
		pinMode(connected_rst_pin, OUTPUT);
		digitalWrite(connected_rst_pin,HIGH);

	}
}

boolean RN4870::startBLE(char userRA[6]) {
	if(!connected_rst_pin){
	enterDataMode(); //ends all the serial input till then (most probably receives Err) and BLE stays in CMD, but empty input line 
	delay(20);
	enterDataMode(); //Exits CMD. Now we are in known state. To fix this, a line to reset should be used. then only driving line low will be enough.
	delay(20);
	enterConfigurationMode(); //Enters config
		delay(20);

	} 
	restart_BLE();	//Restarts the module just in case, also nice when developing. 
    if (enterConfigurationMode() == false) {
        return false;
    }

    if (ble_rn4870.enterDataMode() == false) {
        return false;
    }

    return true;
}


void RN4870::rawConfiguration(String stream) {
    answerLen =0; // reset Answer Counter
    memset(uartBuffer, 0, uartBufferLen);
    stream.concat("\r");
    antenna->print(stream);
}

volatile char  timeout=0;
boolean RN4870::enterConfigurationMode(void) {

    setStatus(enterConfmode);
    antenna->print(CONF_CHAR);
    delay(10);
    antenna->print(CONF_CHAR);
    delay(10);
    antenna->print(CONF_CHAR);
   antenna->flush();
	answerOrTimeout();
	validateAnswer();
	return (status == confMode);
}

boolean RN4870::enterDataMode(void) {

    setStatus(enterDatamode);
    antenna->print(EXIT_CONF);

    return answerOrTimeout();

}

AnswerE RN4870::hasAnswer(void) {
    char data;
    if (antenna->available()) {

        data = antenna->read();
		if((data < 0x20) && (answerLen == 0)){return dataAnswer;}
        uartBuffer[answerLen] = data;
        // when in data mode just collect all the char till the end of the buffer
        if (status != dataMode) {
            // the answer ends with the \n or '>' char
            if (uartBuffer[answerLen] == endStreamChar) {
                return completeAnswer;
            }
        } else {
            return dataAnswer;
        }
        answerLen++;

        // cannot receive more data than the allocated buffer
        if (answerLen > uartBufferLen)
            return partialAnswer;
    }

    // nothing ready at the moment
    return noAnswer;
}


boolean RN4870::factoryReset(void) {
    // if not in configuration mode enter immediately
    if (status != confMode) {
        if (!enterConfigurationMode())
            return false;
    }

    rawConfiguration(FACTORY_RESET);
    return true;
}

boolean RN4870::assignRandomAddress(char userRA[6]){
    if (status == confMode) {
        char timeout=0;
        if(NULL == userRA) {
            rawConfiguration(AUTO_RANDOM_ADDRESS);
        } else {
            //[TODO] - Need to add the user requested Mac
            rawConfiguration(AUTO_RANDOM_ADDRESS);
        }

        if (answerOrTimeout()==true) {
            setAddress(trim((char*)getLastAnswer()));
            return true;
        } else {
            return false;
        }

    } else {
        return false;
    }
}


void RN4870::sendData(char *stream, int streamLen) {
    answerLen =0; // reset Answer Counter
    antenna->write(stream, streamLen);
}


boolean RN4870::setName(char *newName, char nameLen){
    if (status != confMode)
        return false;

    uint8_t ptrData = strlen(SET_NAME);
    memcpy(uartBuffer, SET_NAME, ptrData);
    memcpy(&uartBuffer[ptrData], newName, nameLen);
    rawConfiguration(uartBuffer);	
    return check_recieved();
}

boolean RN4870::check_recieved(){
	answerOrTimeout();
	if(uartBuffer[2] == PROMPT_MIDDLE_AOK)
	{
		return true;
	} else return false;
}
void RN4870::restart_BLE(){
	if(!connected_rst_pin){
	rawConfiguration(RESTART_CONF);}
	else
	{
		digitalWrite(connected_rst_pin, LOW);
		delay(10);
		digitalWrite(connected_rst_pin,HIGH);
	}
	answerOrTimeout();
	//TO DO: Check if module actually restarted(%REBOOT% string)
}
boolean RN4870::clear_Serv_Char(){
	rawConfiguration(CLEAR_ALL_SERV);
	return check_recieved();
}
boolean RN4870::create_service(unsigned long int *UUID_ser){
	uint8_t ptrData = strlen(CREATE_SERV);
	memcpy(uartBuffer, CREATE_SERV, ptrData);
	snprintf(&uartBuffer[ptrData], 9, "%lx",UUID_ser[0]);
	snprintf(&uartBuffer[ptrData+8], 9, "%lx",UUID_ser[1]);
	snprintf(&uartBuffer[ptrData+16], 9, "%lx",UUID_ser[2]);
	snprintf(&uartBuffer[ptrData+24], 9, "%lx",UUID_ser[3]);
	rawConfiguration(uartBuffer);
	return check_recieved();
}
boolean RN4870::create_characteristic(unsigned long int *UUID_ch_root, BLE_char *input_ch){
	
	uint8_t ptrData = strlen(CREATE_CHAR);
	memcpy(uartBuffer, CREATE_CHAR, ptrData);
	snprintf(&uartBuffer[ptrData], 9, "%lx",UUID_ch_root[0]);
	snprintf(&uartBuffer[ptrData+8], 9, "%lx",UUID_ch_root[1]);
	snprintf(&uartBuffer[ptrData+16], 9, "%lx",UUID_ch_root[2]);
	snprintf(&uartBuffer[ptrData+24], 9, "%lx",input_ch->end_UUID);
	snprintf(&uartBuffer[ptrData+32], 2, ",");
	snprintf(&uartBuffer[ptrData+33], 3, "%02x",input_ch->properies);
	snprintf(&uartBuffer[ptrData+35], 2, ",");
	snprintf(&uartBuffer[ptrData+36], 3, "%02x",input_ch->nr_bytes); //for variable width of string, https://stackoverflow.com/questions/5932214/printf-string-variable-length-item
	
	rawConfiguration(uartBuffer);
	
	if(!check_recieved())
	{
		return 0;
	}
	
	handle_id = handle_id + handle_add; //add 3 if notifications are enabled add 2 otherwise 
	input_ch->handle = handle_id;
	
	return 1;
}

boolean RN4870::update_characteristic( BLE_char *input_ch){
	uint8_t ptrData = strlen(WRITE_CHAR);
	memcpy(uartBuffer, WRITE_CHAR, ptrData);
	snprintf(&uartBuffer[ptrData], 5, "%04x",input_ch->handle);
	snprintf(&uartBuffer[ptrData+4], 2, ",");
	if(input_ch->data_to_send_2 > 0){
		sprintf(&uartBuffer[ptrData+5], "%08lx", input_ch->data_to_send_2);
		sprintf(&uartBuffer[ptrData+13], "%08lx", input_ch->data_to_send);
		}
	else 
		sprintf(&uartBuffer[ptrData+5], "%04x", input_ch->data_to_send);
	rawConfiguration(uartBuffer);
	input_ch->data_to_send = 0;
	input_ch->data_to_send_2 = 0;
	return check_recieved();
}

/* -----------------------------------------------------------------------------
 *                      PRIVATE SECTION
 * -----------------------------------------------------------------------------
 */
char* RN4870::trim(char* input) {
    int i,j;
    char* output=input;
    for (i = 0, j = 0; i<strlen(input); i++,j++)
    {
        if (input[i]!=' ')
            output[j]=input[i];
        else
            j--;
    }
    output[j]=0;
    return output;
}


boolean RN4870::validateAnswer(void) {
    switch(status) {
    case enterConfmode:
        if ((uartBuffer[0] == PROMPT_FIRST_CHAR) &&
                (uartBuffer[PROMPT_LEN-1] == PROMPT_LAST_CHAR))
            setStatus(confMode);
			return true;
        break;

    case enterDatamode:
        uartBuffer = trim(uartBuffer);
        if ((uartBuffer[1] == PROMPT_END_FIST_CHAR) &&
                (uartBuffer[strlen(PROMPT_END)-1] == PROMPT_END_LAST_CHAR))
            setStatus(dataMode);
			return true;
        break;

    default:
        // Do nothing remain in the current status
        break;
    }
}

void RN4870::setStatus(RN4870StatusE newStatus) {
    status = newStatus;

    // reset Answer Counter and buffer
	//while(Serial.available()){
	//	Serial.read();
	//	delay(10);
	//	}
	answerLen =0;
    memset(uartBuffer, 0, uartBufferLen);

    switch(status) {
    case enterConfmode:
    case confMode:
        endStreamChar = PROMPT_LAST_CHAR;
        break;

    case enterDatamode:
    case dataMode:
        memset(uartBuffer, 0, uartBufferLen);
        endStreamChar = DATA_LAST_CHAR;
        break;
    }
}

boolean RN4870::answerOrTimeout(void) {
    // wait till there is an Answer or timeout occurred.
	timeout = 0;
	answerLen = 0;
    while ((this->hasAnswer()!=completeAnswer) && (INTERNAL_CMD_TIMEOUT>timeout)){
        delay(DELAY_INTERNAL_CMD);
        timeout++;
    }

    if (INTERNAL_CMD_TIMEOUT>timeout) {
        return true;
    } else {
        return false;
    }
}

void RN4870::setAddress(const char *address){
    //     int i=0,j=0;
    //     char tmp[3]= {0,0,0};
    //     for (j=0; j<6; j++) {
    //         tmp[0] = address[i++];
    //         tmp[1] = address[i++];
    //         if (sscanf(tmp, "%x", &bleAddress[j])) {
    //             SerialUSB.print("OK ");
    //             SerialUSB.print(tmp);
    //         } else {
    //             SerialUSB.print("error ");
    //             SerialUSB.print(tmp);
    //         }
    //
    //     }
    bleAddress[0]=0x59;
    bleAddress[1]=0xe4;
    bleAddress[2]=0x34;
    bleAddress[3]=0xfa;
    bleAddress[4]=0x6b;
    bleAddress[5]=0xcd;
};


void RN4870::getCleanCommandAnswer(char* stream, char* name)
{
    char* cleaned = trim(stream);
    int i,j;
    
    for (i = 0, j = 0; i<strlen(cleaned); i++,j++)
    {
        if (cleaned[i]!=0xd)
            name[j]=cleaned[i];
        else {
        name[j]=0; // null pointer to String
        return;    // exit
        }        
    }
    
}

RN4870 ble_rn4870;
