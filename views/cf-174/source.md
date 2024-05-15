#  CF-174
2016-03-04 2024-05-06 #algorithms #data-structures #post

I took part in Codeforces 174 Division II and here are my solutions for some of the problems.

## [A. Cows and primitive roots](https://codeforces.com/contest/284/problem/A)
### Complicated version:
Stick to the problem definition and do the tests, we need a modpow function. Complexity: $O(n^2)$.

```cpp
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
```

This problem took me about an hour, I am out of practice, I didn't remember well how to implement the modpow function and I wanted to do it by myself.

### Simplified version:
I found this formula in [Primitive roots](https://en.wikipedia.org/wiki/Primitive_root_modulo_n#Finding_primitive_roots):

<blockquote>
The number of primitive roots modulo n, if there are any, is equal to
$\varphi\left(\varphi\left(n\right)\right)$
</blockquote>

Where $\varphi\left(n\right)$ is defined as: How many numbers $m$($1 \leq m < n$) are relatively prime to $n$, i.e. $gcd(n, m) = 1$. Since $p$ in the problem is guaranteed to be prime then $\varphi\left(p\right) = p - 1$ and we only need to compute $\varphi\left(p - 1\right)$, this can be done easily in $O(n)$.

```cpp
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
```

## [B. Cows and Poker Game](https://codeforces.com/contest/284/problem/B)
Count the occurrences of 'F's and 'A's. If the occurrences of 'I' is 0 the answer is the number of occurrences of 'A's, if the occurrences of 'I' is exactly 1 the answer is 1, in other case the answer is 0. This is the solution that I sent during the contest. Complexity: $O(n)$.

```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int BUFFER_SIZE = 200 * 1024;
char buffer[BUFFER_SIZE];

int main(int argc, char *argv[])
{
    int n, i, A = 0, F = 0, ans = 0;
    scanf("%d\n", &n);

    for (i = 0; i < n; i++)
        buffer[i] = getchar();

    for (i = 0; i < n; i++)
        if (buffer[i] == 'A')
            A++;
        else if (buffer[i] == 'F')
            F++;

    for (i = 0; i < n; i++) {
        if ((buffer[i] == 'I') && ((A + F) + 1 == n)) {
            ans++;
        } else if ((buffer[i] == 'A') && ((A + F) == n)) {
            ans++;
        }
    }

    cout << ans << endl;

    return EXIT_SUCCESS;
}
```

## [C. Cows and Sequence](https://codeforces.com/contest/284/problem/C)
I wasn't able to solve this problem during the contest, the idea described here is from the editorial and my implementation is based on [Efremov_licesos](https://codeforces.com/profile/Efremov_licesos)'s solution.

**Q**: If the solution is described in the editorial Why to write about it again? 

**A**: Because sometimes the solutions described in the editorials are very abstract and it's almost always hard to understand other contestants' solutions(many contestants are very intelligent but their code is cryptic and ugly. No offense).

If the operations were only 1 and 2 you can solve the problem keeping the sum of the additions to existing elements or new elements. The hard part is operation 3, How to know what is the value of the last element after some aditions? The idea is to use two arrays, an array B to store the new values($k_i$), and an array A to store the additions(operation 1). A picture is worth a thousand words.

![](/cf-174/cf174d2_c_0.png)

The value of the last element is `(A[n] * n) - (A[n] * (n-1)) + B[n]`, or graphically.

![](/cf-174/cf174d2_c_1.png)

I hope that with this context, the code is more understandable.
Complexity: $O(n)$.

```cpp
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
```

### D. Not solved yet.

### E. Not solved yet.

That was it for CF 174. Until next time!
