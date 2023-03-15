#include "Arduino.h"
#include "SoftwareSerial.h"
#include "core/bot.h"

Core::Motor left{2, 3}, right{4, 5};
SoftwareSerial mySerial(0, 1);
Core::Bot bot{left, right};


void setup() {
    Serial.println("Setting up baud rate");
    Serial.begin(9600);
    mySerial.begin(9600);
    Serial.println("Declaring pins");
    left.declarePins();
    right.declarePins();
    Serial.println("Robot is ready");
}


void loop() {
    if (mySerial.available()) {
        char inChar = (char) tolower(mySerial.read());
        Serial.print("I received: ");
        Serial.println(inChar);
        if ((inChar >= '1' && inChar <= '9') || 'q' == inChar) {
            bot.setSpeed((inChar == 'q') ? 100 : int(inChar) * 10);
            Serial.print("Speed set to: ");
            Serial.println(int(inChar));
        }
        switch (inChar) {
            case 'f':
                Serial.println("Moving forward");
                bot.linear(true);
                break;
            case 'b':
                Serial.println("Moving backward");
                bot.linear(false);
                break;
            case 'l':
                Serial.println("Turning left");
                bot.turn(false);
                break;
            case 'r':
                Serial.println("Turning right");
                bot.turn(true);
                break;
            case 'g':
                Serial.println("Moving forward left");
                bot.diagonal(true, false);
                break;
            case 'i':
                Serial.println("Moving forward right");
                bot.diagonal(true, true);
                break;
            case 'h':
                Serial.println("Moving backward left");
                bot.diagonal(false, true);
                break;
            case 'j':
                Serial.println("Moving backward right");
                bot.diagonal(false, false);
                break;
            default:
                bot.stop();
                break;
        }
    }
}