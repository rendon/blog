// R is a copy of the adjacency matrix.
for (int k = 0; k < n; k++) {
    R[k][k] = true;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (R[i][k] && R[k][j]) {
                R[i][j] = true;
            }
        }
    }
}
