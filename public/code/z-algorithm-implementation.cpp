Z[0] = n;
int l = 0, r = 0;
for (int k = 1; k < n; k++) {
    if (r < k) {
        l = r = k;
        while (S[r] == S[r-l])
            r++;
        Z[k] = r - l;
    } else {
        int b = r - k;
        int j = k - l; // j is k'
        if (Z[j] < b) {
            Z[k] = Z[j];
        } else if (Z[j] > b) {
            Z[k] = b;
        } else {
            l = k;
            r = k + b;
            while (S[r] == S[r-l])
                r++;
            Z[k] = r - l;
        }
    }
}
