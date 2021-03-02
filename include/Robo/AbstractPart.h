#ifndef ROBO_ABSTRACTPART_H_
#define ROBO_ABSTRACTPART_H_

#include <Arduino.h>
#include <Robo/Brain.h>
#include <Helpers.h>

namespace Robo {
class AbstractPart
{
public:
  AbstractPart(Brain& robo_brain, const String part_name);
  ~AbstractPart();

  inline const String name() const { return m_part_name; }
  virtual void setup() = 0;

private:
  const String m_part_name;
};
}  // namespace Robo

#endif  // ROBO_ABSTRACTPART_H_
