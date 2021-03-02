#include <Robo/Brain.h>
#include <Robo/AbstractPart.h>

namespace Robo
{
AbstractPart::AbstractPart(Brain& robo_brain, const String part_name) :
  m_part_name(part_name)
{
  robo_brain.add_part(*this);
}

AbstractPart::~AbstractPart()
{
}
}  // namespace Robo
