#include "flasher.hpp"

#include <lib/interruptTimer.hpp>
#include <lib/interrupts.hpp>

Led* Flasher::led_ = nullptr;
Led::Color Flasher::first_ = Led::Color::OFF;
Led::Color Flasher::second_ = Led::Color::OFF;

bool Flasher::isActive_ = false;

void Flasher::initialize(Led &led, const uint16_t frequencyHz,
                         const Led::Color &first, const Led::Color &second)
{
    led_ = &led;
    first_ = first;
    second_ = second;

    const double periodS = 1.0 / frequencyHz;
    InterruptTimer::initialize(InterruptTimer::Mode::CLEAR_ON_COMPARE, periodS);
}

void Flasher::initializeAmber(Led &led)
{
    initialize(led, AMBER_FREQUENCY_HZ, Led::Color::RED, Led::Color::GREEN);
}

void Flasher::startFlashing()
{
    InterruptTimer::start();
    interrupts::startCatching();

    isActive_ = true;
}

void Flasher::stopFlashing()
{
    InterruptTimer::stop();
    interrupts::stopCatching();

    isActive_ = false;
    led_->setColor(Led::Color::OFF);
}

void Flasher::handleFlash()
{
    if (isActive_) {
        static volatile bool flashed = false;

        if (flashed) {
            led_->setColor(first_);
        }
        else {
            led_->setColor(second_);
        }

        flashed = !flashed;
    }
}
