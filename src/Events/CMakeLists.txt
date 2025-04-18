set(EVENTS_SRC 
    ApplicationEvents.cpp
    ApplicationEvents.hpp
    AsyncEvent.cpp
    AsyncEvent.hpp
    Event.hpp
    EventListener.cpp
    EventListener.hpp
    EventNotifier.cpp
    EventNotifier.hpp
    KeyEvents.cpp
    KeyEvents.hpp
    MouseEvents.cpp
    MouseEvents.hpp
    WindowEvents.cpp
    WindowEvents.hpp
)

add_library(Events STATIC ${EVENTS_SRC})
target_include_directories(Events PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})