#pragma once

namespace Math
{
    struct Vector3;

    struct Matrix4
    {
    public:
        Matrix4() { SetIdentity(); }
        ~Matrix4() noexcept = default;

        void SetIdentity();
        void SetOrthoLH(float width, float height, float nearPlane, float farPlane);
        void SetPrespective(float aspectRatio, float fov, float zNear, float zFar);
        void SetScale(const Vector3& scale) noexcept;
        void SetTranslation(const Vector3& translation) noexcept;

        void SetRotation(const Vector3& rotation) noexcept;
        void SetRotationX(float rotation) noexcept;
        void SetRotationY(float rotation) noexcept;
        void SetRotationZ(float rotation) noexcept;

        void operator*=(const Matrix4& other) noexcept;
        Matrix4 operator*(const Matrix4& other) noexcept;

        float Matrix[4][4] = {};
    };
};