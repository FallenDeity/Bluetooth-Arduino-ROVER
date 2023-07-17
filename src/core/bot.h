#ifndef ARDUINO_BOT_H
#define ARDUINO_BOT_H

#include "Arduino.h"


namespace Core {

    struct Motor {
        uint8_t pin1;
        uint8_t pin2;
        uint8_t enabler;

        void declarePins() const {
            pinMode(pin1, OUTPUT);
            pinMode(pin2, OUTPUT);
            pinMode(enabler, OUTPUT);
        }
    };

    class Bot {

    public:
        explicit Bot(Motor leftMotor, Motor rightMotor);

        void linear(bool forward) const;

        void turn(bool right) const;

        void diagonal(bool forward, bool right) const;

        void stop() const;

        int speed{0};

        Motor leftMotor;

        Motor rightMotor;
    };
}


#endif //ARDUINO_BOT_H
