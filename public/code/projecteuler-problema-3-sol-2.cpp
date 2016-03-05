long long max_prime_factor(long long n)
{
    long long max = 1, d;

    if (n % 2 == 0) {
        max = 2;

        while (n % 2 == 0) {
            n /= 2;
        }
    }

    for (d = 3; d < n; d += 2) {
        if (n % d == 0) {
            max = d;

            while (n % d == 0) {
                n /= d;
            }
        }
    }

    if (n > 1) {
        max = n;
    }

    return max;
}
