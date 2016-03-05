int fibonacci(unsigned int n)
{
    int a = 0, b = 1, c = 1, i;
    if (n == 0)
        return 0;

    if (n == 1 || n == 2)
        return 1;

    for (i = 3; i <= n; i++) {
        a = b;
        b = c;
        c = a + b;
    }

    return c;
}
