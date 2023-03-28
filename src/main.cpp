#include "Arduino.h"
#include <string>
#include "core/bot.h"
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
Core::Motor left{13, 14}, right{18, 19};
Core::Bot bot{left, right};


void setup() {
    Serial.println("Setting up baud rate");
    Serial.begin(115200);
    SerialBT.begin("ESPROVER_TECHNOXIAN");
    Serial.println("Declaring pins");
    left.declarePins();
    right.declarePins();
    Serial.println("Robot is ready");
}


void loop() {
    if (SerialBT.available()) {
        std::string line = SerialBT.readStringUntil('\n').c_str();
        if (line.empty()) {
            return;
        }
        Core::Control left_ { false, 0 }, right_ { false, 0 };
        Serial.println(line.c_str());
        left_.fromPayload(line.substr(0, line.find(',')));
        right_.fromPayload(line.substr(line.find(',') + 1));
        bot.controlMotors(left_, right_);
    }
    delay(100);
}