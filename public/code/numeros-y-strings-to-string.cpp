string to_string(int n)
{
    string digits = "";

    while (n > 0) {
        digits += (char)(n % 10 + '0');
        n /= 10;
    }

    reverse(digits.begin(), digits.end());
    return digits;
}
