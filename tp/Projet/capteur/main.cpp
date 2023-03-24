/**
 * Read infra red sensor values.
 *
 * Hardware Identification
 * OUTPUT:
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date March 16, 2023
 */

#include <avr/io.h>
#include <util/delay.h>
#include <lib1900/analogReader.hpp>
#include <lib1900/communication.hpp>
#include <lib1900/led.hpp>

constexpr io::Position SENSOR = PA6;

int main()
{
    Communication::initialize();
    io::setInput(&DDRA, SENSOR);
    AnalogReader reader;


    const uint8_t N_MEASURMENTS = 6;
    

    Led led = Led(&DDRB, &PORTB, PB0, PB1);

    while (true) 
    {
        uint16_t sumForAverage = 0;
        uint8_t temporaryMaximum = 0;
        for (uint8_t i = 0 ; i< N_MEASURMENTS; i++)
        {
            const uint8_t value = reader.read(SENSOR);
            Communication::send(value);
            Communication::send(" ");
            if (value > temporaryMaximum)
            {
                sumForAverage = sumForAverage + temporaryMaximum;
                temporaryMaximum = value;
            }
            else 
            {
                sumForAverage = sumForAverage + value;
            }
            _delay_ms(5);
            
        }
        sumForAverage = sumForAverage/ (N_MEASURMENTS-1);
        if (sumForAverage < 130 && sumForAverage > 33 )
        {
            led.setColor(Led::Color::RED);
        }
        else
        {
            led.setColor(Led::Color::GREEN);
        }
    }
}