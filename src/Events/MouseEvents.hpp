#pragma once

// vendors
// project headers
#include "Event.hpp"
// std library
#include <bitset>
#include <sstream>

/* MOUSE PRESS EVENT */
class MousePressEvent : public Event
{
public:
    MousePressEvent(int code) 
        : m_buttonCode{code} {}

    int GetKeyCode() const { return m_buttonCode; }

    std::string_view ToString() const override
    {
        std::stringstream sstr;
        sstr << "MousePressEvent: " << m_buttonCode;
        return sstr.str();
    }

    static std::bitset<EventCategoryFlag::BitLength> GetStaticCategory() { return m_category; };
    virtual std::bitset<EventCategoryFlag::BitLength> GetCategory() const override { return GetStaticCategory(); };
    static EventType GetStaticType() { return EventType::MousePress; }
    virtual EventType GetType() const override { return GetStaticType(); }
    virtual std::string GetName() const override { return "MousePressEvent"; };

private:
    int m_buttonCode;
    
    static const std::bitset<EventCategoryFlag::BitLength> m_category;
};

/* MOUSE RELEASE EVENT */
class MouseReleaseEvent : public Event
{
public:
    MouseReleaseEvent(int code) 
        : m_buttonCode{code} {}

    int GetKeyCode() const { return m_buttonCode; }

    std::string_view ToString() const override
    {
        std::stringstream sstr;
        sstr << "MouseReleaseEvent: " << m_buttonCode;
        return sstr.str();
    }
    
    static std::bitset<EventCategoryFlag::BitLength> GetStaticCategory() { return m_category; };
    virtual std::bitset<EventCategoryFlag::BitLength> GetCategory() const override { return GetStaticCategory(); };
    static EventType GetStaticType() { return EventType::MouseRelease; }
    virtual EventType GetType() const override { return GetStaticType(); }
    virtual std::string GetName() const override { return "MouseReleaseEvent"; };

private:
    int m_buttonCode;

    static const std::bitset<EventCategoryFlag::BitLength> m_category;
};

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
    virtual std::bitset<EventCategoryFlag::BitLength> GetCategory() const override { return GetStaticCategory(); };
    static EventType GetStaticType() { return EventType::MouseScroll; }
    virtual EventType GetType() const override { return GetStaticType(); }
    virtual std::string GetName() const override { return "MouseScrollEvent"; };

private:
    float m_xOffSet;
    float m_yOffSet;

    static const std::bitset<EventCategoryFlag::BitLength> m_category;
};

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
    virtual std::bitset<EventCategoryFlag::BitLength> GetCategory() const override { return GetStaticCategory(); };
    static EventType GetStaticType() { return EventType::MouseMove; }
    virtual EventType GetType() const override { return GetStaticType(); }
    virtual std::string GetName() const override { return "MouseMoveEvent"; };

private:
    float m_mouseX;
    float m_mouseY;

    static const std::bitset<EventCategoryFlag::BitLength> m_category;
};