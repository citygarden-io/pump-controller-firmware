#include <Arduino.h>
#include <log.h>
#include <network.h>

void setup() {
    Serial.begin(115200);
    Serial.println();

    Log.info("Hello :-)");
    
    Network.init();
    // TODO: Power.init();
    // TODO: GUI.init();
}

void loop() {
    Network.loop();
    // TODO: Power.loop();
    // TODO: GUI.loop();
}
