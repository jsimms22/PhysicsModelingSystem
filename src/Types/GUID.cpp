// vendors
// project headers
#include "../Types/GUID.hpp"
// std library

static std::random_device s_RandomDevice;
static std::mt19937_64 s_Engine(s_RandomDevice());
static std::uniform_int_distribution<std::uint64_t> s_UniformDistribution;

GUID::GUID() 
    : m_id{s_UniformDistribution(s_Engine)} 
{
}