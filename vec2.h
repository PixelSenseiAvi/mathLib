#pragma once
#include "vec.h"

template<class T>
class vec2 : public Vector<T, 2>
{	
public:
	T* x = &(Vector<T, 2>::a[0]);
	T* y = &(Vector<T, 2>::a[1]);

	vec2() = default;
	vec2(T r, T b);

	T cross(vec2<T> &v);
};

template<class T>
vec2<T>::vec2(T r, T b)
{
	Vector<T, 2>::a[0] = r;
    Vector<T, 2>::a[1] = b;
}

template<class T>
T vec2<T>::cross(vec2<T>& v)
{
	T result = *x * v.a[1] - *y * v.a[0];
	return result;
}


