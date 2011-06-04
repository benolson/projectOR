#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2
{
public:
    Vector2();
    Vector2(float _x, float _y);

    Vector2 operator+(const Vector2& rhs);
    Vector2 operator-(const Vector2& rhs);
    Vector2 operator/(float rhs);
    Vector2 operator*(float rhs);
    Vector2& operator+=(const Vector2& rhs);
    Vector2& operator-=(const Vector2& rhs);

    float length();
    void normalize();

    float x;
    float y;
};

#endif // VECTOR2_H
