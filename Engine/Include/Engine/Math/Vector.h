#pragma once

namespace Math 
{
    struct Vector1
    {
        Vector1() noexcept = default;
        Vector1(float x)
            : X(x) {}

        void operator+= (const Vector1& other) noexcept { X += other.X; }
        Vector1 operator- (const Vector1& other) const noexcept { return X - other.X; }
        bool operator== (const Vector1& other) const noexcept { return X == other.X; }
        bool operator!= (const Vector1& other) const noexcept { return !(*this == other); }

        float X;
    };

    struct Vector2
    {
        Vector2() noexcept = default;

        Vector2(float xy) noexcept
            : X(xy), Y(xy) {}

        Vector2(float x, float y) noexcept
            : X(x), Y(y) {}

        void operator+= (const Vector2& other) noexcept
        {
            X += other.X;
            Y += other.Y;
        }

        Vector2 operator- (const Vector2& other) const noexcept { return { X - other.X, Y - other.Y }; }
        bool operator== (const Vector2& other) const noexcept { return X == other.X && Y == other.Y; }
        bool operator!= (const Vector2& other) const noexcept { return !(*this == other); }

        float X;
        float Y;
    };

    struct Vector3
    {
        Vector3() noexcept = default;
        Vector3(float xyz)
            : X(xyz), Y(xyz), Z(xyz) {}

        Vector3(float x, float y, float z) noexcept
            : X(x), Y(y), Z(z) {}

        void operator+= (const Vector3& other) noexcept
        {
            X += other.X;
            Y += other.Y;
            Z += other.Z;
        }

        Vector3 operator- (const Vector3& other) const noexcept { return { X - other.X, Y - other.Y, Z - other.Z }; }
        bool operator== (const Vector3& other) const noexcept { return X == other.X && Y == other.Y && Z == other.Z; }
        bool operator!= (const Vector3& other) const noexcept { return !(*this == other); }

        float X;
        float Y;
        float Z;
    };

    struct Vector4
    {
        Vector4() noexcept = default;

        Vector4(float xyzw)
            : X(xyzw), Y(xyzw), Z(xyzw), W(xyzw) {}

        Vector4(float x, float y, float z, float w) noexcept
            : X(x), Y(y), Z(z), W(w) {}

        void operator+= (const Vector4& other) noexcept
        {
            X += other.X;
            Y += other.Y;
            Z += other.Z;
            Z += other.W;
        }

        Vector4 operator- (const Vector4& other) const noexcept { return { X - other.X, Y - other.Y, Z - other.Z, W - other.W }; }
        bool operator== (const Vector4& other)  const noexcept { return X == other.X && Y == other.Y && Z == other.Z && W == other.W; }
        bool operator!= (const Vector4& other) const noexcept { return !(*this == other); }

        float X;
        float Y;
        float Z;
        float W;
    };
}
