#ifndef TRANSMIT_RUN_H
#define TRANSMIT_RUN_H

#include <lib/led.hpp>

namespace transmit {
    namespace {
        constexpr uint16_t INITIALIZATION_DELAY_MS = 2000;
        constexpr uint8_t FLASH_FREQUENCY_HZ = 10;
    } // namespace

    void run(Led &led);
}; // namespace transmit

#endif
