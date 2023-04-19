#ifndef ALERTS_H
#define ALERTS_H

#include <stdint.h>
#include <util/delay.h>

#include <lib/sound.hpp>

namespace alerts {
    template <uint8_t NOTE, uint16_t PERIOD_MS, uint8_t N_SOUNDS = 1>
    void alert()
    {
        for (uint8_t i = 0; i < N_SOUNDS; i++) {
            Sound::playNote(NOTE);
            _delay_ms(PERIOD_MS);
            Sound::stop();

            if (N_SOUNDS > 1)
                _delay_ms(PERIOD_MS);
        }
    }

    namespace parked {
        static constexpr uint8_t PARK_NOTE = 78;
        static constexpr uint16_t PARK_SOUND_PERIOD_MS = 300;
        static constexpr uint8_t N_PARK_SOUNDS = 3;

        auto play = alert<PARK_NOTE, PARK_SOUND_PERIOD_MS, N_PARK_SOUNDS>;
    } // namespace parked

    namespace notFound {
        static constexpr uint16_t END_NOTE = 45;
        static constexpr uint16_t END_SOUND_PERIOD_MS = 2000;

        auto play = alert<END_NOTE, END_SOUND_PERIOD_MS>;
    } // namespace notFound
} // namespace alerts

#endif
