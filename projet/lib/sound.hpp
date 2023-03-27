/**
 * Emit MIDI notes using piezoelectric buzzer and hardware PWM.
 *
 * LIMITATIONS: Supports only notes from 45 to 81.
 *
 * Hardware Identification
 *  WARNING: Data Direction Register will be set automatically.
 *  TIMER: Timer 0 (OC0A)
 *  OUTPUT: Buzzer, connected plus to PB3 and minus to PB2.
 *
 * USAGE:
 *  Sound::intialize();
 *  Sound::playNote(45);
 *  _delay_ms(500);
 *  Sound::stop();
 *  _delay_ms(500);
 *  Sound::start();
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date March 14, 2023
 */

#ifndef SOUND_H
#define SOUND_H

#include <avr/io.h>

#include <lib/io.hpp>

class Sound
{
public:
    static void initialize();

    static void start();
    static void stop();

    static void playNote(uint8_t midiNote);

private:
    static constexpr uint16_t PRESCALER_VALUE = 256;
    static constexpr uint8_t MINIMUM_NOTE = 45;
    static constexpr uint8_t MAXIMUM_NOTE = 81;

    static uint16_t getFrequency(uint8_t midiNote);

    static io::DataDirectionRegister dataDirectionRegister_;
    static io::Position buzzerMinusPosition_;
    static io::Position buzzerPlusPosition_;
};

#endif
