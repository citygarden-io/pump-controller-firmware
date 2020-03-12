#include <SPI.h>
#include <Wire.h>
#include <U8g2lib.h>
#include "log.h"

enum GUIDisplayPage {
    GUI_DISPLAY_PAGE_HEALTH = 1,
    GUI_DISPLAY_PAGE_NETWORK = 2,
    GUI_DISPLAY_PAGE_PROGRAM = 10,
};

class GUIManager
{
    U8G2 display;
    GUIDisplayPage displayCurrentPage = GUI_DISPLAY_PAGE_HEALTH;
    uint8 heartbeatBPM = 60;
    uint64 heartbeatLastPulseMilis = 0;
    
    Logger log;
public:
    GUIManager();

    void init();
    void loop();

    void setHeartbeatBPM(uint8 bpm);
private:
    void initDisplay();
    
    void loopInput();
    void loopDraw();

    void drawPageHealth();
    void drawPageNetwork();
    void drawPageProgram();
    void drawPageTitle(const char * title);
    void drawHeartbeat();
    void drawNetworkActivity();
};

extern GUIManager GUI;