#ifndef _Vector_h_
#define _Vector_h_

#include "Trig.h"
#include <SFML/Sytem/Vector2.hpp>
#include <SFML/Sytem/Vector3.hpp>

namespace Vector
{
    template <typename T>
    T DotProduct(const sf::Vector2<T>& lhs, const sf::Vector2<T>& rhs)
    {
        return lhs.x * rhs.x + lhs.y * rhs.y;
    }

    template <typename T>
    sf::Vector3<T> CrossProduct(const sf::Vector2<T>& lhs, const sf::Vector2<T>& rhs)
    {
        return sf::Vector3<T>(0, 0, lhs.x * rhs.y - lhs.y * rhs.x);
    }

    template <typename T>
    T Angle(const sf::Vector2<T>& lhs, const sf::Vector2<T>& rhs)
    {
        return Trig<T>::ArcTan2(CrossProduct(lhs, rhs).z, DotProduct(lhs, rhs));
    }

    template <typename T>
    T Length(const sf::Vector2<T>& v)
    {
        return Trig<T>::Sqrt(LengthSquared(v));
    }

    template <typename T>
    T LengthSquared(const sf::Vector2<T>& v)
    {
        return DotProduct(v, v);
    }

    template <typename T>
    sf::Vector2<T> Resize(sf::Vector2<T>& v, T newLength)
    {
        return v * (newLength / Length(v));
    }

    template <typename T>
    sf::Vector2<T> Rotate(const sf::Vector2<T>& v, T angle)
    {
        T cos = Trig<T>::Cos(angle);
        T sin = Trig<T>::Sin(angle);

        // Don't manipulate x and y separately, otherwise they're overwritten too early
        return sf::Vector2<T>(
               cos * v.x - sin * v.y,
               sin * v.x + cos * v.y);
    }

    template <typename T>
    sf::Vector2<T> UnitVector(const sf::Vector<T>& v)
    {
        return v / Length(v);
    }

    template <typename T>
    sf::Vector2<T> LinearInterpolate(const sf::Vector<T>& v1, const sf::Vector<T>& v2, T step)
    {
        return sf::Vector2<T>((v2.x - v1.x) / step, (v2.y - v1.y) / step);
    }
};

#endif
