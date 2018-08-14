#ifndef RN4870_H
#define RN4870_H
#define connected_rst_pin 4 //in case RST pin of RN4870 is connected to MCU, define the Digital pin, else use -1
//#define NOTIFICATIONS_ON //comment out if no notificatios are used 
#ifdef NOTIFICATIONS_ON
	#define handle_start  0x006f
	#define handle_add  3
	#else
		#define handle_start  0x0070
		#define handle_add  2
#endif

#include <Arduino.h>
#include "rn4870Model.h"
#include "HardwareSerial.h"
#include "struct_def.h"
#include <SoftwareSerial.h>

class RN4870 {

	
private:
    HardwareSerial *antenna;
    uint16_t answerLen;
	uint16_t handle_id = handle_start; //first handle id given by BLE. Next one is increment by 3 (0072 0075 etc) with notifications enabled 
							//otherwise use 0x0070 and add 2  
	
private:
    boolean checkAnswer(const char *answer);
    
    int uartBufferLen;
   // volatile RN4870StatusE status;
    char endStreamChar;
    char bleAddress[6];

public:


volatile RN4870StatusE status;
char *uartBuffer;

    RN4870(){status=dataMode;};

    void begin(char *buffer, int bufferLen,HardwareSerial *antenna, long baudrate=115200);


    /*
     * The function set the address and move in data mode
     */
    boolean startBLE(char userRA[6]=NULL);

    /* 
     * Send a specific string of configuration
     */
    void rawConfiguration(String stream);

    /*
     * Send a streamLen of bytes over the air
     */
    void sendData(char *stream, int streamLen);

    /* 
     * function to enter in the BLE chip configuration
     */
    boolean enterConfigurationMode(void);

    /*
     * function to enter in the BLE data communication
     */
    boolean enterDataMode(void);

    AnswerE hasAnswer(void);

    /* 
     * Assign the internal buffer used for the answer of configuration command
     *  or for the received message
     */
    inline void setAnswerBuffer(char *buffer, int bufferLen){
        uartBuffer = buffer;
        uartBufferLen = bufferLen;
    }

    /*
     * generates and assigns a random address to the local device.
     * It accepts one input parameter which is a 6-byte random address.
     * This random address can be a static or a private address.
     *
     *  When the use does not assign a specific address it will be automatically
     *  found by the BLE, otherwise the user address will be assign.
     */
    boolean assignRandomAddress(char userRA[6]=NULL);

    /* 
     * Return the latest receive message from the configuration command or 
     *      from the air
     */
    inline const char* getLastAnswer(void) {return uartBuffer;};

    /*
     * This command resets the configurations into factory default.
     * 
     * The function works either in configuration or in data mode.
     */
    boolean factoryReset(void);

    /*
     * The function return the address used by the BLE 
     *
     */
    inline char* getAddress(void){return bleAddress;};

    /*
     * Set a new name
     *
     * The function works in configuration mode.
     */
    boolean setName(char *newName, char nameLen);

    /*
     * retrieve the configured name
     *
     * The function works in configuration mode.
     *
     */
	/*Checks for AOK*/
	boolean check_recieved();
	
	void restart_BLE(); //Restart the module
	
	boolean clear_Serv_Char(); //Command PZ clears all settings of services and characteristics. A reboot or power
	//cycle is required afterwards to make the changes effective. Roboot is NOT DONE AFTER THIS COMMAND. 
	
	boolean create_service(unsigned long int *UUID_ser); //Creates service with given UUID
	
	boolean create_characteristic(unsigned long int *UUID_ch_root, BLE_char *input_ch); //Creates characteristics with given UUID, with given bitmap and length in Octets (two char)
	
	boolean update_characteristic( BLE_char *input_ch); //updates given characteristic. Uses data already in the structure
	
    boolean getName(char *name);

    /*
     * Set the internal baud rate
     *
     * 00 921600
     * 01 460800
     * 02 230400
     * 03 115200
     * 04 57600
     * 05 38400
     * 06 28800
     * 07 19200
     * 08 14400
     * 09 9600
     * 0A 4800
     * 0B 2400
     *
     * The function works in configuration mode.
     */
    boolean setBaudRate(char bufferParam);

    /*
     * get the internal baud-rate
     *
     * The function works in configuration mode.
     */
    boolean getBaudRate(char *bufferParam);


    /*
     * get the FW version of the BLE
     *
     * The function works in configuration mode.
     */
    boolean getFwVersion(char *bufferParam);

    /*
     * get the SW version of the BLE
     *
     * The function works in configuration mode.
     */
    boolean getSwVersion(char *bufferParam);

    /*
     * get the HW version of the BLE
     *
     * The function works in configuration mode.
     */
    boolean getHwVersion(char *bufferParam);

    /*
     * get the Serial Number of the BLE
     *
     * The function works in configuration mode.
     */
    boolean getSN(char *bufferParam);


    /*
     * true  = Enables  low-power operation.
     *         RN4870 runs 32 kHz clock with much lower 
     *         power consumption.
     *
     * false = disables low-power operation.
     *         RN4870/71 runs 16 MHz clock all the time, 
     *         therefore, can operate UART all the time.     
     *
     *  When RN4870 runs on 32 kHz clock, UART is not operational.
     *  RN4870/71 restarts 16 MHz clock by pulling UART_RX_IND pin low. 
     *
     *  When UART_RX_IND pin is high, RN4870/71 runs 32 kHz clock.      
     *  When RN4870/71 runs on 32 kHz clock, a BLE connection can 
     *      still be maintained, but UART cannot receive data. 
     *  
     *  If the user sends input data to the UART, UART_RX_IND pin 
     *      must be pulled low to start 16MHz clock, 
     *      then wait for 5 ms before UART can be operated.
     *
     *
     *   The function works either in configuration or in data mode.
     */
    boolean setPowerSave(boolean powerSave);

    /*
     * get the internal baud-rate
     *
     * The function works in configuration mode.
     */
    boolean getPowerSave(boolean *powerSave);

private:
    boolean validateAnswer(void);
    void setStatus(RN4870StatusE newStatus);
    char* trim(char* input);
    boolean answerOrTimeout(void);
    void setAddress(const char *address);
    void getCleanCommandAnswer(char* stream, char* name);
};

// external variable used by the sketches
extern RN4870  ble_rn4870;
#endif
