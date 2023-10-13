/**
 * @file app_timer.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-09-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "app_timer.h"
#include "spdlog/spdlog.h"


using namespace MOONCAKE::APPS;


void AppTimer::onCreate()
{
    spdlog::info("{} onCreate", getAppName());

    // Get hal
    _data.hal = mcAppGetDatabase()->Get("HAL")->value<HAL::Hal *>();
}


void AppTimer::onResume()
{
    ANIM_APP_OPEN();

    _data.hal->canvas()->fillScreen(THEME_COLOR_BG);
    _data.hal->canvas()->setFont(FONT_REPL);
    _data.hal->canvas()->setTextColor(TFT_ORANGE, THEME_COLOR_BG);
    _data.hal->canvas()->setTextSize(2);
}

static uint32_t _time_count = 0;

void AppTimer::onRunning()
{
    if ((millis() - _time_count) > 1000)
    {
        _data.hal->canvas()->fillScreen(THEME_COLOR_BG);

        _data.hal->canvas()->setCursor(10, 5);
        _data.hal->canvas()->setTextSize(1);
        _data.hal->canvas()->print("System Time");

        snprintf(_data.string_buffer, sizeof(_data.string_buffer), "%02lld:%02lld:%02lld", millis() / 3600000, millis() / 60000, (millis() / 1000) % 60);
        
        _data.hal->canvas()->setTextSize(2);
        _data.hal->canvas()->drawCenterString(_data.string_buffer, _data.hal->canvas()->width() / 2, _data.hal->canvas()->height() / 2 - 10);

        _data.hal->canvas_update();

        _time_count = millis();
    }

    if (_data.hal->homeButton()->pressed())
    {
        _data.hal->playNextSound();
        spdlog::info("quit timer");
        destroyApp();
    }
}