#ifndef BUTTON_H
#define BUTTON_H

class Button
{
public:
    static bool isPressed();

private:
    static bool getState();
    static constexpr int DEBOUNCE_DELAY_MS = 10;
};

#endif
