// vendors
// project headers
#include "MouseEvents.hpp"
// std library


const std::bitset<EventCategoryFlag::BitLength> MousePressEvent::m_category = {EventCategoryFlag::Input | 
                                                                               EventCategoryFlag::Mouse |
                                                                               EventCategoryFlag::MouseButton};

                                                                               
const std::bitset<EventCategoryFlag::BitLength> MouseReleaseEvent::m_category = {EventCategoryFlag::Input | 
                                                                                 EventCategoryFlag::Mouse |
                                                                                 EventCategoryFlag::MouseButton};

const std::bitset<EventCategoryFlag::BitLength> MouseScrollEvent::m_category = {EventCategoryFlag::Input | 
                                                                                EventCategoryFlag::Mouse};

                                                                                
const std::bitset<EventCategoryFlag::BitLength> MouseMoveEvent::m_category = {EventCategoryFlag::Input | 
                                                                              EventCategoryFlag::Mouse};