#include "alerts.hpp"

#include <util/delay.h>

#include <lib/sound.hpp>

namespace alerts {
    namespace parked {
        void play()
        {
            for (uint8_t i = 0; i < N_PARK_SOUNDS; i++) {
                Sound::playNote(PARK_NOTE);
                _delay_ms(PARK_SOUND_PERIOD_MS);
                Sound::stop();
                _delay_ms(PARK_SOUND_PERIOD_MS);
            }
        }
    } // namespace parked

    namespace notFound {
        void play()
        {
            Sound::playNote(END_NOTE);
            _delay_ms(END_SOUND_PERIOD_MS);
            Sound::stop();
        }
    } // namespace notFound
} // namespace alerts
