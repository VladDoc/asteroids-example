#ifndef VECTOR2D_H
#define VECTOR2D_H


template <typename T>
struct Vector2D
{
    T x{};
    T y{};
    Vector2D() = default;
    Vector2D(T xx, T yy) : x(xx), y(yy) {}
    Vector2D(const Vector2D<T>& vec) : x(vec.x), y(vec.y) {}

    template<typename V>
    Vector2D<T>& operator+(const Vector2D<V> &another)
    {
        this->x += another.x;
        this->y += another.y;

        return *this;
    }

    template<typename V>
    Vector2D<T>& operator+=(const Vector2D<V> &another)
    {
        this->x += another.x;
        this->y += another.y;

        return *this;
    }

    template<typename V>
    Vector2D<T>& operator-(const Vector2D<V> &another)
    {
        this->x -= another.x;
        this->y -= another.y;

        return *this;
    }

    template<typename V>
    Vector2D<T> operator-=(const Vector2D<V> &another)
    {
        this->x -= another.x;
        this->y -= another.y;

        return *this;
    }

    template <typename V>
    operator Vector2D<V>() const
    {
        return Vector2D<V>{static_cast<V>(x),
                           static_cast<V>(y)};
    }
};

#endif // VECTOR2D_H
