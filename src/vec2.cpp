#include "vec2.h"

template <typename T>
Vec2<T>::Vec2()
{
    x = 0;
    y = 0;
}

template <>
Vec2<int>::Vec2()
{
    x = 0;
    y = 0;
}

template <>
Vec2<unsigned int>::Vec2()
{
    x = 0;
    y = 0;
}

template <>
Vec2<float>::Vec2()
{
    x = 0.0f;
    y = 0.0f;
}

template <>
Vec2<double>::Vec2()
{
    x = 0.0;
    y = 0.0;
}

template <typename T>
Vec2<T>::Vec2(T mx, T my)
{
    x = mx;
    y = my;
}

template <>
Vec2<int>::Vec2(int mx, int my)
{
    x = mx;
    y = my;
}

template <>
Vec2<unsigned int>::Vec2(unsigned int mx, unsigned int my)
{
    x = mx;
    y = my;
}

template <>
Vec2<float>::Vec2(float mx, float my)
{
    x = mx;
    y = my;
}

template <>
Vec2<double>::Vec2(double mx, double my)
{
    x = mx;
    y = my;
}
