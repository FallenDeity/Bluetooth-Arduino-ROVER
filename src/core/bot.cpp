#include "bot.h"
#include "Arduino.h"


namespace Core {

    void Bot::linear(bool forward) const {
        digitalWrite(leftMotor.pin1, !forward);
        digitalWrite(rightMotor.pin1, !forward);
        digitalWrite(leftMotor.pin2, forward);
        digitalWrite(rightMotor.pin2, forward);
        analogWrite(leftMotor.enabler, speed);
        analogWrite(rightMotor.enabler, speed);
        Serial.println("Linear: " + String(forward) + " " + String(speed));
    }

    void Bot::turn(bool right) const {
        digitalWrite(leftMotor.pin1, !right);
        digitalWrite(rightMotor.pin1, right);
        digitalWrite(leftMotor.pin2, right);
        digitalWrite(rightMotor.pin2, !right);
        analogWrite(leftMotor.enabler, speed);
        analogWrite(rightMotor.enabler, speed);
        Serial.println("Turn: " + String(right) + " " + String(speed));
    }

    void Bot::diagonal(bool forward, bool right) const {
        digitalWrite(leftMotor.pin1, !forward);
        digitalWrite(rightMotor.pin1, !forward);
        digitalWrite(leftMotor.pin2, forward);
        digitalWrite(rightMotor.pin2, forward);
        if (right) {
            analogWrite(leftMotor.enabler, speed);
            analogWrite(rightMotor.enabler, speed / 2);
        } else {
            analogWrite(leftMotor.enabler, speed / 2);
            analogWrite(rightMotor.enabler, speed);
        }
        Serial.println("Diagonal: " + String(forward) + " " + String(right) + " " + String(speed));
    }

    void Bot::stop() const {
        digitalWrite(leftMotor.pin1, LOW);
        digitalWrite(rightMotor.pin1, LOW);
        digitalWrite(leftMotor.pin2, LOW);
        digitalWrite(rightMotor.pin2, LOW);
    }

    Bot::Bot(Motor leftMotor, Motor rightMotor) : leftMotor(leftMotor), rightMotor(rightMotor) {
        leftMotor.declarePins();
        rightMotor.declarePins();
    }
}
