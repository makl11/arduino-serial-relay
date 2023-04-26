#include <Arduino.h>

class Relay
{
public:
    Relay(uint8_t pin);
    enum State : uint8_t
    {
        OFF,
        ON
    };

    uint8_t getPin();
    Relay::State getState();

    Relay::State toggle();
    Relay::State on();
    Relay::State off();

private:
    uint8_t _pin;
    Relay::State _state;
};