#pragma once

#include <array>
#include <cstddef>
#include <ostream>
#include <type_traits>
#include <utility>

// Fixed-size M x N matrix (row-major).
//
// Dimensions are part of the type, so dimension mismatches in addition and
// multiplication are caught at compile time. Storage is a flat std::array for
// cache-friendly, contiguous layout.
template <class T, std::size_t M, std::size_t N>
class matrix
{
    static_assert(std::is_arithmetic<T>::value,
                  "matrix<T, M, N> requires an arithmetic element type T");
    static_assert(M > 0 && N > 0, "matrix dimensions must be positive");

    std::array<T, M * N> data_{}; // value-initialised to zero

public:
    using value_type = T;

    matrix() = default;

    static constexpr std::size_t rows() noexcept { return M; }
    static constexpr std::size_t cols() noexcept { return N; }
    static constexpr bool isSquare() noexcept { return M == N; }

    // ----- element access (row, col) ------------------------------------
    T& operator()(std::size_t row, std::size_t col)
    {
        return data_[row * N + col];
    }

    const T& operator()(std::size_t row, std::size_t col) const
    {
        return data_[row * N + col];
    }

    // ----- factories ----------------------------------------------------
    // Identity matrix (square types only).
    static matrix identity()
    {
        static_assert(M == N, "identity() is only defined for square matrices");
        matrix result;
        for (std::size_t i = 0; i < M; ++i)
            result(i, i) = T{1};
        return result;
    }

    // ----- matrix arithmetic --------------------------------------------
    matrix operator+(const matrix& other) const
    {
        matrix result;
        for (std::size_t i = 0; i < M * N; ++i)
            result.data_[i] = data_[i] + other.data_[i];
        return result;
    }

    matrix operator-(const matrix& other) const
    {
        matrix result;
        for (std::size_t i = 0; i < M * N; ++i)
            result.data_[i] = data_[i] - other.data_[i];
        return result;
    }

    matrix operator*(const T& scalar) const
    {
        matrix result;
        for (std::size_t i = 0; i < M * N; ++i)
            result.data_[i] = data_[i] * scalar;
        return result;
    }

    // Matrix product: (M x N) * (N x P) -> (M x P).
    template <std::size_t P>
    matrix<T, M, P> operator*(const matrix<T, N, P>& other) const
    {
        matrix<T, M, P> result;
        for (std::size_t i = 0; i < M; ++i)
            for (std::size_t k = 0; k < N; ++k)
            {
                const T lhs = (*this)(i, k);
                for (std::size_t j = 0; j < P; ++j)
                    result(i, j) += lhs * other(k, j);
            }
        return result;
    }

    // Transpose: (M x N) -> (N x M).
    matrix<T, N, M> transpose() const
    {
        matrix<T, N, M> result;
        for (std::size_t i = 0; i < M; ++i)
            for (std::size_t j = 0; j < N; ++j)
                result(j, i) = (*this)(i, j);
        return result;
    }

    // Determinant (square types only), via Laplace cofactor expansion.
    T det() const
    {
        static_assert(M == N, "det() is only defined for square matrices");
        return determinant(*this, M);
    }

    // ----- comparison ---------------------------------------------------
    bool operator==(const matrix& other) const { return data_ == other.data_; }
    bool operator!=(const matrix& other) const { return !(*this == other); }

    // ----- streaming ----------------------------------------------------
    friend std::ostream& operator<<(std::ostream& os, const matrix& m)
    {
        for (std::size_t i = 0; i < M; ++i)
        {
            for (std::size_t j = 0; j < N; ++j)
                os << m(i, j) << (j + 1 < N ? ' ' : '\n');
        }
        return os;
    }

private:
    // Determinant of the leading n x n block of a square matrix.
    // Recurses on a dynamically sized minor so it works for any n <= M.
    static T determinant(const matrix& m, std::size_t n)
    {
        if (n == 1)
            return m(0, 0);
        if (n == 2)
            return m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0);

        T result = T{};
        int sign = 1;
        for (std::size_t col = 0; col < n; ++col)
        {
            matrix minor;
            std::size_t mi = 0;
            for (std::size_t r = 1; r < n; ++r)
            {
                std::size_t mj = 0;
                for (std::size_t c = 0; c < n; ++c)
                {
                    if (c == col)
                        continue;
                    minor(mi, mj) = m(r, c);
                    ++mj;
                }
                ++mi;
            }
            result += static_cast<T>(sign) * m(0, col) * determinant(minor, n - 1);
            sign = -sign;
        }
        return result;
    }
};

// Scalar-on-the-left multiplication.
template <class T, std::size_t M, std::size_t N>
matrix<T, M, N> operator*(const T& scalar, const matrix<T, M, N>& m)
{
    return m * scalar;
}
