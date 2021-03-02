#include <Robo/Brain.h>
#include <Arduino.h>
#include <Robo/AbstractPart.h>
#include <Helpers.h>

namespace Robo {
class AbstractPartNode
{
public:
  explicit AbstractPartNode(AbstractPart& robo_part) :
    m_robo_part(robo_part),
    m_next_node(NULL)
  {
  }

  inline void set_next_node(AbstractPartNode* next_node) {
    m_next_node = next_node;
  }

  inline AbstractPartNode* get_next_node() {
    return m_next_node;
  }

  inline AbstractPart& get_robo_part() {
    return m_robo_part;
  }

private:
  AbstractPart& m_robo_part;
  AbstractPartNode* m_next_node;
};

Brain::Brain() :
  m_last_part_added_node(NULL)
{
}

void Brain::add_part(AbstractPart& robo_part)
{
  AbstractPartNode* new_part_node = new AbstractPartNode(robo_part);

  if (m_first_part_added_node == NULL) {
    m_first_part_added_node = new_part_node;
    m_last_part_added_node = new_part_node;
  }
  else {
    m_last_part_added_node->set_next_node(new_part_node);
    m_last_part_added_node = new_part_node;
  }
}

void Brain::setup()
{
  AbstractPartNode* current_node = m_first_part_added_node;
  while (current_node != NULL) {
    AbstractPart& robo_part = current_node->get_robo_part();

    Serial.println(String("setting up robo part: ") + robo_part.name());

    robo_part.setup();
    current_node = current_node->get_next_node();
  }
}
}  // namespace Robo
