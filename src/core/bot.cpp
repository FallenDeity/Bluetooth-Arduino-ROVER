#include "bot.h"
#include "Arduino.h"


namespace Core {

    void Bot::linear(bool forward) const {
        digitalWrite(leftMotor.pin1, forward);
        digitalWrite(rightMotor.pin1, forward);
        analogWrite(leftMotor.pwm, speed);
        analogWrite(rightMotor.pwm, speed);
    }

    void Bot::turn(bool right) const {
        digitalWrite(leftMotor.pin1, right);
        digitalWrite(rightMotor.pin1, !right);
        analogWrite(leftMotor.pwm, speed);
        analogWrite(rightMotor.pwm, speed);
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
        }
    }

    void Bot::stop() {
        speed = 0;
        analogWrite(leftMotor.pwm, speed);
        analogWrite(rightMotor.pwm, speed);
    }

    void Bot::setSpeed(int percent) {
        speed = (percent * MAX_SPEED) / 100;
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

    Bot::Bot(Motor leftMotor, Motor rightMotor) {
        this->leftMotor = leftMotor;
        this->rightMotor = rightMotor;
    }
}
