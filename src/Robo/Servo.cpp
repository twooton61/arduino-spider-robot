#include <Arduino.h>
#include <Robo/Servo.h>
#include <Helpers.h>

namespace Robo {
Servo::Servo(Brain& robo_brain, const int pin, const int flat_angle, const int stand_straighten_modifier) :
  AbstractPart(robo_brain, String("Servo on pin ") + String(pin)),
  m_pin(pin),
  m_flat_angle(flat_angle),
  m_stand_straighten_modifier(stand_straighten_modifier)
{
}

void Servo::setup()
{
  m_servo.attach(m_pin);

  delay(100);
}

void Servo::set_angle(const int angle)
{
  if (m_servo.read() == angle) {
    return;
  }

  Serial.print("writing: ");
  Serial.println(angle);

  m_servo.write(angle);
}

void Servo::flat()
{
  set_angle(m_flat_angle);
}

void Servo::base()
{
  set_angle(m_flat_angle + (m_stand_straighten_modifier * 45));
}

void Servo::straight()
{
  set_angle(m_flat_angle + (m_stand_straighten_modifier * 90));
}

void Servo::lift()
{
  set_angle(m_flat_angle + (m_stand_straighten_modifier * 25));
}

}  // namespace Robo
