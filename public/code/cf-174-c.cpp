#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

int A[200010];
int B[200010];

int main(int argc, char **argv)
{
    int size = 0;
    int type, i, n, a, x, k;
    long long sum = 0;

    scanf("%d", &n);

    B[size++] = 0;
    for (i = 0; i < n; i++) {
        scanf("%d", &type);

        if (type == 1) {
            scanf("%d %d", &a, &x);
            A[a] += x;
            sum += a * x;
        } else if (type == 2) {
            scanf("%d", &k);
            B[size++] = k;
            sum += k;
        } else {
            sum -= A[size] * size;
            sum += A[size] * (size - 1);
            A[size-1] += A[size];
            A[size] = 0;
            sum -= B[--size];
        }

        printf("%.10lf\n", (double)sum/size);
    }
    return EXIT_SUCCESS;
}
