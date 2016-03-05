long long z(long long n)
{
    long long zeros = 0;
    long long  k = 5;

    while (k <= n) {
        zeros += n / k;
        k *= 5;
    }

    return zeros;
}
