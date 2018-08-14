/*
 * ConfiguratioinExample.ino
 *
 * Example that shows some API used to retrieve the BLE configuration
 * 
 * All the possible commands are visible on the following document wrote by Microchip.
 * User Guide = "http://ww1.microchip.com/downloads/en/DeviceDoc/50002466A.pdf"
 *
 *
 * Author: development@axelelettronica.it
 *
 */
#include <Arduino.h>
#include "rn4870.h"
#define PIN_LED 13
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX

bool ledLigth = false;
char bufferAnswer[100];
char bufferParam[100];
bool sendCmd = true;
char ptrData = 0;

static void ledOn(bool ligthOn) {
#ifdef ARDUINO_SAMD_SMARTEVERYTHING
    ledYellowOneLight(ligthOn);
#else
    pinMode(PIN_LED, OUTPUT);
    digitalWrite(PIN_LED, ligthOn);
#endif
}


void setup() {
    mySerial.begin(9600);

#ifndef ARDUINO_SAMD_SMARTEVERYTHING
    pinMode(PIN_LED, OUTPUT);
#endif

    ble_rn4870.begin(bufferAnswer, sizeof(bufferAnswer));

    delay(100);
    while (!mySerial) {
        ;
    }

    ledOn(ledLigth);
    ledLigth = !ledLigth;

    if (!ble_rn4870.enterConfigurationMode()) {
        mySerial.print("Cannot enter in Configuration mode");
        while(1){};
    }

    mySerial.println("-----------------------------------------");
    mySerial.println("  ---   Configure Your BLE RN4870  ---   ");
    mySerial.println("-----------------------------------------");
    mySerial.println("1) Set BLE Name");
    mySerial.println("2) Set Prompt command <pre>,<post> (default is %,%)");

    /*
    00 921600
    01 460800
    02 230400
    03 115200
    04 57600
    05 38400
    06 28800
    07 19200
    08 14400
    09 9600
    0A 4800
    0B 2400
     */
    mySerial.println("3) Set micro to micro uart baud-rate");
    mySerial.println("4) Set Power Save mode (1=enable; 2=disable)");
    mySerial.println("5) Get Fw, Hw, SW version & Serial Number");
    mySerial.println("6) Get Manufacture");
    mySerial.println("7) Get Name");
    mySerial.println("8) Get uart baud-rate");
    mySerial.println("9) Get Power Save mode");
    mySerial.println("A) Factory Reset !! USE IT CAREFULLY !! ");
    mySerial.println("-----------------------------------------");


}


static boolean composeParam(void) {
    char data;
    if (mySerial.available()) {
        data = mySerial.read();
        if (data != '.'){
            bufferParam[ptrData++] = data;
            return false;
        } else {
            bufferParam[ptrData++] = 0; //end the string
            return true;
        }
    }
    return false;
}


void loop() {
    char data;
    char readData = 0;
    bool paramCompleted = false;
    boolean activated=false;


    if (mySerial.available()) {
        data = mySerial.read();

        switch (data) {
        case '1':
            do {
                paramCompleted = composeParam();
            } while (!paramCompleted);

            // function to set the name          
            if (ble_rn4870.setName(bufferParam, strlen(bufferParam))) {
                mySerial.print("Name ");
                mySerial.print(bufferParam);
                mySerial.println(" changed correctly");
            } else {
                mySerial.println("Error in setName ");
            }
            break;

        case '2':
            break;

        case '3':
            do {
                paramCompleted = composeParam();
            } while (!paramCompleted);

            // function to set the name
            if (ble_rn4870.setBaudRate(bufferParam[0])) {
                mySerial.print("baud-rate set to ");
                mySerial.println(bufferParam);
            } else {
                mySerial.println("Error in baud-rate setting ");
            }
            break;

        case '4':
            do {
                paramCompleted = composeParam();
            } while (!paramCompleted);

            // function to set the name     
            switch (bufferParam[0]) {
            case '0':
                activated = ble_rn4870.setPowerSave(false);
                break;

            case '1':
                activated = ble_rn4870.setPowerSave(true);
                break;

            default:
                mySerial.println("Wrong param ");
                break;
            }     
            if (activated) {                
                mySerial.println("set new Power Save");
            } else {
                mySerial.println("Error in setPowerSave ");
            }
            break;

            case '5':
                if (ble_rn4870.getFwVersion(bufferParam)) {
                    mySerial.print("FW = ");
                    mySerial.println(ble_rn4870.getLastAnswer());
                } else {
                    mySerial.println("Error in getFW ");
                }
                if (ble_rn4870.getHwVersion(bufferParam)) {
                    mySerial.print("Hw = ");
                    mySerial.println(ble_rn4870.getLastAnswer());
                } else {
                    mySerial.println("Error in getHw ");
                }
                if (ble_rn4870.getSwVersion(bufferParam)) {
                    mySerial.print("Sw = ");
                    mySerial.println(ble_rn4870.getLastAnswer());
                } else {
                    mySerial.println("Error in getSw ");
                }
                if (ble_rn4870.getSN(bufferParam)) {
                    mySerial.print("SN = ");
                    mySerial.println(ble_rn4870.getLastAnswer());
                } else {
                    mySerial.println("Error in getSw ");
                }
                break;

            case '6':
                break;

            case '7':
                if (ble_rn4870.getName(bufferParam)) {
                    mySerial.print("Name is ");
                    mySerial.println(bufferParam);
                } else {
                    mySerial.println("Error in getName ");
                }
                break;

            case '8':
                if (ble_rn4870.getBaudRate(bufferParam)) {
                    mySerial.print("baud-rate is ");
                    mySerial.println(ble_rn4870.getLastAnswer());
                } else {
                    mySerial.println("Error in baud-rate ");
                }
                break;

            case '9':
                boolean power;
                if (ble_rn4870.getPowerSave(&power)) {
                    mySerial.print("BLE is ");
                    if (!power)
                        mySerial.print("NOT ");
                    mySerial.println("in Power Save");
                } else {
                    mySerial.println("Error in Power Save");
                }
                break;

            case'A':
                if (ble_rn4870.factoryReset()) {
                    mySerial.print("BLE resetting..... ");
                } else {
                    mySerial.println("Error in factoryReset");
                }
                break;
        }                                
    }

    // collect the Answer from BLE
    if (ble_rn4870.hasAnswer()==completeAnswer) {
        mySerial.write(ble_rn4870.getLastAnswer());

        // clear buffer
        memset(bufferParam, 0, sizeof(bufferParam));
        sendCmd = true;
    }
}

