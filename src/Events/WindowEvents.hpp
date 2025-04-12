#pragma once

// vendors
// project headers
#include "../Events/Event.hpp"
// std library
#include <string_view>
#include <sstream>
#include <cstdint>

/* WINDOWS CLOSE EVENT */
class WindowCloseEvent : public Event
{
public:
    WindowCloseEvent() {}

    static std::bitset<EventCategoryFlag::BitLength> GetStaticCategory() { return m_category; };
    virtual std::bitset<EventCategoryFlag::BitLength> GetCategory() const { return GetStaticCategory(); };
    static EventType GetStaticType() { return EventType::WindowClose; }
    virtual EventType GetType() const { return GetStaticType(); }
    virtual const char* GetName() const { return "WindowCloseEvent"; };

private:
    static const std::bitset<EventCategoryFlag::BitLength> m_category;
};

/* WINDOWS OPEN EVENT */
class WindowOpenEvent : public Event
{
public:
    WindowOpenEvent(std::uint32_t width, std::uint32_t height)
        : m_width{width}, m_height{height} {}
    
    std::uint32_t GetWidth() const { return m_width; }
    std::uint32_t GetHeight() const { return m_height; }

    std::string_view ToString() const override
    {
        std::stringstream sstr;
        sstr << "WindowOpenEvent: " << m_width << ", " << m_height;
        return sstr.str();
    }

    static std::bitset<EventCategoryFlag::BitLength> GetStaticCategory() { return m_category; };
    virtual std::bitset<EventCategoryFlag::BitLength> GetCategory() const { return GetStaticCategory(); };
    static EventType GetStaticType() { return EventType::WindowOpen; }
    virtual EventType GetType() const { return GetStaticType(); }
    virtual const char* GetName() const { return "WindowOpenEvent"; };

private:
    std::uint32_t m_width;
    std::uint32_t m_height;

    static const std::bitset<EventCategoryFlag::BitLength> m_category;
};

/* WINDOWS RESIZE EVENT */
class WindowResizeEvent : public Event
{
public:
    WindowResizeEvent(std::uint32_t width, std::uint32_t height)
        : m_width{width}, m_height{height} {}
    
    std::uint32_t GetWidth() const { return m_width; }
    std::uint32_t GetHeight() const { return m_height; }

    std::string_view ToString() const override
    {
        std::stringstream sstr;
        sstr << "WindowResizeEvent: " << m_width << ", " << m_height;
        return sstr.str();
    }

    static std::bitset<EventCategoryFlag::BitLength> GetStaticCategory() { return m_category; };
    virtual std::bitset<EventCategoryFlag::BitLength> GetCategory() const { return GetStaticCategory(); };
    static EventType GetStaticType() { return EventType::WindowOpen; }
    virtual EventType GetType() const { return GetStaticType(); }
    virtual const char* GetName() const { return "WindowResizeEvent"; };

private:
    std::uint32_t m_width;
    std::uint32_t m_height;

    static const std::bitset<EventCategoryFlag::BitLength> m_category;
};
