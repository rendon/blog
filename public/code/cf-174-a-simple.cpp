#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    else
        return gcd(b, a%b);
}

int main(int argc, char *argv[])
{
    int p, phi, count = 0;

    cin >> p;

    phi = p - 1;
    for (int i = 1; i < phi; i++)
        if (gcd(phi, i) == 1)
            count++;

    if (p == 2)
        count++;

    cout << count << endl;

    return EXIT_SUCCESS;
}
