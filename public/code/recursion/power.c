int power(int a, int n)
{
    if (n == 0)
        return 1;
    if (n%2 == 0)
        return square(power(a, n / 2)); // square(a) returns a^2
    else
        return a * power(a, n - 1);
}
