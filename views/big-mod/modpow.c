int modpow(int b, int p, int m)
{
    int pow = 1;

    while (p > 0) {
        if (p % 2 == 1) {
            pow = (pow * b) % m;
        }

        b = (b * b) % m;
        p /= 2;
    }

    return pow % m;
}
