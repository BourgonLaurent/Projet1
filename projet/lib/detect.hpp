/**
 * Detect program of the project
 *
 * HARDWARE:
 * IR sensor to PA0
 * Led to PB0(+) and PB1(-) // à vérifier
 * InterruptButton to PD2
 * White Button to PC2
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date April 17, 2023
 */
#include <avr/io.h>
#include <util/delay.h>

#include <lib/button.hpp>
#include <lib/debug.hpp>
#include <lib/interruptButton.hpp>
#include <lib/interruptTimer.hpp>
#include <lib/interrupts.hpp>
#include <lib/led.hpp>
#include <lib/objectFinder.hpp>
#include <lib/sound.hpp>
#include <lib/wheels.hpp>

#include <app/misc/map/mapManager.hpp>

namespace detect {
    enum class States
    {
        SET_DIRECTION,
        RIGHT,
        FROM_RIGH_UP,
        UP,
        FIND_OBJECT,
        FOUND_NOTHING,
        FOUND_OBJECT,
        WAIT_NEXT_DETECTION

    };

    volatile States state = States::SET_DIRECTION;
    volatile bool timeOut = false;
    Led led = Led(&DDRB, &PORTB, PB0, PB1);
    Button whiteButton(&DDRC, &PINC, PC2);
    Button interruptButton(&DDRD, &PIND, PD2);
    Map map;
    IrSensor irSensor(constants::SENSOR);
    ObjectFinder finder(led, irSensor, &map);

    void initialize();
    void checkTimerValue();
    int run();

}; 