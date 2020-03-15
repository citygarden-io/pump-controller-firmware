#include <Arduino.h>
#include "log.h"
#include "network.h"
#include "gui.h"
#include "health.h"
#include "pump.h"
#include "http.h"

ADC_MODE(ADC_VCC);

Logger Log = Logger("System");

void setup() {
    Serial.begin(115200);
    Serial.println();
    
    Log.info("Hello :-)");
    
    Network.init();
    Health.init();
    GUI.init();
    Pump.init();
    HTTP.init();

    Log.info("Initialization complete.");
}

void loop() {
    Network.loop();
    Health.loop();
    GUI.loop();
    Pump.loop();
    HTTP.loop();
}
