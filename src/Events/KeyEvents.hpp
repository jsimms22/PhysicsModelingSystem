#pragma once

// vendors
// project headers
#include "../Events/Event.hpp"
// std library
#include <sstream>
#include <bitset>

class KeyEvent : public Event
{
public:
    int GetKeyCode() const { return m_keyCode; }

    static std::bitset<EventCategoryFlag::BitLength> GetStaticCategory() { return m_category; };
    virtual std::bitset<EventCategoryFlag::BitLength> GetCategory() const { return GetStaticCategory(); };
    virtual const char* GetName() const { return "KeyEvent"; };

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
    KeyPressEvent(int code, int repeatCount)
        : KeyEvent(code), m_repeatCount{repeatCount} {}
    
    int GetRepeatCount() const { return m_repeatCount; }

    std::string_view ToString() const override
    {
        std::stringstream sstr;
        sstr << "KeyPressedEvent: " << m_keyCode << " (" << m_repeatCount << ")";
        return sstr.str();
    }
    
    static EventType GetStaticType() { return EventType::KeyPress; }
    virtual EventType GetType() const { return GetStaticType(); }
    virtual const char* GetName() const { return "KeyPressEvent"; };

private:
    int m_repeatCount;
};

/* KEY RELEASE EVENT */
class KeyReleaseEvent : public KeyEvent
{
public:
    KeyReleaseEvent(int code)
        : KeyEvent(code) {}

    std::string_view ToString() const override
    {
        std::stringstream sstr;
        sstr << "KeyReleaseEvent: " << m_keyCode;
        return sstr.str();
    }

    static EventType GetStaticType() { return EventType::KeyRelease; }
    virtual EventType GetType() const { return GetStaticType(); }
    virtual const char* GetName() const { return "KeyReleaseEvent"; };

private:
};

/* KEY HOLD EVENT */
class KeyHoldEvent : public KeyEvent
{
public:
    KeyHoldEvent(int code, int repeatCount)
        : KeyEvent(code) {}

    std::string_view ToString() const override
    {
        std::stringstream sstr;
        sstr << "KeyHoldEvent: " << m_keyCode;
        return sstr.str();
    }

    static EventType GetStaticType() { return EventType::KeyHold; }
    virtual EventType GetType() const { return GetStaticType(); }
    virtual const char* GetName() const { return "KeyHoldEvent"; };

private:
};