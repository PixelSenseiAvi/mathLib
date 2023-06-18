#pragma once
#include "vec.h"

template<class T>
class vec3 :
	public Vector<T, 3>
{
public:
	T* x = &(Vector<T, 3>::a[0]);
	T* y = &(Vector<T, 3>::a[1]);
	T* z = &(Vector<T, 3>::a[2]);

	inline vec3();
	inline vec3(T r, T g, T b);

	//suitable operations can be implemented in the sub classes
	//inline std::array<T, 3> cross(vec3<T> &v);
	~vec3();
};

template<class T>
inline vec3<T>::vec3()
{
	*x = T(0);
	*y = T(0);
	*z = T(0);
}

template<class T>
inline vec3<T>::vec3(T r, T g, T b)
{
	*x = r;
	*y = g;
	*z = b;
}

//template<class T>
//inline std::array<T, 3> vec3<T>::cross(vec3<T>& v)
//{
//	std::array<T, 3> arr = { (*y) * (v.a[0]), (*x) * (v.a[1]) };
//	return arr;
//}

template<class T>
vec3<T>::~vec3()
{
}