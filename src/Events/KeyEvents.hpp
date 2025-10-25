#pragma once

// vendors
// project headers
#include "Event.hpp"
// std library
#include <bitset>
#include <sstream>

class KeyEvent : public Event
{
public:
    int GetKeyCode() const { return m_keyCode; }

    static std::bitset<EventCategoryFlag::BitLength> GetStaticCategory() { return m_category; };
    virtual std::bitset<EventCategoryFlag::BitLength> GetCategory() const override { return GetStaticCategory(); };
    virtual std::string GetName() const override { return "KeyEvent"; };

protected:
    KeyEvent(int code)
        : m_keyCode{code} {}

    int m_keyCode;

    static const std::bitset<EventCategoryFlag::BitLength> m_category;
};

/* KEY PRESS EVENT */
class KeyPressEvent : public KeyEvent
{
public:
    KeyPressEvent(const int code, const int repeatCount)
        : KeyEvent(code), m_repeatCount{repeatCount} {}
    
    int GetRepeatCount() const { return m_repeatCount; }

    std::string_view ToString() const override
    {
        std::stringstream sstr;
        sstr << "KeyPressedEvent: " << m_keyCode << " (" << m_repeatCount << ")";
        return sstr.str();
    }
    
    static EventType GetStaticType() { return EventType::KeyPress; }
    virtual EventType GetType() const override { return GetStaticType(); }
    virtual std::string GetName() const override { return "KeyPressEvent"; };

private:
    int m_repeatCount;
};

/* KEY RELEASE EVENT */
class KeyReleaseEvent : public KeyEvent
{
public:
    KeyReleaseEvent(const int code)
        : KeyEvent(code) {}

    std::string_view ToString() const override
    {
        std::stringstream sstr;
        sstr << "KeyReleaseEvent: " << m_keyCode;
        return sstr.str();
    }

    static EventType GetStaticType() { return EventType::KeyRelease; }
    virtual EventType GetType() const override { return GetStaticType(); }
    virtual std::string GetName() const override { return "KeyReleaseEvent"; };

private:
};

/* KEY HOLD EVENT */
class KeyHoldEvent : public KeyEvent
{
public:
    KeyHoldEvent(const int code, const int repeatCount)
        : KeyEvent(code), m_repeatCount{repeatCount} {}

    std::string_view ToString() const override
    {
        std::stringstream sstr;
        sstr << "KeyHoldEvent: " << m_keyCode;
        return sstr.str();
    }

    static EventType GetStaticType() { return EventType::KeyHold; }
    virtual EventType GetType() const override { return GetStaticType(); }
    virtual std::string GetName() const override { return "KeyHoldEvent"; };

private:
    int m_repeatCount;
};