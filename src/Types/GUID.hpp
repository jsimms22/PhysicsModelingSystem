#pragma once

// vendors
// project headers
// std library
#include <cstdlib>
#include <random>


class GUID
{
public:
    GUID();
    GUID(std::uint64_t id)
        : m_id{id} {}
    GUID(const GUID&) = default;
    
    ~GUID() = default;

    const std::uint64_t& GetGUID() const { return m_id; }

    operator std::uint64_t() const { return m_id; }

    GUID& operator ++() { m_id += 1; return *this; }

private:
    std::uint64_t m_id;
};

template <typename T> struct hash;

template<>
struct hash<GUID>
{
    std::size_t operator()(const GUID& id) const 
    { 
        return static_cast<std::uint64_t>(id);
    }
};