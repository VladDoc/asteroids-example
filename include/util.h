#pragma once

#ifndef UTIL_H
#define UTIL_H

#include <utility>
#include <ctime>
#include <cmath>
#include <type_traits>

#include "Constants.h"
#include "Vector2d.h"

namespace util
{
    template<typename T>
    constexpr void check(T&)
    {
        static_assert(std::is_arithmetic<T>::value,
                      "Works only with arithmetic types.");
    }

    template<typename T>
    inline bool withinRange(T arg, T min, T max)
    {
        return arg >= min && arg < max;
    }
    // Works only for positive min and max
    inline float clampLooping(float value, float min, float max) {
        int howManyTimesMax = value / max;
        return value >= 0 ? (value - (howManyTimesMax * max))
                          : max + (value - (howManyTimesMax * max));

    }

    template <typename T>
    inline T clamp(T value, T min, T max) {
        if(value > max) {
                return max;
        }
        if(value < min) {
                return min;
        }
        return value;
    }


    inline float angleBetweenPoints(const Vector2D<float>& a,
                                    const Vector2D<float>& b)
    {
        float deltaY = std::abs(b.y - a.y);
        float deltaX = std::abs(b.x - a.x);
        return std::atan2(deltaY, deltaX);
    }

    template <typename T>
    inline T uintPow(T value, unsigned power)
    {
        check(value);

        if(power == 0) return T{0};

        T temp = value;
        while(--power) {
            temp *= value;
        }
        return temp;
    }

    constexpr float radToDeg(float rad)
    {
        return rad * (180.0f / Constants::pi);
    }

    constexpr float degToRad(float deg)
    {
        return deg * (Constants::pi / 180);
    }

    template <typename T>
    inline float vectorAngle(T x, T y)
    {
        float val = std::atan2(x, -y);
        return val < 0 ? Constants::pi * 2 + val : val;
    }

    template <typename T>
    inline T interpolateValue(time_t frametime, T value)
    {
        check(value);
        using namespace Constants;
        return value * ((T)frametime / targetSpeed);
    }

    inline Vector2D<float> lengthWithAngleToVector(float angle, float length)
    {

        return {std::sin(angle) * length,
                std::cos(angle) * length};
    }

    inline int twoIndeciesIntoOne(int i, int j, int width)
    {
        return i * width + j;
    }

    inline void oneIndexIntoTwo(int index, int width, int& i, int& j)
    {
        i = index / width;
        j = index - (index / width) * width;
    }

    template <typename T>
    inline bool withinArea(Vector2D<T> src, Vector2D<T> dest, float radius)
    {
        check(src.x);

        T dx = src.x - dest.x;
        T dy = src.x - dest.x;

        float distance = std::hypot(dx, dy);

        if(distance < radius) {
            return true;
        }

        return false;
    }

    inline void mapToScreenSpace(Vector2D<float>& screen,
                                 const Vector2D<float>& screenSize,
                                 const Vector2D<float>& map,
                                 const Vector2D<float>& mapSize)
    {
        Vector2D<float> zeroOnScreen;

        zeroOnScreen.x = mapSize.x / 2 - screenSize.x / 2;
        zeroOnScreen.y = mapSize.y / 2 - screenSize.y / 2;


        screen.x = map.x - zeroOnScreen.x;
        screen.y = map.y - zeroOnScreen.y;
    }
}

#endif // UTIL_H
