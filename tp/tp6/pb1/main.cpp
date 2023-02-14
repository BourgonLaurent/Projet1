
#define F_CPU 8000000UL;
#include <tp2/components/button.hpp>
#include <tp2/components/io.hpp>
#include <tp2/components/led.hpp>

int main()
{
    Button button = Button(&DDRD, &PIND, DDD2);
    LED led = LED(&DDRB, &PORTB, DDD1, DDD0);

    return 0;
}