// vendors
// project headers
#include "../Events/WindowEvents.hpp"
// std library

const std::bitset<EventCategoryFlag::BitLength> WindowCloseEvent::m_category = {EventCategoryFlag::Input | 
                                                                                EventCategoryFlag::Application | 
                                                                                EventCategoryFlag::Window};

const std::bitset<EventCategoryFlag::BitLength> WindowOpenEvent::m_category = {EventCategoryFlag::Input | 
                                                                               EventCategoryFlag::Application | 
                                                                               EventCategoryFlag::Window};

const std::bitset<EventCategoryFlag::BitLength> WindowResizeEvent::m_category = {EventCategoryFlag::Input | 
                                                                                 EventCategoryFlag::Application | 
                                                                                 EventCategoryFlag::Window};