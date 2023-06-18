#pragma once

#include <iostream>
#include <array>
#include <type_traits>

template<class T, size_t N, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class Vector
{
protected:
	std::array<T, N> a;

public:
	Vector(const std::array<T, N>& arr) : a(arr) {}
	Vector() = default;

	T dot(const Vector& v)
	{
		T sum = 0;
		for (size_t i = 0; i < N; ++i)
		{
			sum += a[i] * v.a[i];
		}
		return sum;
	}

	Vector operator+(const T& d)
	{
		std::array<T, N> vec;
		for (size_t i = 0; i < N; ++i)
		{
			vec[i] = a[i] + d;
		}

		return Vector(vec);
	}

	Vector operator-(const T& d)
	{
		std::array<T, N> vec;
		for (size_t i = 0; i < N; ++i)
		{
			vec[i] = a[i] - d;
		}

		return Vector(vec);
	}

	Vector operator+(const Vector& v)
	{
		std::array<T, N> vec;
		for (size_t i = 0; i < N; ++i)
		{
			vec[i] = a[i] + v.a[i];
		}

		return Vector(vec);
	}

	Vector operator-(const Vector& v)
	{
		std::array<T, N> vec;
		for (size_t i = 0; i < N; ++i)
		{
			vec[i] = a[i] - v.a[i];
		}

		return Vector(vec);
	}

	Vector operator/(const T& d)
	{
		std::array<T, N> vec;
		for (size_t i = 0; i < N; ++i)
		{
			vec[i] = a[i] / d;
		}

		return Vector(vec);
	}

	Vector operator/(const Vector& v)
	{
		std::array<T, N> vec;
		for (size_t i = 0; i < N; ++i)
		{
			vec[i] = a[i] / v.a[i];
		}

		return Vector(vec);
	}

	~Vector() {}

	friend std::ostream& operator<<(std::ostream& out, const Vector& v)
	{
		out << "[";
		for (size_t i = 0; i < N; ++i)
		{
			out << v.a[i];
			if (i != N - 1)
				out << ", ";
		}
		out << "]";
		return out;
	}
};
