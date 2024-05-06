int pascal(int i, int j)
{
    if (i == j || j == 1) return 1;
    return pascal(i - 1, j - 1 + pascal(i - 1, j);
}
