#ifndef TRANSMIT_H
#define TRANSMIT_H

#include <lib/led.hpp>

class Transmit
{
public:
    enum class Mode
    {
        NORMAL,
        DEMO,
    };

    static void run(Led &led, const Mode &mode = Mode::NORMAL);

private:
    static constexpr uint16_t INITIALIZATION_DELAY_MS = 2000;
    static constexpr uint8_t FLASH_FREQUENCY_HZ = 10;
};

#endif
