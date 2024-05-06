// inicialmente se llama  a perm con el total de elementos en el conjunto
void perm(int n)
{
    int i, tmp;
    // Caso base: A[0..N-1] contiene la permutacion, podemos hacer lo
    // que sea con ella, que tal imprimirla :)
    if (n == 0) { 
        for (i = 0; i < N; i++)
            printf("%d", A[i]);
        printf("\n");
    } else {
        for (i = 0; i < n; i++) { // Para cada elemento en A
            tmp = A[n - 1];       // Mandamos el elemento i al final
            A[n - 1] = A[i];      // del arreglo con un intercambio
            A[i] = tmp;
            
            // Ahora generamos las permutaciones
            // de los n - 1 elementos restantes
            perm(n - 1);    
        
            tmp = A[n - 1]; // Regresamos el elemento i a su lugar
            A[n - 1] = A[i];
            A[i] = tmp;
        }
    }
}
