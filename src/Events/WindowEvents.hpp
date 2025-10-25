#pragma once

// vendors
// project headers
#include "Event.hpp"
// std library
#include <cstdint>
#include <sstream>
#include <string_view>

/* WINDOWS CLOSE EVENT */
class WindowCloseEvent : public Event
{
public:
    WindowCloseEvent() {}

    static std::bitset<EventCategoryFlag::BitLength> GetStaticCategory() { return m_category; };
    virtual std::bitset<EventCategoryFlag::BitLength> GetCategory() const override { return GetStaticCategory(); };
    static EventType GetStaticType() { return EventType::WindowClose; }
    virtual EventType GetType() const override { return GetStaticType(); }
    virtual std::string GetName() const override { return "WindowCloseEvent"; };

private:
    static const std::bitset<EventCategoryFlag::BitLength> m_category;
};

/* WINDOWS OPEN EVENT */
class WindowOpenEvent : public Event
{
public:
    WindowOpenEvent(const std::uint32_t width, const std::uint32_t height)
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
    virtual std::bitset<EventCategoryFlag::BitLength> GetCategory() const override { return GetStaticCategory(); };
    static EventType GetStaticType() { return EventType::WindowOpen; }
    virtual EventType GetType() const override { return GetStaticType(); }
    virtual std::string GetName() const override { return "WindowOpenEvent"; };

private:
    std::uint32_t m_width = 0;
    std::uint32_t m_height = 0;

    static const std::bitset<EventCategoryFlag::BitLength> m_category;
};

/* WINDOWS RESIZE EVENT */
class WindowResizeEvent : public Event
{
public:
    WindowResizeEvent(const std::uint32_t width, const std::uint32_t height)
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
    virtual std::bitset<EventCategoryFlag::BitLength> GetCategory() const override { return GetStaticCategory(); };
    static EventType GetStaticType() { return EventType::WindowOpen; }
    virtual EventType GetType() const override { return GetStaticType(); }
    virtual std::string GetName() const override { return "WindowResizeEvent"; };

private:
    std::uint32_t m_width = 0;
    std::uint32_t m_height = 0;

    static const std::bitset<EventCategoryFlag::BitLength> m_category;
};
