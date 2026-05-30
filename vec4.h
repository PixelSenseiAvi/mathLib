#pragma once

#include "vec.h"

// 4D vector with named x/y/z/w accessors (e.g. homogeneous coordinates / RGBA).
template <class T>
class vec4 : public Vector<T, 4>
{
    using Base = Vector<T, 4>;

public:
    vec4() = default;
    vec4(T x, T y, T z, T w)
    {
        Base::a[0] = x;
        Base::a[1] = y;
        Base::a[2] = z;
        Base::a[3] = w;
    }

    // Allow a base-class result (e.g. from operator+) to be used as a vec4.
    vec4(const Base& v) : Base(v) {}

    T& x() { return Base::a[0]; }
    T& y() { return Base::a[1]; }
    T& z() { return Base::a[2]; }
    T& w() { return Base::a[3]; }
    const T& x() const { return Base::a[0]; }
    const T& y() const { return Base::a[1]; }
    const T& z() const { return Base::a[2]; }
    const T& w() const { return Base::a[3]; }
};
