#include <iostream>
#include <cassert>
#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 50005;
const long long mod = 98765431;
long long C[N];
class Matrix {
public:
    Matrix()
    {
        _rows = 0;
        _cols = 0;
    }

    Matrix(int r, int c)
    {
        _rows = r;
        _cols = c;
    }

    long long * operator[](int index)
    {
        return _m[index];
    }

    Matrix operator*(Matrix &B) const
    {
        int i, j, k;
        Matrix C(rows(), B.cols());
        for (i = 0; i < rows(); i++) {
            for (j = 0; j < B.cols(); j++) {
                C[i][j] = 0;
                for (k = 0; k < cols(); k++)
                    C[i][j] = (C[i][j] + _m[i][k] * B[k][j]) % mod;
            }
        }

        return C;
    }

    Matrix& operator=(Matrix right)
    {
        _rows = right.rows();
        _cols = right.cols();
        for (int i = 0; i < right.rows(); i++)
            for (int j = 0; j < right.cols(); j++)
                _m[i][j] = right[i][j];
        return *this;
    }

    Matrix operator^(int p) const 
    {
        p--;
        Matrix a = *this;
        Matrix b = *this;
        while (p > 0) {
            if (p % 2 == 1)
                a = a * b;
            p /= 2;
            b = b * b;
        }

        return a;
    }

    int cols() const { return _cols; }
    int rows() const { return _rows; }

    void print()
    {
        for (int i = 0; i < rows(); i++) {
            printf("|");
            for (int j = 0; j < cols(); j++)
                printf("%lld ", _m[i][j]);
            printf("|\n");
        }
    }
private:
    int _rows, _cols;
    long long  _m[5][5];
};

int main(int argc, char **argv)
{
    long long  n, t, sum = 0;
    int i;

    scanf("%lld %lld", &n, &t);
    for (i = 0; i < n; i++) {
        scanf("%lld", &C[i]);
        sum += C[i];
    }

    sum %= mod;

    Matrix m(2, 2);
    m[0][0] = -1;
    m[0][1] = 1;
    m[1][0] = 0;
    m[1][1] = n - 1;

    Matrix b = m^t;
    long long x = (sum * b[0][1]) % mod;
    for (i = 0; i < n; i++) {
        if (t % 2 == 1) {
            printf("%lld\n", (x - C[i] + mod) % mod);
        } else {
            printf("%lld\n", (x + C[i]) % mod);
        }
    }

    return 0;
}
