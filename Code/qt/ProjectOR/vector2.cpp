#include "vector2.h"
#include <math.h>

Vector2::Vector2()
    : x(0), y(0)
{
}

Vector2::Vector2(float _x, float _y)
    : x(_x), y(_y)
{
}

Vector2 Vector2::operator+(const Vector2& rhs)
{
    Vector2 r;
    r.x = x + rhs.x;
    r.y = y + rhs.y;
    return r;
}

Vector2 Vector2::operator-(const Vector2& rhs)
{
    Vector2 r;
    r.x = x - rhs.x;
    r.y = y - rhs.y;
    return r;
}

Vector2 Vector2::operator/(float rhs)
{
    Vector2 r;
    if (rhs == 0)
        return Vector2();
    r.x = x / rhs;
    r.y = y / rhs;
    return r;
}

Vector2 Vector2::operator*(float rhs)
{
    Vector2 r;
    r.x = x * rhs;
    r.y = y * rhs;
    return r;
}

Vector2& Vector2::operator+=(const Vector2& rhs)
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

float Vector2::length()
{
    return sqrtf(x*x + y*y);
}

void Vector2::normalize()
{
    float l = length();
    if (l == 0)
        return;
    x /= l;
    y /= l;
}
