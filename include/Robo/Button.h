#ifndef ROBO_BUTTON_H_
#define ROBO_BUTTON_H_

#include <Arduino.h>
#include <Robo/AbstractPart.h>

namespace Robo
{
class Button : public AbstractPart
{
  DISABLE_COPY_AND_ASSIGN(Button)
public:
  Button(Brain& robo_brain, const int pin);

  void setup() override;
  const bool is_pressed() const;
private:
  const int m_pin;
};
}  // namespace Robo

#endif  // ROBO_BUTTON_H_
