#ifndef ARDUINO_BOT_H
#define ARDUINO_BOT_H

#include "Arduino.h"
#include <string>


namespace Core {

    struct Motor {
        uint8_t pin1;
        uint8_t pwm;

        void declarePins() const {
            pinMode(pin1, OUTPUT);
            pinMode(pwm, OUTPUT);
        }
    };

    struct Control {
        bool reverse;
        uint8_t speed;

        void fromPayload(const std::string &data) {
            reverse = data[0] == '-';
            speed = (uint8_t) abs(std::stoi(data));
            Serial.print("Reverse: ");
            Serial.print(reverse);
            Serial.print(" Speed: ");
            Serial.println(speed);
        }

    };

    class Bot {

    public:
        explicit Bot(Motor leftMotor, Motor rightMotor);

        void linear(bool forward) const;

        void turn(bool right) const;

        void diagonal(bool forward, bool right) const;

        void controlMotors(Control left, Control right) const;

        void stop() const;

        void setSpeed(int percent);

        int speed{255};

        Motor leftMotor;

        Motor rightMotor;

    private:
        constexpr static int MAX_SPEED = 255;
    };
}


#endif //ARDUINO_BOT_H
