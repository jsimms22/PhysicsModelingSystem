#pragma once

// vendors
// project headers
// std library
#include <string_view>

class GUID
{
public:
    GUID() = default;
    ~GUID() = default;

    const std::string_view& GetGUID() const { return m_guid; }

private:
    std::string_view m_guid = "0000-0000-0000-0000";
};