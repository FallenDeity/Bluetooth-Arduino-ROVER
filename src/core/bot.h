#ifndef ARDUINO_BOT_H
#define ARDUINO_BOT_H

#include "Arduino.h"
#include <string>


namespace Core {

    struct Motor {
        int pin1;
        int pwm;

        void declarePins() const {
            pinMode(pin1, OUTPUT);
            pinMode(pwm, OUTPUT);
        }
    };

    struct Control {
        bool reverse;
        int speed;

        void fromPayload(const std::string &data) {
            reverse = data[0] == '-';
            speed = std::stoi(data.substr(1));
        }

    };

    class Bot {

    public:
        explicit Bot(Motor leftMotor, Motor rightMotor);

        void linear(bool forward) const;

        void turn(bool right) const;

        void diagonal(bool forward, bool right) const;

        void controlMotors(Control left, Control right) const;

        void stop();

        void setSpeed(int percent);

        Motor leftMotor{}, rightMotor{};
        int speed{};

    private:
        constexpr static int MAX_SPEED = 255;
    };
}


#endif //ARDUINO_BOT_H
