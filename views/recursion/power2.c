int power2(int a, int n)
{
    int p = 1;
    if (n == 0)
        return 1;

    while (n > 0) {
        if (n % 2 == 1) {
            p *= a;
            n--;
        } else {
            p *= p;
            n /= 2;
        }
    }

    return p;
}
