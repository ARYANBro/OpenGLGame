#include <Engine/Math/Utility.h>

#include <numbers>

float Math::DegToRad(float degrees)
{
    return (degrees * std::numbers::pi_v<float>) / 180.0f;
}

float Math::RadToDeg(float radians)
{
    return radians * (180.0f / std::numbers::pi_v<float>);
}