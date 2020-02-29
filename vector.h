#pragma once
#include <iostream>
#include <array>

//TODO: limit the class to numeric type only
//class vector: std::array<T, N>
template<class T, size_t N>
class vector
{
protected:
	std::array<T, N> a;

public:
	//vector constructors
	vector(std::array<T, N>& arr); 
	vector();
	//vector(T[] ar); avoiding raw types

	T dot(vector v);

	const std::array<T, N> operator-(const T& d) noexcept;
	const std::array<T, N> operator+(const T& d) noexcept;
	const std::array<T, N> operator-(const vector& v) noexcept;
	const std::array<T, N> operator+(const vector& v) noexcept;
	const std::array<T, N> operator/(const T& d) noexcept;
	const std::array<T, N> operator/(const vector& v) noexcept;
	friend std::ostream& operator<<(std::ostream& out, const std::array<T, N>& v);

	virtual ~vector();
};

template<class T, size_t N>
inline vector<T, N>::vector(std::array<T, N>& arr)
{
	//Check: std::copy()
	a = &arr;
}


template<class T, size_t N>
inline vector<T, N>::vector()
{
	a = {};
}

template<class T, size_t N>
T vector<T, N>::dot(vector v)
{
	T sum(0);
	for (size_t i = 0; i < N; ++i)
	{
		sum += a[i] * v.a[i];
	}
	return sum;
}


template<class T, size_t N>
const std::array<T, N> vector<T, N>::operator+(const T& d) noexcept
{
	std::array<T, N> vec;
	for (size_t i = 0; i < N; ++i)
	{
		vec[i] = a[i] + d;
	}

	return vec;
}

template<class T, size_t N>
const std::array<T, N> vector<T, N>::operator-(const vector& v) noexcept
{
	std::array<T, N> vec;
	for (size_t i = 0; i < N; ++i)
	{
		vec[i] = a[i] - v.a[i];
	}

	return vec;
}

template<class T, size_t N>
const std::array<T, N> vector<T, N>::operator+(const vector& v) noexcept
{
	std::array<T, N> vec;
	for (size_t i = 0; i < N; ++i)
	{
		vec[i] = a[i] + v.a[i];
	}

	return vec;
}

template<class T, size_t N>
inline const std::array<T, N> vector<T, N>::operator/(const T & d) noexcept
{
	std::array<T, N> vec;
	for (size_t i = 0; i < N; ++i)
	{
		vec[i] = a[i] / d;
	}

	return vec;
}

template<class T, size_t N>
inline const std::array<T, N> vector<T, N>::operator/(const vector & v) noexcept
{
	std::array<T, N> vec;
	for (size_t i = 0; i < N; ++i)
	{
		vec[i] = a[i] / v.a[i];
	}

	return vec;
}

template<class T, size_t N>
vector<T, N>::~vector()
{
}

template<class T, size_t N>
const std::array<T, N> vector<T, N>::operator-(const T& d) noexcept
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
