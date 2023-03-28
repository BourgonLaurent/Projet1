/**
 * Control of a infrared sensor.
 *
 * Hardware Identification:
 *  WARNING: Pin must be in port A
 *  OUTPUT:
 *
 * USAGE:
 *  Led led = Led(&DDRA, &PORTA, PA0, PA1);
 *  led.setColor(Led::Color::RED);
 *  led.setAmberForMs(10);
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date March 26, 2023
 */

#include "irSensor.hpp"

#include <util/delay.h>

#include <lib1900/communication.hpp>
#include <lib1900/led.hpp>
#include <lib1900/interruptTimer.hpp>
#include <lib1900/io.hpp>
#include <lib1900/wheels.hpp>

IrSensor::IrSensor(const io::Position pin) : pin_(pin)
{
    io::setInput(&DDRA, IrSensor::pin_);
};

uint16_t IrSensor::read()
{

    uint16_t sumForAverage = 0;
    uint8_t temporaryMaximum = 0;
    for (uint8_t i = 0; i < IrSensor::N_MEASURMENTS_; i++) {
        const uint8_t value = IrSensor::reader_.read(IrSensor::pin_);
        if (value > temporaryMaximum) {
            sumForAverage = sumForAverage + temporaryMaximum;
            temporaryMaximum = value;
        }
        else {
            sumForAverage = sumForAverage + value;
        }
        _delay_ms(5);
    }
    sumForAverage = sumForAverage / (IrSensor::N_MEASURMENTS_ - 1);
    return sumForAverage;
}

bool IrSensor::detect()
{
    uint16_t value = read();

    if (value < 130 && value > 12) {
        return true;
    }
    return false;
}

bool IrSensor::detectDistanceToPark(uint8_t distance1, uint8_t distance2)
{

    uint16_t value = read();

    if (value < distance1 && value > distance2) {
        return true;
    }
    return false;
}
void IrSensor::park()
{
    while (!detectDistanceToPark(110, 85)) {
        Wheels::setDirection(Wheels::Direction::FORWARD);
        Wheels::setSpeed(50);
        _delay_ms(500);
        Wheels::turnOff();
        _delay_ms(100);
        if (!detect()) {
            find();
        }
    }
    Wheels::turnOff();
}

void IrSensor::goToObject(uint8_t distanceObject)
{
    detectRange(distanceObject);
    park();
    switch (IrSensor::range_) {
        case Range::DIAGONAL_FAR :
            _delay_ms(3000);
            Wheels::turn(Wheels::Side::RIGHT);
            while (!detect()) {
                continue;
            }
            Wheels::stopTurn(Wheels::Side::RIGHT);
            park();
            break;

        case Range::STRAIGHT_ANGLE_CLOSE :
        case Range::DIAGONAL_CLOSE :
        case Range::STARIGHT_ANGLE_FAR :
            park();
            break;
    }
}

void IrSensor::detectRange(uint8_t distance)
{
    if (distance < 15 && distance > 12) {
        IrSensor::range_ = IrSensor::Range::DIAGONAL_FAR;
    }

    if (distance < 50 && distance > 44) {
        IrSensor::range_ = IrSensor::Range::DIAGONAL_CLOSE;
    }
}

void IrSensor::find()
{
    InterruptTimer::initialize(InterruptTimer::Mode::NORMAL, 4.0);
    Wheels::initialize();
    Led led = Led(&DDRB, &PORTB, PB0, PB1);

    Wheels::turn(Wheels::Side::RIGHT);
    interrupts::startCatching();
    InterruptTimer::start();

    while (!detect()) 
    {
        led.setColor(Led::Color::GREEN);
    }

    InterruptTimer::stop();
    Wheels::stopTurn(Wheels::Side::RIGHT);
    led.setColor(Led::Color::RED);
}