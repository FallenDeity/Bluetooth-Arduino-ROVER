#include "Arduino.h"
#include "core/bot.h"
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
Core::Motor left{13, 14};
Core::Motor right{18, 19};
Core::Bot bot{left, right};
static char buffer;


void setup() {
    Serial.println("Setting up baud rate");
    Serial.begin(115200);
    SerialBT.begin("ESPROVER_TECHNOXIAN");
    Serial.println("Robot is ready");
}


char getFirstChar() {
    auto inChar = (char) tolower(SerialBT.read());
    while (SerialBT.available() > 0) {
        SerialBT.read();
    }
    return (inChar == '\n' || inChar == '\r') ? buffer : inChar;
}


void loop() {
    if (SerialBT.available()) {
        char inChar = getFirstChar();
        if ((inChar >= '1' && inChar <= '9') || 'q' == inChar) {
            if ('q' == inChar) {
                bot.setSpeed(100);
            } else {
                bot.setSpeed((inChar - '0') * 10);
            }
        }
        if ('f' == inChar) {
            bot.linear(true);
        } else if ('b' == inChar) {
            bot.linear(false);
        } else if ('l' == inChar) {
            bot.turn(false);
        } else if ('r' == inChar) {
            bot.turn(true);
        } else if ('g' == inChar) {
            bot.diagonal(true, false);
        } else if ('i' == inChar) {
            bot.diagonal(true, true);
        } else if ('h' == inChar) {
            bot.diagonal(false, true);
        } else if ('j' == inChar) {
            bot.diagonal(false, false);
        } else {
            bot.stop();
        }
        buffer = inChar;
    }
}