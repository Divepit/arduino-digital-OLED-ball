#pragma once

class Vector3
{
public:
    float x{0.0f};
    float y{0.0f};
    float z{0.0f};
    constexpr Vector3() = default;
    constexpr Vector3(float x, float y, float z) noexcept : x(x), y(y), z(z) {}
    constexpr Vector3 operator+(const Vector3 &other) const
    {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    constexpr Vector3 operator-(const Vector3 &other) const
    {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    constexpr Vector3 operator*(float scalar) const
    {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }
    friend Vector3 operator*(float scalar, const Vector3 &v)
    {
        return v * scalar;
    }
};