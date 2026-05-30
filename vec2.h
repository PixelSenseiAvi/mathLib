#pragma once

#include "vec.h"

// 2D vector with named x/y accessors.
//
// Accessors are functions rather than pointer members so that the type keeps
// clean value semantics (copying/moving a vec2 does not leave dangling
// references into another object's storage).
template <class T>
class vec2 : public Vector<T, 2>
{
    using Base = Vector<T, 2>;

public:
    vec2() = default;
    vec2(T x, T y)
    {
        Base::a[0] = x;
        Base::a[1] = y;
    }

    // Allow a base-class result (e.g. from operator+) to be used as a vec2.
    vec2(const Base& v) : Base(v) {}

    T& x() { return Base::a[0]; }
    T& y() { return Base::a[1]; }
    const T& x() const { return Base::a[0]; }
    const T& y() const { return Base::a[1]; }

    // 2D cross product: returns the scalar z-component of the 3D cross product,
    // i.e. the signed area of the parallelogram spanned by the two vectors.
    T cross(const vec2<T>& v) const
    {
        return x() * v.y() - y() * v.x();
    }
};
