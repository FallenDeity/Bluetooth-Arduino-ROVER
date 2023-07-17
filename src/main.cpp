#include "Arduino.h"
#include "core/bot.h"
#include "core/speaker.h"
#include "SoftwareSerial.h"

utility::Speaker speaker{3};
Core::Motor left{7, 12, 9};
Core::Motor right{8, 4, 6};
Core::Bot bot{left, right};
SoftwareSerial SerialBT(10, 11);
static char buffer { 's' };


void setup() {
    Serial.println("Setting up baud rate");
    Serial.begin(115200);
    SerialBT.begin(9600);
    Serial.println("Setting up speaker");
    randomSeed(analogRead(0));
    Serial.println("Robot is ready");
    speaker.speak();
}


char getFirstChar() {
    auto inChar = (char) tolower(SerialBT.read());
    while (SerialBT.available() > 0) {
        SerialBT.read();
    }
    return (inChar == '\n' || inChar == '\r') ? buffer : inChar;
}


void characterControl() {
    char inChar = getFirstChar();
    if ((inChar >= '1' && inChar <= '9') || 'q' == inChar) {
        if ('q' == inChar) {
            bot.speed = 255;
        }
        else {
            bot.speed = (inChar - '0') * 10 * 255 / 100;
        }
        Serial.println("Speed: " + String(bot.speed));
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
    } else if ('v' == inChar) {
        speaker.state = !speaker.state;
        if (speaker.state) {
            speaker.speak();
        }
    } else {
        bot.stop();
    }
    buffer = inChar;
}


void loop() {
    if (SerialBT.available()) {
        characterControl();
    }
}