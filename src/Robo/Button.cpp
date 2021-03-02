#include <Arduino.h>
#include <Robo/Button.h>
#include <Helpers.h>

const int PRESSED = LOW;

namespace Robo {
Button::Button(Brain& robo_brain, const int pin) :
  AbstractPart(robo_brain, "Button"),
  m_pin(pin)
{
}

void Button::setup()
{
  pinMode(m_pin, INPUT_PULLUP);
}

const bool Button::is_pressed() const
{
  return digitalRead(m_pin) == PRESSED;
}
}  // namespace Robo
