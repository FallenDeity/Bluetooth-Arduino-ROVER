#include "speaker.h"


namespace utility {

    Speaker::Speaker(uint8_t pin) : pin(pin) {
        pinMode(pin, OUTPUT);
    }

    void Speaker::phrase_1() const {
        long k = random(1000, 2000);
        for (int i = 0; i <= random(100, 2000); i++) {
            tone(pin, static_cast<int>(k + (-i * 2)));
            delay(random(static_cast<long>(.9), 2));
        }
        for (int i = 0; i <= random(100, 1000); i++) {
            tone(pin, static_cast<int>(k + (i * 10)));
            delay(random(static_cast<long>(.9), 2));
        }
    }

    void Speaker::phrase_2() const {
        long k = random(1000, 2000);
        for (int i = 0; i <= random(100, 2000); i++) {
            tone(pin, static_cast<int>(k + (i * 2)));
            delay(random(static_cast<long>(.9), 2));
        }
        for (int i = 0; i <= random(100, 1000); i++) {
            tone(pin, static_cast<int>(k + (-i * 10)));
            delay(random(static_cast<long>(.9), 2));
        }
    }

    void Speaker::speak() const {
        int K = 2000;
        switch (random(1, 7)) {
            case 1:
                phrase_1();
                break;
            case 2:
                phrase_2();
                break;
            case 3:
                phrase_1();
                phrase_2();
                break;
            case 4:
                phrase_1();
                phrase_2();
                phrase_1();
                break;
            case 5:
                phrase_1();
                phrase_2();
                phrase_1();
                phrase_2();
                phrase_1();
                break;
            case 6:
                phrase_2();
                phrase_1();
                phrase_2();
                break;
            default:
                break;
        }
        for (int i = 0; i <= random(3, 9); i++) {
            tone(pin, static_cast<int>(K + random(-1700, 2000)));
            delay(random(70, 170));
            noTone(pin);
            delay(random(0, 30));
        }
        noTone(pin);
    }
}