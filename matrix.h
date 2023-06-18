#pragma once

#include <vector>
#include <cassert>
#include <algorithm>

template<typename T, size_t M, size_t N>
class matrix {
public:
    std::vector<std::vector<T>> mat;

    matrix() {
        mat = std::vector<std::vector<T>>(M, std::vector<T>(N, 0));
    }

    T& operator()(const size_t &x, const size_t &y) {
        return mat[x][y];
    }

    const T& operator()(const size_t &x, const size_t &y) const {
        return mat[x][y];
    }

    const size_t getRows() const {
        return mat.size();
    }

    const size_t getCols() const {
        if (mat.size() > 0)
            return mat[0].size();
        else
            return 0;
    }

    const bool isSquare(const matrix<T, M, N>& m) const {
        return m.getRows() == m.getCols();
    }

    void getCofactor(matrix<T, M, N>& m, matrix<T, M, N>& temp, int p, int q, int n) {
        int i = 0, j = 0;
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++) {
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

    const T det() {
        assert(isSquare(*this));
        int n = getRows();
        T D = 0;
        if (n == 1)
            return mat[0][0];
        matrix<T, M, N> temp;
        int sign = 1;  
        for (int f = 0; f < n; f++) {
            getCofactor(*this, temp, 0, f, n);
            D += sign * mat[0][f] * temp.det();
            sign = -sign;
        }
        return D;
    }
};
