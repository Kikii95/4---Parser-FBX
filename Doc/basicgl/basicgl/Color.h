//
// Created by kolyne on 10/28/25.
//

#ifndef MINIGL_COLOR_H
#define MINIGL_COLOR_H

namespace mngl
{
    struct Color
    {
        constexpr Color(float _r, float _g, float _b, float _a = 1.0f);

        float r;
        float g;
        float b;
        float a;

        static const Color Black;
        static const Color White;
        static const Color Red;
        static const Color Green;
        static const Color Blue;
        static const Color Yellow;
        static const Color Magenta;
        static const Color Cyan;
        static const Color Transparent;
    };

    constexpr Color::Color(float _r, float _g, float _b, float _a) :
        r(_r),
        g(_g),
        b(_b),
        a(_a)
    {
    }

    inline constexpr Color Color::Black{0.f, 0.f, 0.f};
    inline constexpr Color Color::White{1.f, 1.f, 1.f};
    inline constexpr Color Color::Red{1.f, 0.f, 0.f};
    inline constexpr Color Color::Green{0.f, 1.f, 0.f};
    inline constexpr Color Color::Blue{0.f, 0.f, 1.f};
    inline constexpr Color Color::Yellow{1.f, 1.f, 0.f};
    inline constexpr Color Color::Magenta{1.f, 0.f, 1.f};
    inline constexpr Color Color::Cyan{0.f, 1.f, 1.f};
    inline constexpr Color Color::Transparent{0.f, 0.f, 0.f, 0.f};
}

#endif //MINIGL_COLOR_H
