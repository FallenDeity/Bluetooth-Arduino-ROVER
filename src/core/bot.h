#ifndef ARDUINO_BOT_H
#define ARDUINO_BOT_H
#include "Arduino.h"


namespace Core {

    struct Motor {
        int pin1;
        int pwm;

        void declarePins() const {
            pinMode(pin1, OUTPUT);
            pinMode(pwm, OUTPUT);
        }
    };

    class Bot {

    public:
        explicit Bot(Motor leftMotor, Motor rightMotor);
        void linear(bool forward) const;
        void turn(bool right) const;
        void diagonal(bool forward, bool right) const;
        void stop();
        void setSpeed(int percent);
        Motor leftMotor{}, rightMotor{};

    private:
        constexpr static int MAX_SPEED = 255;
        int speed{};
    };
}


#endif //ARDUINO_BOT_H
