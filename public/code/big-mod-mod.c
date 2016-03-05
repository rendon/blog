int mod(const char* digits, int m)
{
    int i, n = 0;
    int size = strlen(digits);

    for (i = 0; i < size; i++) {
        n = n * 10 + digits[i] - '0';
        n = n % m;
    }

    return n % m;
}
