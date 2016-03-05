#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

long long modpow(long long b, int p, long long m)
{
    long long mod = 1;
    while (p) {
        if (p%2 == 1)
            mod = (mod * b)%m;
        b = (b * b)%m;
        p /= 2;
    }

    return mod;
}

int main(int argc, char *argv[])
{
    int count = 0;
    long long p, x;
    cin >> p;

    for (x = 2; x < p; x++) {
        bool isPrimitive = true;
        for (int y = 1; y <= p - 2; y++)
            if (modpow(x, y, p) == 1)
                isPrimitive = false;

        if (modpow(x, p - 1, p) != 1)
            isPrimitive = false;

        if (isPrimitive) {
            count++;
        }
    }

    if (p == 2)
        count++;

    cout << count << endl;

    return EXIT_SUCCESS;
}
