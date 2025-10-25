#pragma once

// vendors
// project headers
// std library
#include <bitset>
#include <cstdint>

using ComponentType = std::uint8_t;
static constexpr ComponentType MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_COMPONENTS>;

static constexpr std::bitset<MAX_COMPONENTS> IDComponentFlag =               {0b0000'0000'0001};
static constexpr std::bitset<MAX_COMPONENTS> RendererComponentFlag =         {0b0000'0000'0010};
static constexpr std::bitset<MAX_COMPONENTS> TransformComponentFlag =        {0b0000'0000'0100};
static constexpr std::bitset<MAX_COMPONENTS> PointLightComponentFlag =       {0b0000'0000'1000};
static constexpr std::bitset<MAX_COMPONENTS> DirectLightComponentFlag =      {0b0000'0001'0000};
static constexpr std::bitset<MAX_COMPONENTS> RigidBodyComponentFlag =        {0b0000'0010'0000};
static constexpr std::bitset<MAX_COMPONENTS> BoxCollisionComponentFlag =     {0b0000'0100'0000};
static constexpr std::bitset<MAX_COMPONENTS> SphereCollisionComponentFlag =  {0b0000'1000'0000};

struct IDComponent
{

};

struct RendererComponent
{

};

struct TransformComponent
{

};

struct PointLightComponent
{

};

struct DirectLightComponent
{
    
};

struct RigidBodyComponent
{

};

struct BoxCollisionComponent
{

};

struct SphereCollisionComponent
{

};