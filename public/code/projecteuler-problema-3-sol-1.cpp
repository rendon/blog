long long max_prime_factor(long long n)
{
    long long max = 1, d;

    for (d = 2; d < n; d++) {
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
