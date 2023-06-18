#pragma once
#include "vec.h"

template<class T>
class vec3 : public Vector<T, 3>
{
public:
    T* x = &(Vector<T, 3>::a[0]);
    T* y = &(Vector<T, 3>::a[1]);
    T* z = &(Vector<T, 3>::a[2]);

    vec3() = default;
    vec3(T x, T y, T z);

    Vector<T, 3> cross(vec3<T>& v);
};

template<class T>
vec3<T>::vec3(T x, T y, T z)
{
    Vector<T, 3>::a[0] = x;
    Vector<T, 3>::a[1] = y;
    Vector<T, 3>::a[2] = z;
}

template<class T>
Vector<T, 3> vec3<T>::cross(vec3<T>& v)
{
    std::array<T, 3> result;
    result[0] = *y * v.a[2] - *z * v.a[1];
    result[1] = *z * v.a[0] - *x * v.a[2];
    result[2] = *x * v.a[1] - *y * v.a[0];
    return Vector<T, 3>(result);
}
