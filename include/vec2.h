#ifndef VEC2_H
#define VEC2_H

#include <ostream>
#include <cmath>
#include <SDL_rect.h>

template <typename T>
class Vec2
{
  public:
    Vec2();
    Vec2(T mx, T my);

    Vec2 operator+(const Vec2 &v)
    {
        return Vec2(x + v.x, y + v.y);
    }

    Vec2 operator-(const Vec2 &v)
    {
        return Vec2(x - v.x, y - v.y);
    }

    Vec2 operator*(float f)
    {
        return Vec2(x * f, y * f);
    }

    // reversed factor multiplication
    friend Vec2 operator*(const Vec2 &v, float f)
    {
        return Vec2(v.x * f, v.y * f);
    }

    Vec2 operator/(float f)
    {
        static_assert(f != static_cast<T>(0), "error: division by zero");
        return Vec2(x / f, y / f);
    }

    // reversed division
    friend Vec2 operator/(const Vec2 &v, float f)
    {
        static_assert(f != static_cast<T>(0), "error: division by zero");
        return Vec2(v.x / f, v.y / f);
    }

    Vec2 &operator=(const Vec2 &v)
    {
        this->x = v.x;
        this->y = v.y;
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &o, const Vec2<T> v)
    {
        return o << "(" << v.x << "," << v.y << ")";
    }

    double length()
    {
        return std::sqrt(x * x, y * x);
    }

    T x, y;
};

using Vec2i = Vec2<int>;
using Vec2ui = Vec2<unsigned int>;
using Vec2f = Vec2<float>;
using Vec2d = Vec2<double>;

#endif // VEC2_H
