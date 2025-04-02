#pragma once

// vendors
// project headers
#include "../Events/Event.hpp"
#include "../Events/EventTypes.hpp"
// std library
#include <bitset>
#include <sstream>

/* MOUSE PRESS EVENT */
class MousePressEvent : public Event
{
public:
    MousePressEvent(int code) 
        : m_keyCode{code} {}

    int GetKeyCode() const { return m_keyCode; }

    std::string_view ToString() const override
    {
        std::stringstream sstr;
        sstr << "KeyPressedEvent: " << m_keyCode;
        return sstr.str();
    }

    static std::bitset<EventCategoryFlag::BitLength> GetStaticCategory() { return m_category; };
    virtual std::bitset<EventCategoryFlag::BitLength> GetCategory() const { return GetStaticCategory(); };
    static EventType GetStaticType() { return EventType::MousePress; }
    virtual EventType GetType() const { return GetStaticType(); }
    virtual const char* GetName() const { return "MousePressEvent"; };

private:
    int m_keyCode;
    
    static const std::bitset<EventCategoryFlag::BitLength> m_category;
};

const std::bitset<EventCategoryFlag::BitLength> MousePressEvent::m_category = {EventCategoryFlag::Input | 
                                                                               EventCategoryFlag::Mouse |
                                                                               EventCategoryFlag::MouseButton};

/* MOUSE RELEASE EVENT */
class MouseReleaseEvent : public Event
{
public:
    MouseReleaseEvent(int code) 
        : m_keyCode{code} {}

    int GetKeyCode() const { return m_keyCode; }

    std::string_view ToString() const override
    {
        std::stringstream sstr;
        sstr << "KeyPressedEvent: " << m_keyCode;
        return sstr.str();
    }
    
    static std::bitset<EventCategoryFlag::BitLength> GetStaticCategory() { return m_category; };
    virtual std::bitset<EventCategoryFlag::BitLength> GetCategory() const { return GetStaticCategory(); };
    static EventType GetStaticType() { return EventType::MouseRelease; }
    virtual EventType GetType() const { return GetStaticType(); }
    virtual const char* GetName() const { return "MouseReleaseEvent"; };

private:
    int m_keyCode;

    static const std::bitset<EventCategoryFlag::BitLength> m_category;
};

const std::bitset<EventCategoryFlag::BitLength> MouseReleaseEvent::m_category = {EventCategoryFlag::Input | 
                                                                                 EventCategoryFlag::Mouse |
                                                                                 EventCategoryFlag::MouseButton};


/* MOUSE SCROLL EVENT */                                                                 
class MouseScrollEvent : public Event
{
public:
    MouseScrollEvent(float xOffSet, float yOffSet)
        : m_xOffSet{xOffSet}, m_yOffSet{yOffSet} {}

    float GetXOffSet() const { return m_xOffSet; }
    float GetYOffSet() const { return m_yOffSet; }

    std::string_view ToString() const override
    {
        std::stringstream sstr;
        sstr << "MouseScrollEvent: "<< m_xOffSet << ", " << m_yOffSet;
        return sstr.str();
    }
    
    static std::bitset<EventCategoryFlag::BitLength> GetStaticCategory() { return m_category; };
    virtual std::bitset<EventCategoryFlag::BitLength> GetCategory() const { return GetStaticCategory(); };
    static EventType GetStaticType() { return EventType::MouseScroll; }
    virtual EventType GetType() const { return GetStaticType(); }
    virtual const char* GetName() const { return "MouseScrollEvent"; };

private:
    float m_xOffSet;
    float m_yOffSet;

    static const std::bitset<EventCategoryFlag::BitLength> m_category;
};

const std::bitset<EventCategoryFlag::BitLength> MouseScrollEvent::m_category = {EventCategoryFlag::Input | 
                                                                                EventCategoryFlag::Mouse};

/* MOUSE PRESS EVENT */
class MouseMoveEvent : public Event
{
public:
    MouseMoveEvent(float x, float y)
        : m_mouseX{x}, m_mouseY{y} {}

    float GetX() const { return m_mouseX; }
    float GetY() const { return m_mouseY; }

    std::string_view ToString() const override
    {
        std::stringstream sstr;
        sstr << "MouseMoveEvent: "<< m_mouseX << ", " << m_mouseY;
        return sstr.str();
    }
    
    static std::bitset<EventCategoryFlag::BitLength> GetStaticCategory() { return m_category; };
    virtual std::bitset<EventCategoryFlag::BitLength> GetCategory() const { return GetStaticCategory(); };
    static EventType GetStaticType() { return EventType::MouseMove; }
    virtual EventType GetType() const { return GetStaticType(); }
    virtual const char* GetName() const { return "MouseMoveEvent"; };

private:
    float m_mouseX;
    float m_mouseY;

    static const std::bitset<EventCategoryFlag::BitLength> m_category;
};

const std::bitset<EventCategoryFlag::BitLength> MouseMoveEvent::m_category = {EventCategoryFlag::Input | 
                                                                              EventCategoryFlag::Mouse};
