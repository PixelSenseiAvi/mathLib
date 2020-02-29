#pragma once
#include <iostream>
#include <array>
#include <stdexcept>


template<class T, size_t M, size_t N>
class matrix
{
public:
	std::array<std::array<T, M>, N> mat;
	//Or std::array<T, M*N> mat;


	//matrix constructor
	matrix();
	matrix(std::array<std::array<T, M>, N> &arr);

	const std::array<std::array<T, M>, N> transpose() noexcept;
	size_t getRows();
	size_t getColumns();

	const matrix<T, M, N> operator-(const T& d) noexcept;
	const matrix<T, M, N> operator+(const T& d) noexcept;
	const matrix<T, M, N> operator-(const matrix<T, M, N>& v) noexcept;
	const matrix<T, M, N> operator+(const matrix<T, M, N>& v) noexcept;
	const matrix<T, M, N> operator*(const T& d) noexcept;
	const matrix<T, M, N> operator*(const matrix<T, M, N>& v) noexcept;
	const matrix<T, M, N> operator/(const T& d) noexcept;
	//TODO: const matrix<T, M, N> operator/(const matrix<T, M, N>& v) noexcept;
	friend std::ostream& operator<<(std::ostream& out, const matrix& v);
	virtual ~matrix();
};

template<class T, size_t M, size_t N>
matrix<T, M, N>::matrix()
{
	mat = {};
}

template<class T, size_t M, size_t N>
matrix<T, M, N>::matrix(std::array<std::array<T, M>, N> &arr)
{
	std::copy(&arr[0][0], &arr[0][0] + M * N, &mat[0][0]);
}


template<class T, size_t M, size_t N>
size_t matrix<T, M, N>::getRows()
{
	return M;
}

template<class T, size_t M, size_t N>
size_t matrix<T, M, N>::getColumns()
{
	return N;
}

template<class T, size_t M, size_t N>
const std::array<std::array<T, M>, N> matrix<T, M, N>::transpose() noexcept
{
	std::array<std::array<T, M>, N> arr;
	for (size_t i = 0; i < N; ++i)
	{
		for (size_t j = 0; j < M; ++j)
		{
			arr[j][i] = mat[i][j];
		}
	}
	return arr;
}


template<class T, size_t M, size_t N>
const matrix<T, M, N> matrix<T, M, N>::operator-(const T& d) noexcept
{
	matrix<T, M, N> matrix;
	//std::array<std::array<T, M>, N> arr;
	matrix.mat = {};
	for (size_t i = 0; i < N; ++i)
	{
		for (size_t j = 0; j < M; ++j)
		{
			matrix.mat[i][j] = mat[i][j] - d;
		}
	}

	return matrix;
}

template<class T, size_t M, size_t N>
const matrix<T, M, N> matrix<T, M, N>::operator+(const T& d) noexcept
{
	matrix<T, M, N> matrix;
	//std::array<std::array<T, M>, N> arr;
	matrix.mat = {};
	for (size_t i = 0; i < N; ++i)
	{
		for (size_t j = 0; j < M; ++j)
		{
			matrix.mat[i][j] = mat[i][j] + d;
		}
	}

	return matrix;
}

template<class T, size_t M, size_t N>
const matrix<T, M, N> matrix<T, M, N>::operator-(const matrix<T, M, N>& v) noexcept
{
	matrix<T, M, N> matrix;
	//std::array<std::array<T, M>, N> arr;
	matrix.mat = {};
	for (size_t i = 0; i < N; ++i)
	{
		for (size_t j = 0; j < M; ++j)
		{
			matrix.mat[i][j] = mat[i][j] - v.mat[i][j];
		}
	}

	return matrix;
}

template<class T, size_t M, size_t N>
const matrix<T, M, N> matrix<T, M, N>::operator+(const matrix<T, M, N>& v) noexcept
{
	matrix<T, M, N> matrix;
	//std::array<std::array<T, M>, N> arr;
	matrix.mat = {};
	for (size_t i = 0; i < N; ++i)
	{
		for (size_t j = 0; j < M; ++j)
		{
			matrix.mat[i][j] = mat[i][j] + v.mat[i][j];
		}
	}

	return matrix;
}

template<class T, size_t M, size_t N>
inline const matrix<T, M, N> matrix<T, M, N>::operator*(const T & d) noexcept
{
	matrix<T, M, N> matrix;
	//std::array<std::array<T, M>, N> arr;
	matrix.mat = {};
	for (size_t i = 0; i < N; ++i)
	{
		for (size_t j = 0; j < M; ++j)
		{
			matrix.mat[i][j] = mat[i][j] * d;
		}
	}

	return matrix;
}

template<class T, size_t M, size_t N>
inline const matrix<T, M, N> matrix<T, M, N>::operator*(const matrix<T, M, N>& v) noexcept
{
	matrix<T, M, N> matrix;
	//std::array<std::array<T, M>, N> arr;
	matrix.mat = {};
	if (N != v.getRows())
	{
		throw std::bad_array_new_length("check matrix dimensions");
	}

	std::array<std::array<T, M>, v.getColumns()> arr;
	for (size_t i = 0; i < N; ++i)
	{
		for (size_t j = 0; j < v.getColumns(); ++j)
		{
			for (size_t k = 0; k < M; ++k)
			{
				matrix.mat[i][j] += mat[i][k] * v.mat[k][j];
			}
		}
	}
	return matrix;
}


template<class T, size_t M, size_t N>
inline const matrix<T, M, N> matrix<T, M, N>::operator/(const T & d) noexcept
{
	if (d == T(0))
	{
		throw std::domain_error("Cannot divide by 0.");
	}
	matrix<T, M, N> matrix;
	//std::array<std::array<T, M>, N> arr;
	matrix.mat = {};
	for (size_t i = 0; i < N; ++i)
	{
		for (size_t j = 0; j < M; ++j)
		{
			matrix.mat[i][j] = mat[i][j] / d;
		}
	}

	return matrix;
}
//
//template<class T, size_t M, size_t N>
//inline const matrix<T, M, N> matrix<T, M, N>::operator/(const matrix<T, M, N>& v) noexcept
//{
//	matrix<T, M, N> matrix;
//	//std::array<std::array<T, M>, N> arr;
//	matrix.mat = {};
//	if (N != v.getRows())
//	{
//		throw std::bad_array_new_length("check matrix dimensions");
//	}
//
//	std::array<std::array<T, M>, v.getColumns()> arr;
//	for (size_t i = 0; i < N; ++i)
//	{
//		
//			for (size_t k = 0; k < M; ++k)
//			{
//				matrix.mat[i][k] += mat[i][k] / v.ge;
//			}
//		
//	}
//	return matrix;
//}

template<class T, size_t M, size_t N>
matrix<T, M, N>::~matrix()
{
}

template<class T, size_t M, size_t N>
std::ostream& operator<<(std::ostream& out, matrix<T, M, N>& v)
{
	out << "[";
	for (size_t i = 0; i < N; ++i)
	{
		for (size_t j = 0; j < M; ++j)
		{
			out << v.mat[i][j] << ", ";
		}
		out << std::endl;
	}
	out << "]";
	return out;
}

