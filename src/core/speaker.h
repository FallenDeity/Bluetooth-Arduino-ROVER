#ifndef ARDUINO_SPEAKER_H
#define ARDUINO_SPEAKER_H

#include "Arduino.h"


namespace utility {

    class Speaker {
    public:
        uint8_t pin;

        bool state = false;

        explicit Speaker(uint8_t pin);

        void phrase_1() const;

        void phrase_2() const;

        void speak() const;
    };
}

#endif //ARDUINO_SPEAKER_H
