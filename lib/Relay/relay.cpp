#include <Arduino.h>
#include "relay.h"

Relay::Relay(uint8_t pin)
{
    _pin = pin;
    pinMode(_pin, OUTPUT);
    off();
}

uint8_t Relay::getPin()
{
    return _pin;
}

Relay::State Relay::getState()
{
    int gpioState = (digitalRead(_pin));
    if (gpioState != _state)
        _state = Relay::State(gpioState);

    return _state;
}

Relay::State Relay::toggle()
{
    switch (_state)
    {
    case State::OFF:
        on();
        break;
    case State::ON:
    default: // Fall back to OFF in case of unknown states
        off();
    }
    return _state;
}

Relay::State Relay::on()
{
    digitalWrite(_pin, State::ON);
    _state = State::ON;
    return _state;
}

Relay::State Relay::off()
{
    digitalWrite(_pin, State::OFF);
    _state = State::OFF;
    return _state;
}
