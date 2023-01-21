#include <colors.hpp>

LED::LED(
    volatile uint8_t *ddr,
    volatile uint8_t *port,
    uint8_t greenPin,
    uint8_t redPin) : port(port),
                      greenPin(greenPin),
                      redPin(redPin)
{
    *ddr |= _BV(greenPin) | _BV(redPin);
};

void LED::setColor(const Color color)
{
    switch (color)
    {
    case Color::OFF:
        *port &= ~(_BV(greenPin) | _BV(redPin));
        break;

    case Color::RED:
        *port |= _BV(redPin);
        *port &= ~_BV(greenPin);
        break;

    case Color::GREEN:
        *port |= _BV(greenPin);
        *port &= ~_BV(redPin);
        break;

    default:
        break;
    }
}