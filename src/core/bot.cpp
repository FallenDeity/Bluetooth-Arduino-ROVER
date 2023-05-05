#include "bot.h"
#include "Arduino.h"


namespace Core {

    void Bot::linear(bool forward) const {
        digitalWrite(leftMotor.pin1, forward);
        digitalWrite(rightMotor.pin1, forward);
        analogWrite(leftMotor.pwm, speed);
        analogWrite(rightMotor.pwm, speed);
        Serial.printf("Moving %s with speed %d\n", forward ? "forward" : "backward", speed);
    }

    void Bot::turn(bool right) const {
        digitalWrite(leftMotor.pin1, right);
        digitalWrite(rightMotor.pin1, !right);
        analogWrite(leftMotor.pwm, speed);
        analogWrite(rightMotor.pwm, speed);
        Serial.printf("Turning %s with speed %d\n", right ? "right" : "left", speed);
    }

    void Bot::diagonal(bool forward, bool right) const {
        if (forward) {
            digitalWrite(leftMotor.pin1, forward);
            digitalWrite(rightMotor.pin1, forward);
            if (right) {
                analogWrite(leftMotor.pwm, speed);
                analogWrite(rightMotor.pwm, speed / 2);
            } else {
                analogWrite(leftMotor.pwm, speed / 2);
                analogWrite(rightMotor.pwm, speed);
            }
            Serial.printf("Moving %s with speed %d\n", right ? "forward-right" : "forward-left", speed);
        } else {
            digitalWrite(leftMotor.pin1, forward);
            digitalWrite(rightMotor.pin1, forward);
            if (right) {
                analogWrite(leftMotor.pwm, speed / 2);
                analogWrite(rightMotor.pwm, speed);
            } else {
                analogWrite(leftMotor.pwm, speed);
                analogWrite(rightMotor.pwm, speed / 2);
            }
            Serial.printf("Moving %s with speed %d\n", right ? "backward-left" : "backward-right", speed);
        }
    }

    void Bot::stop() const {
        analogWrite(leftMotor.pwm, 0);
        analogWrite(rightMotor.pwm, 0);
    }

    void Bot::setSpeed(int percent) {
        speed = (percent * MAX_SPEED) / 100;
        Serial.printf("Speed set to %d\n", speed);
    }

    void Bot::controlMotors(Control left, Control right) {
        leftMotor.pwm = left.speed;
        rightMotor.pwm = right.speed;
        rightMotor.pin1 = right.reverse;
        leftMotor.pin1 = left.reverse;
        digitalWrite(leftMotor.pin1, left.reverse);
        digitalWrite(rightMotor.pin1, right.reverse);
        analogWrite(leftMotor.pwm, left.speed);
        analogWrite(rightMotor.pwm, right.speed);
    }

    Bot::Bot(Motor leftMotor, Motor rightMotor) : leftMotor(leftMotor), rightMotor(rightMotor) {
        leftMotor.declarePins();
        rightMotor.declarePins();
    }
}
