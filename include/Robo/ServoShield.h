#ifndef ROBO_SERVOSHIELD_H_
#define ROBO_SERVOSHIELD_H_

#include <Arduino.h>
#include <Helpers.h>
#include <Robo/AbstractPart.h>
#include <Adafruit_PWMServoDriver.h>

namespace Robo {
class ServoShield : public AbstractPart
{
  DISABLE_COPY_AND_ASSIGN(ServoShield)
public:
  explicit ServoShield(Brain& robo_brain, Adafruit_PWMServoDriver& servo_driver);

  void setup() override;
  void go();

private:
  Adafruit_PWMServoDriver& m_servo_driver;
  uint8_t m_twbrbackup;
};
}  // namespace Robo

#endif  // ROBO_SERVOSHIELD_H_
