#pragma once

#include "vec.h"

// 3D vector with named x/y/z accessors.
template <class T>
class vec3 : public Vector<T, 3>
{
    using Base = Vector<T, 3>;

public:
    vec3() = default;
    vec3(T x, T y, T z)
    {
        Base::a[0] = x;
        Base::a[1] = y;
        Base::a[2] = z;
    }

    // Allow a base-class result (e.g. from operator+) to be used as a vec3.
    vec3(const Base& v) : Base(v) {}

    T& x() { return Base::a[0]; }
    T& y() { return Base::a[1]; }
    T& z() { return Base::a[2]; }
    const T& x() const { return Base::a[0]; }
    const T& y() const { return Base::a[1]; }
    const T& z() const { return Base::a[2]; }

    // 3D cross product.
    vec3<T> cross(const vec3<T>& v) const
    {
        return vec3<T>(
            y() * v.z() - z() * v.y(),
            z() * v.x() - x() * v.z(),
            x() * v.y() - y() * v.x());
    }
};
