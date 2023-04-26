#include <Arduino.h>
#include <relay.h>

#define RELAY_PIN 7
#define LED_PIN 13

Relay *relay;

void setup()
{
  relay = new Relay(RELAY_PIN);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.read(); // skip first byte
}

enum Command
{
  OFF,
  ON,
  TOGGLE,
  GET_STATE,
  UNSET = -1
};

Command command = UNSET;

void setState(Relay::State newState)
{
  digitalWrite(LED_PIN, newState);
  Serial.write((uint8_t)newState);
}

void loop()
{
  command = UNSET;
  delay(100);

  if (Serial.available())
    command = Command(Serial.read());

  if (command == UNSET)
    return;

  switch (command)
  {
  case GET_STATE:
    return setState(relay->getState());
  case TOGGLE:
    return setState(relay->toggle());
  case ON:
    return setState(relay->on());
  case OFF:
    return setState(relay->off());
  default:
    Serial.write(7);
  }
}