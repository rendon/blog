int gcd(int a, int b) // a > b
{
    if (b == 0) return a;
    else return gcd(b, a % b);
}
