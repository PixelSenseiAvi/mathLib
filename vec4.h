#pragma once
#include "vec.h"

template<class T>
class vec4 : public Vector<T, 4>
{
public:
    T* x = &(Vector<T, 4>::a[0]);
    T* y = &(Vector<T, 4>::a[1]);
    T* z = &(Vector<T, 4>::a[2]);
    T* w = &(Vector<T, 4>::a[3]);

    vec4() = default;
    vec4(T x, T y, T z, T w);
};

template<class T>
vec4<T>::vec4(T x, T y, T z, T w)
{
    Vector<T, 4>::a[0] = x;
    Vector<T, 4>::a[1] = y;
    Vector<T, 4>::a[2] = z;
    Vector<T, 4>::a[3] = w;
}
