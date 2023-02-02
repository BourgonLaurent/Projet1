#define F_CPU 8000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include <tp2/components/colors.hpp>
#include <tp2/components/led.hpp>

#include <tp4/components/interruptButton.hpp>
#include <tp4/components/interruptTimer.hpp>
#include <tp4/components/interrupts.hpp>

constexpr uint8_t TIMER_DURATION_S = 1;
constexpr uint8_t FLASH_DURATION_MS = 100;
constexpr uint16_t WAIT_DURATION_MS = 4000;

volatile bool waitForUser = false;
volatile bool userWon = false;

void InterruptTimer::whenFinished()
{
    if (::waitForUser) {
        ::userWon = false;
        ::waitForUser = false;
    }

    interrupts::clear();
}

void InterruptButton::whenPressed()
{
    if (::waitForUser) {
        ::userWon = true;
    }
}

int main()
{
    LED led = LED(&DDRA, &PORTA, PORTA0, PORTA1);

    InterruptButton::initialize();
    InterruptButton::setMode(InterruptButton::Mode::RISING);

    InterruptTimer::initialize();
    InterruptTimer::setMode(InterruptTimer::Mode::CTC);
    InterruptTimer::setPrescaleMode(InterruptTimer::PrescaleMode::CLK1024);
    InterruptTimer::setSecondsDelay(TIMER_DURATION_S);

    _delay_ms(WAIT_DURATION_MS);

    led.setColor(Color::RED);
    _delay_ms(FLASH_DURATION_MS);
    led.setColor(Color::OFF);

    InterruptTimer::start();
    ::waitForUser = true;

    while (::waitForUser && !::userWon) {
    }

    interrupts::stopCatching();

    led.setColor(::userWon ? Color::GREEN : Color::RED);

    return 0;
}
