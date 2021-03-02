#ifndef ROBO_SERVO_H_
#define ROBO_SERVO_H_

#include <Arduino.h>
#include <Helpers.h>
#include <Servo.h>
#include <Robo/AbstractPart.h>

namespace Robo {
class Servo : public AbstractPart
{
  DISABLE_COPY_AND_ASSIGN(Servo)
public:
  static const int ANGLE_GROWS_TO_STAND = 1;
  static const int ANGLE_GROWS_TO_STRAIGHTEN = 1;
  static const int ANGLE_SHRINKS_TO_STAND = -1;
  static const int ANGLE_SHRINKS_TO_STRAIGHTEN = -1;

  Servo(Brain& robo_brain, const int pin, const int flat_angle, const int stand_straighten_modifier);

  void setup() override;

  void flat();
  void base();
  void straight();
  void lift();
private:
  const int m_pin = 0;
  ::Servo m_servo;
  const int m_flat_angle;
  const int m_stand_straighten_modifier;

  void set_angle(const int angle);
};
}  // namespace Robo

#endif  // ROBO_SERVO_H_
