#include <Engine/Math/Matrix4.h>

#include <Engine/Math/Vector.h>

#include <memory>
#include <cmath>

void Math::Matrix4::SetIdentity()
{
    std::memset(Matrix, 0, sizeof(16 * sizeof(float)));
    Matrix[0][0] = 1;
    Matrix[1][1] = 1;
    Matrix[2][2] = 1;
    Matrix[3][3] = 1;
}

void Math::Matrix4::SetOrthoLH(float width, float height, float nearPlane, float farPlane)
{
    Matrix[0][0] = 2.0f / width;
    Matrix[1][1] = 2.0f / height;
    Matrix[2][2] = 1.0f / (farPlane - nearPlane);
    Matrix[3][2] = -(nearPlane / (farPlane - nearPlane));
}

void Math::Matrix4::SetPrespective(float aspectRatio, float fov, float zNear, float zFar)
{
    std::memset(Matrix, 0, sizeof(15 * sizeof(float)));
    float f = 1.0f / std::tan(fov / 2.0f);
    float lambda = zFar / (zFar - zNear);
    Matrix[0][0] = aspectRatio * f;
    Matrix[1][1] = f;   
    Matrix[2][2] = lambda;
    Matrix[2][3] = 1.0f;
    Matrix[3][2] = -lambda * zNear;
}

void Math::Matrix4::SetScale(const Vector3& scale) noexcept
{
    Matrix[0][0] = scale.X;
    Matrix[1][1] = scale.Y;
    Matrix[2][2] = scale.Z;
}

void Math::Matrix4::SetRotation(const Vector3& rotation) noexcept
{
    Matrix4 rotationX;
    Matrix4 rotationY;
    Matrix4 rotationZ;

    rotationX.SetRotationX(rotation.X);
    rotationY.SetRotationY(rotation.Y);
    rotationZ.SetRotationZ(rotation.Z);

    *this *= rotationX * rotationY * rotationZ;
}

void Math::Matrix4::SetRotationX(float rotation) noexcept
{
    Matrix[1][1] = std::cos(rotation);
    Matrix[1][2] = std::sin(rotation);
    Matrix[2][1] = -std::sin(rotation);
    Matrix[2][2] = std::cos(rotation);
}

void Math::Matrix4::SetRotationY(float rotation) noexcept
{
    Matrix[0][0] = std::cos(rotation);
    Matrix[0][2] = -std::sin(rotation);
    Matrix[2][0] = std::sin(rotation);
    Matrix[2][2] = std::cos(rotation);
}

void Math::Matrix4::SetRotationZ(float rotation) noexcept
{
    Matrix[0][0] = std::cos(rotation);
    Matrix[0][1] = std::sin(rotation);
    Matrix[1][0] = -std::sin(rotation);
    Matrix[1][1] = std::cos(rotation);
}

void Math::Matrix4::SetTranslation(const Vector3& translation) noexcept
{
    Matrix[3][0] = translation.X;
    Matrix[3][1] = translation.Y;
    Matrix[3][2] = translation.Z;
}

void Math::Matrix4::operator*=(const Matrix4& other) noexcept
{
    Matrix4 result;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            result.Matrix[i][j] =
            Matrix[i][0] * other.Matrix[0][j] +
            Matrix[i][1] * other.Matrix[1][j] +
            Matrix[i][2] * other.Matrix[2][j] +
            Matrix[i][3] * other.Matrix[3][j];
        }
    }

    *this = result;
}

Math::Matrix4 Math::Matrix4::operator*(const Matrix4& other) noexcept
{
    Matrix4 result;
    result *= *this;
    result *= other;
    return result;
}