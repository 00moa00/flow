#pragma once
#include <sstream>
#include <bitset>


inline const float& clamp(const float& v, const float& lo, const float& hi)
{
    assert(hi >= lo);
    return (std::max)((std::min)(v, hi), lo);
}