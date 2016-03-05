Arrays.fill(X, 0);

while (true) {
    for (int i = 0; i < n; i++) {
        double sum = M[i][n]; // b_n

        for (int j = 0; j < n; j++)
            if (j != i)
                sum -= M[i][j] * X[j];

        // Update x_i to use in the next row calculation
        X[i] = 1/M[i][i] * sum;   
    }
