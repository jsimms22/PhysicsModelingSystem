#pragma once

// vendors
// project headers
#include "../Events/EventTypes.hpp"
// std library
#include <string_view>
#include <fstream>

class Event
{
public:
    // Constructor
    Event() = default;

    // Destructor
    virtual ~Event() = default;

    //virtual void OnEvent() = 0;

    //virtual void OnExecute() = 0;

    virtual const char* GetName() const = 0;

    virtual EventType GetType() const = 0;

    virtual std::bitset<EventCategoryFlag::BitLength> GetCategory() const = 0;

    virtual std::string_view ToString() const 
    { 
        return GetName(); 
    }

    bool IsInCategory(const std::bitset<EventCategoryFlag::BitLength> category) const 
    { 
        return (GetCategory() & category).any();
    }

private: // members
    bool m_handled = false;
};

inline std::ostream& operator<<(std::ostream& os, const Event& e)
{
    return os << e.ToString();
}