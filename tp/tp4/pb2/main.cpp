#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <tp2/components/button.hpp>
#include <tp2/components/led.hpp>
#include <tp2/components/colors.hpp>

constexpr uint8_t DEBOUNCE_DELAY_MS = 10;

volatile uint8_t gExpiredTimespan;
volatile uint8_t gButton;

// ISR(TODO modify here)
// {
//     gExpiredTimespan = 1;
// }

// ISR(TODO modify here)
// {
//     gButton = 1;
//     // Anti-bounce
//     TODO implement anti-bounce
// }

// void elapseTimespan(uint16_t duration)
// {
//     gExpiredTimespan = 0;

//     // mode CTC du timer 1 avec horloge divisée par 1024

//     // interruption après la durée spécifiée

//     TCNT1 = 'modifier ici';

//     OCR1A = duree;

//     TCCR1A = 'modifier ici';

//     TCCR1B = 'modifier ici';

//     TCCR1C = 0;

//     TIMSK1 = 'modifier ici';
// }

int main()
{
    return 0;
}