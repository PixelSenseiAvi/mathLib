#pragma once

#include <array>
#include <cmath>
#include <cstddef>
#include <ostream>
#include <type_traits>

// Generic fixed-size mathematical vector.
//
// T must be an arithmetic type (enforced via static_assert). N is the number of
// components. The storage is a std::array, so Vector has value semantics: it can
// be freely copied, moved, and stored in containers.
template <class T, std::size_t N>
class Vector
{
    static_assert(std::is_arithmetic<T>::value,
                  "Vector<T, N> requires an arithmetic component type T");
    static_assert(N > 0, "Vector<T, N> requires N > 0");

protected:
    std::array<T, N> a{}; // value-initialised to zero

public:
    using value_type = T;
    static constexpr std::size_t size() noexcept { return N; }

    Vector() = default;
    explicit Vector(const std::array<T, N>& arr) : a(arr) {}

    // ----- element access -----------------------------------------------
    T& operator[](std::size_t i) { return a[i]; }
    const T& operator[](std::size_t i) const { return a[i]; }

    T& at(std::size_t i) { return a.at(i); }
    const T& at(std::size_t i) const { return a.at(i); }

    T* data() noexcept { return a.data(); }
    const T* data() const noexcept { return a.data(); }

    // ----- vector / vector arithmetic -----------------------------------
    Vector operator+(const Vector& v) const
    {
        Vector result;
        for (std::size_t i = 0; i < N; ++i)
            result.a[i] = a[i] + v.a[i];
        return result;
    }

    Vector operator-(const Vector& v) const
    {
        Vector result;
        for (std::size_t i = 0; i < N; ++i)
            result.a[i] = a[i] - v.a[i];
        return result;
    }

    // Component-wise (Hadamard) product / quotient.
    Vector operator*(const Vector& v) const
    {
        Vector result;
        for (std::size_t i = 0; i < N; ++i)
            result.a[i] = a[i] * v.a[i];
        return result;
    }

    Vector operator/(const Vector& v) const
    {
        Vector result;
        for (std::size_t i = 0; i < N; ++i)
            result.a[i] = a[i] / v.a[i];
        return result;
    }

    // ----- vector / scalar arithmetic -----------------------------------
    Vector operator+(const T& s) const
    {
        Vector result;
        for (std::size_t i = 0; i < N; ++i)
            result.a[i] = a[i] + s;
        return result;
    }

    Vector operator-(const T& s) const
    {
        Vector result;
        for (std::size_t i = 0; i < N; ++i)
            result.a[i] = a[i] - s;
        return result;
    }

    Vector operator*(const T& s) const
    {
        Vector result;
        for (std::size_t i = 0; i < N; ++i)
            result.a[i] = a[i] * s;
        return result;
    }

    Vector operator/(const T& s) const
    {
        Vector result;
        for (std::size_t i = 0; i < N; ++i)
            result.a[i] = a[i] / s;
        return result;
    }

    // ----- compound assignment ------------------------------------------
    Vector& operator+=(const Vector& v)
    {
        for (std::size_t i = 0; i < N; ++i) a[i] += v.a[i];
        return *this;
    }

    Vector& operator-=(const Vector& v)
    {
        for (std::size_t i = 0; i < N; ++i) a[i] -= v.a[i];
        return *this;
    }

    Vector& operator*=(const T& s)
    {
        for (std::size_t i = 0; i < N; ++i) a[i] *= s;
        return *this;
    }

    Vector& operator/=(const T& s)
    {
        for (std::size_t i = 0; i < N; ++i) a[i] /= s;
        return *this;
    }

    // Unary negation.
    Vector operator-() const
    {
        Vector result;
        for (std::size_t i = 0; i < N; ++i)
            result.a[i] = -a[i];
        return result;
    }

    // ----- geometric operations -----------------------------------------
    T dot(const Vector& v) const
    {
        T sum = T{};
        for (std::size_t i = 0; i < N; ++i)
            sum += a[i] * v.a[i];
        return sum;
    }

    // Squared length: avoids the sqrt when only comparisons are needed.
    T lengthSquared() const { return dot(*this); }

    // Euclidean length (magnitude).
    T length() const
    {
        return static_cast<T>(std::sqrt(static_cast<double>(lengthSquared())));
    }

    // Returns a unit-length copy. Returns the zero vector if length is zero.
    Vector normalized() const
    {
        const T len = length();
        if (len == T{})
            return *this;
        return *this / len;
    }

    // Normalises in place and returns *this for chaining.
    Vector& normalize()
    {
        const T len = length();
        if (len != T{})
            *this /= len;
        return *this;
    }

    // ----- comparison ---------------------------------------------------
    bool operator==(const Vector& v) const { return a == v.a; }
    bool operator!=(const Vector& v) const { return !(*this == v); }

    // ----- streaming ----------------------------------------------------
    friend std::ostream& operator<<(std::ostream& out, const Vector& v)
    {
        out << "[";
        for (std::size_t i = 0; i < N; ++i)
        {
            out << v.a[i];
            if (i != N - 1)
                out << ", ";
        }
        out << "]";
        return out;
    }
};

// Scalar-on-the-left multiplication, so both `v * s` and `s * v` work.
template <class T, std::size_t N>
Vector<T, N> operator*(const T& s, const Vector<T, N>& v)
{
    return v * s;
}
