int to_int(string number)
{
    int n = 0;
    for (int i = 0; i < int(number.length()); i++)
        n = n * 10 + (number[i] - '0');

    return n;
}
