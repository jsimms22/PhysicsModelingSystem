// vendors
// project headers
#include "../Events/KeyEvents.hpp"
// std library

const std::bitset<EventCategoryFlag::BitLength> KeyEvent::m_category {EventCategoryFlag::Input | 
                                                                      EventCategoryFlag::Keyboard};
