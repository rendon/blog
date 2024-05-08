<!-- vim: set spelllang=es_MX: -->

# ProjectEuler - Problema 3
2016-02-18 2024-05-07 #algorithms #data-structures #post

Dentro del conjunto de los [números naturales](http://es.wikipedia.org/wiki/N%C3%BAmero_natural)(denotado por $\mathbb{N}$) pueden distinguirse básicamente dos tipos de números: primos y compuestos. Los primos son aquellos que son únicamente divisibles(división exacta) con uno y consigo mismos mientras que los compuestos reciben su nombre debido a que se obtienen como un producto de números primos, factores, los cuales pueden aparecer más de una vez en el producto.

Ejemplos de números primos son 2, 3, 5, 7, 19, etc. Por su parte 4, 6, 9 y 20 son ejemplos de números compuestos. Un algoritmos simple para comprobar la primalidad de un número es apegándose a su definición, es decir, comprobar la divisibilidad de $n$ con $d = 2$  hasta $n - 1$. Próximamente dedicaré un artículo para hablar sobre números primos, por ahora procedamos con el tema de este artículo.

## Problema
<blockquote>
  Los factores primos de 13195 son 5, 7, 13 y 29.<br>
  Cual es el factor primos mas grande del número 600851475143?
</blockquote>

Versión original: [Problem 3](http://projecteuler.net/index.php?section=problems&id=3) projecteuler.net


## Análisis

Sea $n$ = 600851475143 y $p_{1}, p_{2}, ..., p_{k}$ los factores primos de $n$. El problema se puede replantear como, dado $n$ encuentre los factores primos $p_{1}, p_{2}, ..., p_{k}$ y retorne el mayor de ellos, $p_{k}$. Note que $n$ es divisible entre sus factores, además, si dividimos $n$ sucesivamente entre todos sus factores $n$ se vuelve 1, por ejemplo si $n $ = 30, sus factores primos son 2, 3 y 5, y por lo tanto 30/2 = 15, 15/3 = 5 y 5/5 = 1. Con estas observaciones podemos formular una primera solución:



```pas
MaxPrimeFactor1(n)
  max = 1
  for d = 2 to n - 1
    if n MOD d == 0
      max = d
      while n MOD d == 0
        n = n/d
      if n > 1
        max = n
  return max

```

La línea 7 y 8 son importantes, en caso de que $n$ no se convierta en 1 es porque $n$ es primo y por tanto `max` toma el valor de n.

Para el valor de $n$ de este problema el algoritmo anterior corre bien en tiempo, sin embargo podemos mejorarlo. Sabemos que todos los primos, con excepción del dos, son números impares y por lo tanto después del dos solo es necesario probar la divisibilidad con los números impares, con esta observación el algoritmos queda así:


```pas
MaxPrimeFactor2(n)
  max = 1
  if (n MOD 2 == 0)
    max = 2
    while n MOD 2 == 0
      n = n / 2
  d = 3
  while d < n
    if n MOD d == 0
      max = d
      while n MOD d == 0
        n = n/d
    d = d + 2
  if n > 1
    max = n
  return max

```

Las líneas de código se han incrementado pero para el número de cálculos se reducirá prácticamente a la mitad. Una observación más, si $p = n/q$ y $q$ divide a $n$ entonces $p$ también divide a $n$, esta observación nos permite buscar factores primos hasta `sqrt(n)` y ya no hasta $n - 1$ ya que si $n$ es divisible entre $p$ entonces $n = p * q$ y si $q$ es menor que $p$ entonces $n$ ya habría sido dividido previamente entre $q$ al menos $p$ veces, líneas 11 y 12 en `MaxPrimeFactors2(n)`. La nueva versión del algoritmo queda así:


```pas
MaxPrimeFactor3(n)
  max = 1
  if (n MOD 2 == 0)
    max = 2
    while n MOD 2 == 0
      n = n / 2
  d = 3
  while d <= sqrt(n)
    if n MOD d == 0
      max = d
      while n MOD d == 0
        n = n/d
    d = d + 2
  if n > 1
    max = n
  return max

```

Es posible agregar algunas optimizaciones más, aunque las cosas se tornan un poco más complicadas con cada una de ellas. Por ejemplo, sabemos que buscamos factores primos y hasta ahora estamos probando con 2 y después con números impares desde 3 hasta `sqrt(n)`, sin embargo muchos de esos números impares no son primos, por ende, si solo probaremos la divisibilidad con números primos la tarea se realizaría a mayor velocidad. Le dejo la implementación de esta última observación como ejercicio al lector.

## Solución [código]
A continuación las implementaciones de los algoritmos en lenguaje C:

### Versión 1

```c
long long max_prime_factor(long long n)
{
    long long max = 1, d;

    for (d = 2; d < n; d++) {
        if (n % d == 0) {
            max = d;

            while (n % d == 0) {
                n /= d;
            }
        }
    }

    if (n > 1) {
        max = n;
    }

    return max;
}

```

### Versión 2

```c
long long max_prime_factor(long long n)
{
    long long max = 1, d;

    if (n % 2 == 0) {
        max = 2;

        while (n % 2 == 0) {
            n /= 2;
        }
    }

    for (d = 3; d < n; d += 2) {
        if (n % d == 0) {
            max = d;

            while (n % d == 0) {
                n /= d;
            }
        }
    }

    if (n > 1) {
        max = n;
    }

    return max;
}

```

### Versión 3

```c
long long max_prime_factor(long long n)
{
    long long max = 1, d;

    if (n % 2 == 0) {
        max = 2;

        while (n % 2 == 0) {
            n /= 2;
        }
    }

    for (d = 3; d * d <= n; d += 2) {
        if (n % d == 0) {
            max = d;

            while (n % d == 0) {
                n /= d;
            }
        }
    }

    if (n > 1) {
        max = n;
    }

    return max;
}

```

## Ejecución y rendimiento

El comando `time` me muestra los siguientes resultados:


```txt
[22:47:47]rendon@debian~$ time ./pe_3_v1 && time ./pe_3_v2 && time ./pe_3_v3
6857

real	0m0.003s
user	0m0.004s
sys	0m0.000s
6857

real	0m0.003s
user	0m0.004s
sys	0m0.000s
6857

real	0m0.003s
user	0m0.000s
sys	0m0.004s

```

Las diferencias en tiempo parecen ser insignificantes, bueno, esto es porque solo estamos trabajando con un número, no obstante, intenten calcular el máximo factor primo desde 2 hasta 10,000 y verán que las diferencias se aprecian mejor.


## Conclusión
La factorización de números enteros es para nada trivial, hasta ahora no existe un algoritmo para la factorización de enteros con complejidad polinomial. El algoritmo de cifrado [RSA](http://es.wikipedia.org/wiki/RSA) se sustenta en esta complejidad.

## Referencias
<table border="0">
    <tr>
      <td>[1]</td><td>Thomas Koshy, Elementary number theory with applications</td>
    </tr>
    <tr>
      <td>[2]</td><td>[http://en.wikipedia.org/wiki/Integer_factorization](http://en.wikipedia.org/wiki/Integer_factorization)</td>
    </tr>
</table>


## Descargas
<table border="0">
    <tr>
        <td>Solución v1:</td> <td> [v1.c](v1.c) </td>
    </tr>
    <tr>
        <td>Solución v2:</td> <td> [v2.c](v2.c) </td>
    </tr>
    <tr>
        <td>Solución v3:</td> <td> [v3.c](v3.c) </td>
    </tr>
</table>
