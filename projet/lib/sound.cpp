/**
 * Emit MIDI notes using piezoelectric buzzer and hardware PWM.
 *
 * LIMITATIONS: Supports only notes from 45 to 81.
 *
 * Hardware Identification
 *  WARNING: Data Direction Register will be set automatically.
 *  TIMER: Timer 2 (OC2A)
 *  OUTPUT: Buzzer, connected plus to PD7 and minus to PD6.
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
 * \date April 4th, 2023
 */

#include "sound.hpp"

#include <math.h>

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

io::DataDirectionRegister Sound::dataDirectionRegister_ = &DDRD;
io::Port buzzerPort = &PORTD;

io::Position Sound::buzzerMinusPosition_ = PD6;
io::Position Sound::buzzerPlusPosition_ = PD7;

void Sound::initialize()
{
    io::setOutput(dataDirectionRegister_, buzzerPlusPosition_);
    io::setOutput(dataDirectionRegister_, buzzerMinusPosition_);

    io::clear(buzzerPort, buzzerMinusPosition_);

    // (p.153) PWM, CTC
    io::clear(&TCCR2A, WGM20);
    io::setActive(&TCCR2A, WGM21);
    io::clear(&TCCR2B, WGM22);

    // (p.154) Prescaler of 256
    io::clear(&TCCR2B, CS20);
    io::setActive(&TCCR2B, CS21);
    io::setActive(&TCCR2B, CS22);
}

void Sound::playNote(uint8_t midiNote)
{
    if (midiNote < MINIMUM_NOTE || midiNote > MAXIMUM_NOTE) {
        return;
    }

    uint16_t frequency = getFrequency(midiNote);

    // (p.143) Get OCR2A value from frequency
    OCR2A = (F_CPU / (2 * uint32_t(frequency) * PRESCALER_VALUE)) - 1;

    start();
}

void Sound::start()
{
    // (p.151) Clear OC2A on set to toggle
    io::setActive(&TCCR2A, COM2A0);
    io::clear(&TCCR2A, COM2A1);
}

void Sound::stop()
{
    // (p.151) Disconnect OC2A
    io::clear(&TCCR2A, COM2A0);
    io::clear(&TCCR2A, COM2A1);
    OCR2A = 0;
}

uint16_t Sound::getFrequency(uint8_t midiNote)
{
    return 440 * pow(2, (double(midiNote) - 69) / 12);
}
