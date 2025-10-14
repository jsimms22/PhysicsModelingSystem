#pragma once

// vendors
// project headers
#include "../Events/Event.hpp"
// std library
#include <functional>

class EventNotifier
{
    template <typename T>
    using EventFn = std::function<bool(T&)>;
    
public:
    EventNotifier(Event& event)
        : m_event(event) {}

    template <typename T>
    bool Dispatch(const EventFn<T>& func)
    {
        if (m_event.GetType() == T::GetStaticType())
        {
            m_event.m_handled = func(static_cast<T&>(m_event));
            return true;
        }
        return false;
    }

private:
    Event& m_event;
};