int gcd2(int a, int b) // a > b
{
    int tmp;

    while (b != 0) {
        tmp = b;
        b = a % b;
        a = tmp;
    }

    return a;
}
