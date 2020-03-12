#include <SPI.h>
#include <Wire.h>
#include <U8g2lib.h>
#include "gui.h"
#include "health.h"

GUIManager::GUIManager()
{
    this->log = Logger("GUIManager");
    this->display = U8G2_SSD1306_128X64_NONAME_F_HW_I2C(U8G2_R0, U8X8_PIN_NONE);
}

void GUIManager::init()
{
    this->initDisplay();
}

void GUIManager::loop()
{
    this->loopInput();
    this->loopDraw();
}

void GUIManager::loopInput()
{

}

void GUIManager::loopDraw()
{
    this->display.firstPage();

    switch(this->displayCurrentPage) {
        case GUI_DISPLAY_PAGE_HEALTH:
            this->drawPageHealth();
            break;
        case GUI_DISPLAY_PAGE_NETWORK:
            this->drawPageNetwork();
            break;
        case GUI_DISPLAY_PAGE_PROGRAM:
            this->drawPageProgram();
            break;
    }

    this->drawHeartbeat();
    this->drawNetworkActivity();

    this->display.nextPage();
}

void GUIManager::initDisplay()
{
    this->log.info("Initializing SSD106 display.");
    this->display.begin();
    this->log.info("SSD1306 display is initialized.");
}

void GUIManager::drawPageHealth()
{
    this->drawPageTitle("HEALTH");

    this->display.setDrawColor(1);
    this->display.setFont(u8g2_font_7x13_mf);
    this->display.setFontMode(1);
    this->display.setFontDirection(0);

    this->display.drawStr(17, 10, "[V]: ");
    this->display.drawStr(50, 10, Health.getMainVoltageStr());
    this->display.drawStr(17, 23, "[A]: ");
    this->display.drawStr(50, 23, Health.getMainCurrentStr());
    this->display.drawStr(17, 36, "[W]: ");
    this->display.drawStr(50, 36, Health.getMainPowerStr());
}

void GUIManager::drawPageNetwork()
{
    this->drawPageTitle("NETWORK");
}

void GUIManager::drawPageProgram()
{
     this->drawPageTitle("PROGRAM");
}

void GUIManager::drawPageTitle(const char * title)
{
    this->display.setFont(u8g2_font_9x18B_mr);
    this->display.setFontMode(1);
    this->display.setFontDirection(1);

    this->display.setDrawColor(1);
    this->display.drawBox(0, 0, 14, 64);

    u8g2_uint_t titleWidth = this->display.getStrWidth(title);

    this->display.setDrawColor(2);
    this->display.drawStr(1, 32 - (titleWidth / 2), title);
}

void GUIManager::drawHeartbeat()
{
    this->display.setFont(u8g2_font_open_iconic_human_1x_t);
    this->display.setDrawColor(0);
    this->display.drawBox(118, 0, 10, 10);

    this->display.setDrawColor(1);
    this->display.setFontDirection(0);
    this->display.setFontMode(1);
    
    this->display.drawStr(119, 9, "B");
}

void GUIManager::drawNetworkActivity()
{
    this->display.setFont(u8g2_font_open_iconic_embedded_1x_t);
    this->display.setDrawColor(0);
    this->display.drawBox(118, 10, 10, 10);

    this->display.setDrawColor(1);
    this->display.setFontDirection(0);
    this->display.setFontMode(1);

    this->display.drawStr(119, 19, "P");
}

GUIManager GUI = GUIManager();