#pragma once
#include <iostream>
#include <array>

//TODO: limit the class to numeric type only
//class Vector: std::array<T, N>
template<class T, size_t N>
class Vector
{
protected:
	std::array<T, N> a;

public:
	//Vector constructors
	Vector(std::array<T, N>& arr); 
	Vector();
	//Vector(T[] ar); avoiding raw types

	T dot(Vector v);

	const std::array<T, N> operator-(const T& d) noexcept;
	const std::array<T, N> operator+(const T& d) noexcept;
	const std::array<T, N> operator-(const Vector& v) noexcept;
	const std::array<T, N> operator+(const Vector& v) noexcept;
	const std::array<T, N> operator/(const T& d) noexcept;
	const std::array<T, N> operator/(const Vector& v) noexcept;
	friend std::ostream& operator<<(std::ostream& out, const std::array<T, N>& v);

	virtual ~Vector();
};

template<class T, size_t N>
inline Vector<T, N>::Vector(std::array<T, N>& arr)
{
	a = &arr;
}


template<class T, size_t N>
inline Vector<T, N>::Vector()
{
	a = {};
}

template<class T, size_t N>
T Vector<T, N>::dot(Vector v)
{
	T sum(0);
	for (size_t i = 0; i < N; ++i)
	{
		sum += a[i] * v.a[i];
	}
	return sum;
}


template<class T, size_t N>
const std::array<T, N> Vector<T, N>::operator+(const T& d) noexcept
{
	std::array<T, N> vec;
	for (size_t i = 0; i < N; ++i)
	{
		vec[i] = a[i] + d;
	}

	return vec;
}

template<class T, size_t N>
const std::array<T, N> Vector<T, N>::operator-(const Vector& v) noexcept
{
	std::array<T, N> vec;
	for (size_t i = 0; i < N; ++i)
	{
		vec[i] = a[i] - v.a[i];
	}

	return vec;
}

template<class T, size_t N>
const std::array<T, N> Vector<T, N>::operator+(const Vector& v) noexcept
{
	std::array<T, N> vec;
	for (size_t i = 0; i < N; ++i)
	{
		vec[i] = a[i] + v.a[i];
	}

	return vec;
}

template<class T, size_t N>
const std::array<T, N> Vector<T, N>::operator/(const T & d) noexcept
{
	std::array<T, N> vec;
	for (size_t i = 0; i < N; ++i)
	{
		vec[i] = a[i] / d;
	}

	return vec;
}

template<class T, size_t N>
const std::array<T, N> Vector<T, N>::operator/(const Vector & v) noexcept
{
	std::array<T, N> vec;
	for (size_t i = 0; i < N; ++i)
	{
		vec[i] = a[i] / v.a[i];
	}

	return vec;
}

template<class T, size_t N>
Vector<T, N>::~Vector()
{
}

template<class T, size_t N>
const std::array<T, N> Vector<T, N>::operator-(const T& d) noexcept
{
	std::array<T, N> vec;
	for (size_t i = 0; i < N; ++i)
	{
		vec[i] = a[i] - d;
	}

	return vec;
}

template<class T, size_t N>
std::ostream& operator<<(std::ostream& out, const std::array<T, N>& v)
{
	out << "[";
	for (size_t i = 0; i < N; ++i)
	{
		out << v[i] << ", ";
	}
	out << "]";
	return out;
}
