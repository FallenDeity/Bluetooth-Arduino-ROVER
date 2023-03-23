#include "Arduino.h"
#include "core/bot.h"
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
Core::Motor left{13, 14}, right{18, 19};
Core::Bot bot{left, right};
static char buffer;


void setup() {
    Serial.println("Setting up baud rate");
    Serial.begin(115200);
    SerialBT.begin("ESPROVER");
    Serial.println("Declaring pins");
    left.declarePins();
    right.declarePins();
    Serial.println("Robot is ready");
}


char getFirstChar() {
    char inChar = (char) tolower(SerialBT.read());
    while (SerialBT.available() > 0) {
        SerialBT.read();
    }
    return (inChar != '\n' && inChar != '\r') ? inChar : buffer;
}


void loop() {
    if (SerialBT.available()) {
        char inChar = getFirstChar();
        Serial.print("I received: ");
        Serial.println(inChar);
        if ((inChar >= '1' && inChar <= '9') || 'q' == inChar) {
            if ('q' == inChar) {
                bot.setSpeed(100);
            } else {
                bot.setSpeed((inChar - '0') * 10);
            }
            Serial.print("Setting speed to ");
            Serial.println(bot.speed);
        }
        if ('f' == inChar) {
            Serial.println("Moving forward");
            bot.linear(true);
        } else if ('b' == inChar) {
            Serial.println("Moving backward");
            bot.linear(false);
        } else if ('l' == inChar) {
            Serial.println("Turning left");
            bot.turn(false);
        } else if ('r' == inChar) {
            Serial.println("Turning right");
            bot.turn(true);
        } else if ('g' == inChar) {
            Serial.println("Moving forward left");
            bot.diagonal(true, false);
        } else if ('i' == inChar) {
            Serial.println("Moving forward right");
            bot.diagonal(true, true);
        } else if ('h' == inChar) {
            Serial.println("Moving backward left");
            bot.diagonal(false, true);
        } else if ('j' == inChar) {
            Serial.println("Moving backward right");
            bot.diagonal(false, false);
        } else {
            bot.stop();
        }
        buffer = inChar;
        delay(10);
    }
}