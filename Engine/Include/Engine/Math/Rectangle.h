#pragma once

namespace Math
{
    struct Rectangle
    {
    public:
        Rectangle() noexcept = default;

        Rectangle(int width, int height)
            : Width(width), Height(height) {}

        Rectangle(int left, int top, int width, int height)
            : Left(left), Top(top), Width(width), Height(height) {}

        Rectangle(const Rectangle& other) = default;

        ~Rectangle() noexcept = default;


        int Width = 0, Height = 0, Left = 0, Top = 0;
    };
}