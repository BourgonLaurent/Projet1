#ifndef TRANSMIT_RUN_H
#define TRANSMIT_RUN_H

#include <lib/led.hpp>

namespace transmit {
    enum class Mode
    {
        NORMAL,
        DEMO,
    };

    void run(Led &led, const Mode &mode = Mode::NORMAL);

    constexpr uint16_t INITIALIZATION_DELAY_MS = 2000;
    constexpr uint8_t FLASH_FREQUENCY_HZ = 10;
}; // namespace transmit

#endif
