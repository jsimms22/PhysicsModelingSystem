#pragma once

// vendors
// project headers
// std library
#include <bitset>
#include <cstdlib>
#include <fstream>
#include <string_view>

class EventNotifier;

enum class EventType
{
    None,
    WindowClose,
    WindowOpen,
    WindowResize,
    WindowFocus,
    WindowLostFocus,
    WindowMove,
    MousePress,
    MouseRelease,
    MouseScroll,
    MouseMove,
    KeyPress,
    KeyRelease,
    KeyHold,
    AppCycle,
    AppUpdate,
    AppRender,
};

namespace EventCategoryFlag
{
    constexpr std::size_t BitLength = 8;

    constexpr std::bitset<BitLength> None             {0b0000'0001};
    constexpr std::bitset<BitLength> Application      {0b0000'0010};
    constexpr std::bitset<BitLength> Input            {0b0000'0100};
    constexpr std::bitset<BitLength> Keyboard         {0b0000'1000};
    constexpr std::bitset<BitLength> Mouse            {0b0001'0000};
    constexpr std::bitset<BitLength> MouseButton      {0b0010'0000};
    constexpr std::bitset<BitLength> Window           {0b0100'0000};
}

class Event
{
public:
    // Constructor
    Event() = default;

    // Destructor
    virtual ~Event() = default;

    //virtual void OnEvent() = 0;

    //virtual void OnExecute() = 0;

    virtual std::string GetName() const { return {}; };

    virtual EventType GetType() const { return {}; };

    virtual std::bitset<EventCategoryFlag::BitLength> GetCategory() const { return {}; };

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

    friend EventNotifier;
};

inline std::ostream& operator<<(std::ostream& os, const Event& e)
{
    return os << e.ToString();
}