bool binary_search(int A[], int v, int l, int u)
{
    int m = (l + u)/2;
    if (l > u)
        return false;
    if (v == A[m])
        return true;
    else if(v < A[m])
        return binary_search(A, v, l, m - 1);
    else
        return binary_search(A, v, m + 1, u);
}
