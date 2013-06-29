#ifndef _Trigonometry_h_
#define _Trigonometry_h_

#include <cmath>

template <typename T>
struct Trig;

template <>
struct Trig<float>
{
    typedef float Type;

    static Type sin(Type deg)                       { return std::sin(degToRad(deg));               }
    static Type cos(Type deg)                       { return std::cos(degToRad(deg));               }
    static Type tan(Type deg)                       { return std::tan(degToRad(deg));               }
    static Type arcSin(Type value)                  { return radToDeg(std::asin(value));            }
    static Type arcCos(Type value)                  { return radToDeg(std::acos(value));            }
    static Type arcTan2(Type valY, Type valX)       { return radToDeg(std::atan2(valY, valX));      }
    static Type sqrt(Type value)                    { return std::sqrt(value);                      }

    static Type pi()                                { return 3.14159265f;                           }
    static Type radToDeg(Type rad)                  { return 180 / 3.14159265f * rad;               }
    static Type degToRad(Type deg)                  { return 3.14159265f / 180 * deg;               }
};

template <typename T>
T toDegree(T radian)
{
    return Trig<T>::radToDeg(radian);
}

template <typename T>
T toRadian(T degree)
{
    return Trig<T>::degToRad(degree);
}

#endif
