/**
 *  Emit MIDI sounds using piezoelectric buzzer and hardware PWM
 *
 * Hardware Identification
 *  WARNING: Data direction register will be set automatically. Change the pins
 *  and timer directly in the class if needed.
 *  TIMER: Timer 0 (OC0A)
 *  OUTPUT: PB2 and PB3, for the minus and plus buzzer pins respectively
 *
 * USAGE:
 *  Sound::intialize();
 *  Sound::playNote(45);
 *  _delay_ms(500);
 *  Sound::stop();
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date March 14th, 2023
 */
#ifndef SOUND_H
#define SOUND_H
#include "io.hpp"
#include <avr/io.h>

class Sound
{
public:
    static void initialize();
    static void playNote(uint8_t midiNote);
    static void start();
    static void stop();

private:
    static constexpr uint16_t PRESCALER_VALUE = 256;

    static uint16_t getFrequency(uint8_t midiNote);

    static io::DataDirectionRegister dataDirectionRegister_;
    static io::Position buzzerMinusPosition_;
    static io::Position buzzerPlusPosition_;
};
#endif
