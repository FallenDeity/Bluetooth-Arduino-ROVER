#include "Arduino.h"
#include "core/bot.h"
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

const bool JOYSTICK_MODE = true;
Core::Motor left{14, 12};
Core::Motor right{26, 27};
Core::Bot bot{left, right};
BluetoothSerial SerialBT;
static char buffer { 's' };


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


void joystickControl() {
    std::string line = SerialBT.readStringUntil('\n').c_str();
    if (line.empty()) {
        return;
    }
    Core::Control left_{false, 0};
    Core::Control right_{false, 0};
    Serial.println(line.c_str());
    left_.fromPayload(line.substr(0, line.find(',')));
    right_.fromPayload(line.substr(line.find(',') + 1));
    bot.controlMotors(left_, right_);
}


void characterControl() {
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
        bot.diagonal(false, false);
    } else if ('j' == inChar) {
        bot.diagonal(false, true);
    } else {
        bot.stop();
    }
    buffer = inChar;
}


void loop() {
    if (SerialBT.available()) {
        JOYSTICK_MODE ? joystickControl() : characterControl();
    }
}