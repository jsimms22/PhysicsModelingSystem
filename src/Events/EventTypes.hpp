#pragma once

// vendors
// project headers
// std library
#include <bitset>


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

    static constexpr std::bitset<BitLength> None             {0b0000'0001};
    static constexpr std::bitset<BitLength> Application      {0b0000'0010};
    static constexpr std::bitset<BitLength> Input            {0b0000'0100};
    static constexpr std::bitset<BitLength> Keyboard         {0b0000'1000};
    static constexpr std::bitset<BitLength> Mouse            {0b0001'0000};
    static constexpr std::bitset<BitLength> MouseButton      {0b0010'0000};
    static constexpr std::bitset<BitLength> Window           {0b0100'0000};
}