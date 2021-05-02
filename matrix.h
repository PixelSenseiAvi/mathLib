#pragma once
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
	matrix(std::array<std::array<T, M>, N>& arr);

	const std::array<std::array<T, M>, N> f() noexcept;
	size_t getRows();
	size_t getColumns();

	const matrix<T, M, N> transpose(matrix<T, M, N>& m);
	const T det(matrix<T, M, N>& m);
	const matrix<T, M, N> inv(matrix<T, M, N>& m);
	const matrix<T, M, N> identity();

	bool inline isSquare(matrix<T, M, N>& m) const;
	const matrix<T, M, N> adjoint(matrix<T, M, N>& m);

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
inline matrix<T, M, N>::matrix()
{
	mat = {};
}

template<class T, size_t M, size_t N>
inline matrix<T, M, N>::matrix(std::array<std::array<T, M>, N>& arr)
{
	std::copy(&arr[0][0], &arr[0][0] + M * N, &mat[0][0]);
}


template<class T, size_t M, size_t N>
inline size_t matrix<T, M, N>::getRows()
{
	return M;
}

template<class T, size_t M, size_t N>
inline size_t matrix<T, M, N>::getColumns()
{
	return N;
}

template<class T, size_t M, size_t N>
const matrix<T, M, N> matrix<T, M, N>::transpose(matrix<T, M, N>& m)
{
	std::array<std::array<T, M>, N> arr = m.mat;
	for (size_t i = 0; i < N; ++i)
	{
		for (size_t j = 0; j < M; ++j)
		{
			arr[j][i] = mat[i][j];
		}
	}
	//matrix mat = new matrix(arr);
	return new matrix(arr);
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
inline const matrix<T, M, N> matrix<T, M, N>::operator*(const T& d) noexcept
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
const matrix<T, M, N> matrix<T, M, N>::operator*(const matrix<T, M, N>& v) noexcept
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
const matrix<T, M, N> matrix<T, M, N>::operator/(const T& d) noexcept
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

template<class T, size_t M, size_t N>
const matrix<T, M, N> matrix<T, M, N>::identity() 
{
#ifndef ISSQUARE
#define ISSQUARE
	assert(isSquare(m));
#endif
	matrix m = new matrix();
	for (i = 0; i < N; i++) {
		for (j = N; j < 2 * N; j++) {
			if (i == (j - n))
				m.mat[i][j] = T(1);
			else
				m.mat[i][j] = T(0);
		}
	}
	return m;
}

template<class T, size_t M, size_t N>
const matrix<T, M, N> matrix<T, M, N>::inv(matrix<T, M, N>& m) {
#ifndef ISSQUARE
#define ISSQUARE
	assert(isSquare(m));
	assert(det(m) != 0);
#endif
	//T determinant = det(m);
	T d = T(0);

	int n = m.getRows();
	//Guass-Jordan Elimination
	// Initializing Right-hand side to identity matrix
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < 2 * n; ++j)
		{
			if (j == (i + n))
			{
				m.mat[i][j] = 1;
			}
		}
	}

	// Partial pivoting
	for (int i = n; i > 1; --i)
	{
		if (m.mat[i - 1][1] < m.mat[i][1])
		{
			for (int j = 0; j < 2 * n; ++j)
			{
				d = m.mat[i][j];
				m.mat[i][j] = m.mat[i - 1][j];
				m.mat[i - 1][j] = d;
			}
		}
	}

	// Reducing To Diagonal Matrix
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < 2 * n; ++j)
		{
			if (j != i)
			{
				d = m.mat[j][i] / m.mat[i][i];
				for (int k = 0; k < n * 2; ++k)
				{
					m.mat[j][k] -= m.mat[i][k] * d;
				}
			}
		}
	}

	// Reducing To Unit Matrix
	for (int i = 0; i < n; ++i)
	{
		d = m.mat[i][i];
		for (int j = 0; j < 2 * n; ++j)
		{
			m.mat[i][j] = m.mat[i][j] / d;
		}
	}

	return m;
}

template<class T, size_t M, size_t N>
const matrix<T, M, N> matrix<T, M, N>::adjoint(matrix<T, M, N>& m)
{
#ifndef ISSQUARE
#define ISSQUARE
	assert(isSquare(m));
#endif
	int n = m.getRows();
	if (n == 1)
	{
		return matrix(std::array < std::array<T, 1> = { 1 });
	}

	// temp is used to store cofactors of A[][]
	int sign = 1;
	matrix<T, M, N> temp;
	matrix<T, M, N> adj;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			// Get cofactor of A[i][j]
			getCofactor(m, temp, i, j, n);

			// sign of adj[j][i] positive if sum of row
			// and column indexes is even.
			sign = ((i + j) % 2 == 0) ? 1 : -1;

			// Interchanging rows and columns to get the
			// transpose of the cofactor matrix
			adj.mat[j][i] = (sign) * (det(temp));
		}
	}
	return adj;
}


//// Function to calculate and store inverse, returns false if
//// matrix is singular
//bool inverse(int A[N][N], float inverse[N][N])
//{
//	// Find determinant of A[][]
//	int det = determinant(A, N);
//	if (det == 0)
//	{
//		cout << "Singular matrix, can't find its inverse";
//		return false;
//	}
//
//	// Find adjoint
//	int adj[N][N];
//	adjoint(A, adj);
//
//	// Find Inverse using formula "inverse(A) = adj(A)/det(A)"
//	for (int i = 0; i < N; i++)
//		for (int j = 0; j < N; j++)
//			inverse[i][j] = adj[i][j] / float(det);
//
//	return true;
//}

template <typename T, size_t M, size_t N>
bool matrix<T, M, N>::isSquare(matrix<T, M, N>& m) const {
	return m.getRows > 0 ? m.getRows() == m.getColumns():0;
	//return empty() ? 0 : data.size() == data[0].size();
}

template <typename T, size_t M, size_t N>
void subMatrix(matrix<T, M, N> m, matrix<T,M,N> temp, int p, int q, int n) {
	int i = 0, j = 0;
	// filling the sub matrix
	for (int row = 0; row < n; row++) {
		for (int col = 0; col < n; col++) {
			// skipping if the current row or column is not equal to the current
			// element row and column
			if (row != p && col != q) {
				temp.mat[i][j++] = m.mat[row][col];
				if (j == n - 1) {
					j = 0;
					i++;
				}
			}
		}
	}
}

template <typename T, size_t M, size_t N>
const T matrix<T,M,N>::det(matrix<T, M, N>& m) {
#ifndef ISSQUARE
#define ISSQUARE
	assert(isSquare(m));
#endif

	int n = int(m.getRows());
	T determinant = T(0);
	if (n == 1) {
		return m.mat[0][0];
	}

	if (n == 2) {
		return (m.mat[0][0] * m.mat[1][1]) - (m.mat[0][1] * m.mat[1][0]);
	}

	matrix<T, M, N> temp = new matrix(new std::array<std::array<T, M>, N>);
	int sign = 1;
	
	for (int i = 0; i < n; i++) {
		subMatrix(m.mat, temp, 0, i, n);
		determinant += sign * m.mat[0][i] * det(temp, n - 1);
		sign = -sign;
	}
	return determinant;
}
