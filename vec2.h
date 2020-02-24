#pragma once
#include "vector.h"

template<class T>
class vec2 :
	public vector<T, 2>
{	
public:
	//std::array<T, 2> arr = vector<T, 2>::a;
	T* x = &(vector<T, 2>::a[0]);
	T* y = &(vector<T, 2>::a[1]);

	inline vec2();
	inline vec2(T r, T b);

	//suitable operations can be implemented in the sub classes
	inline std::array<T, 2> cross(vec2<T> &v);
	~vec2();
};

template<class T>
inline vec2<T>::vec2()
{
	*x = T(0);
	*y = T(0);
}

template<class T>
inline vec2<T>::vec2(T r, T b)
{
	*x = r;
	*y = b;
}

template<class T>
inline std::array<T, 2> vec2<T>::cross(vec2<T>& v)
{
	std::array<T, 2> arr = { (*y) * (v.a[0]), (*x) * (v.a[1]) };
	return arr;
}

template<class T>
vec2<T>::~vec2()
{
}

