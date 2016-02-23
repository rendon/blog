"=========== Meta ============
"StrID : 69
"Title : ProjectEuler: Problema 3
"Slug  : projecteuler-problema-3
"Cats  : Algoritmos,Matemática,Programación
"Tags  : division exacta, divisores, factores primos, números compuestos, números naturales, projecteuler
"=============================
"EditType   : post
"EditFormat : markdown
"TextAttach : wpid1253-vimpress_5377a9b7_mkd.txt
"========== Content ==========

Dentro del conjunto de los <a href="http://es.wikipedia.org/wiki/N%C3%BAmero_natural">números naturales</a>(denotado por $$\mathbb{N}$$) pueden distinguirse básicamente dos tipos de números: primos y compuestos. Los primos son aquellos que son únicamente divisibles(división exacta) con uno y consigo mismos mientras que los compuestos reciben su nombre debido a que se obtienen como un producto de números primos, factores, los cuales pueden aparecer más de una vez en el producto.

Ejemplos de números primos son 2, 3, 5, 7, 19, etc. Por su parte 4, 6, 9 y 20 son ejemplos de números compuestos. Un algoritmos simple para comprobar la primalidad de un número es apegándose a su definición, es decir, comprobar la divisibilidad de $$n$$ con $$d = 2$$  hasta $$n - 1$$. Próximamente dedicaré un artículo para hablar sobre números primos, por ahora procedamos con el tema de este artículo.


#Problema
<blockquote>
    Los factores primos de 13195 son 5, 7, 13 y 29.<br>
    Cual es el factor primos mas grande del número 600851475143?    
</blockquote>

Versión original: <a href="http://projecteuler.net/index.php?section=problems&id=3">Problem 3</a> projecteuler.net


#Análisis

Sea $$n$$ = 600851475143 y $$p_{1}, p_{2}, ..., p_{k}$$ los factores primos de $$n$$. El problema se puede replantear como, dado $$n$$ encuentre los factores primos $$p_{1}, p_{2}, ..., p_{k}$$ y retorne el mayor de ellos, $$p_{k}$$. Note que $$n$$ es divisible entre sus factores, además, si dividimos $$n$$ sucesivamente entre todos sus factores $$n$$ se vuelve 1, por ejemplo si $$n $$ = 30, sus factores primos son 2, 3 y 5, y por lo tanto 30/2 = 15, 15/3 = 5 y 5/5 = 1. Con estas observaciones podemos formular una primera solución:


<pre lang="pascal" theme="slate" line="1">
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
</pre>


La línea 7 y 8 son importantes, en caso de que $$n$$ no se convierta en 1 es porque $$n$$ es primo y por tanto <code>max</code> toma el valor de n.

Para el valor de $$n$$ de este problema el algoritmo anterior corre bien en tiempo, sin embargo podemos mejorarlo. Sabemos que todos los primos, con excepción del dos, son números impares y por lo tanto después del dos solo es necesario probar la divisibilidad con los números impares, con esta observación el algoritmos queda así:

<pre lang="pascal" theme="slate" line="1">
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
</pre>


Las líneas de código se han incrementado pero para el número de cálculos se reducirá prácticamente a la mitad. Una observación más, si $$p = n/q$$ y $$q$$ divide a $$n$$ entonces $$p$$ también divide a $$n$$, esta observación nos permite buscar factores primos hasta <code>sqrt(n)</code> y ya no hasta $$n - 1$$ ya que si $$n$$ es divisible entre $$p$$ entonces $$n = p$$ * $$q$$ y si $$q$$ es menor que $$p$$ entonces $$n$$ ya habría sido dividido previamente entre $$q$$ al menos $$p$$ veces, líneas 11 y 12 en <code>MaxPrimeFactors2(n)</code>. La nueva versión del algoritmo queda así:

<pre lang="pascal" theme="slate" line="1">
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
</pre>


Es posible agregar algunas optimizaciones más, aunque las cosas se tornan un poco más complicadas con cada una de ellas. Por ejemplo, sabemos que buscamos factores primos y hasta ahora estamos probando con 2 y después con números impares desde 3 hasta <code>sqrt(n)</code>, sin embargo muchos de esos números impares no son primos, por ende, si solo probaremos la divisibilidad con números primos la tarea se realizaría a mayor velocidad. Le dejo la implementación de esta última observación como ejercicio al lector.

#Solución [código]
A continuación las implementaciones de los algoritmos en lenguaje C:

##Versión 1

<pre lang="c" theme="slate" line="1">
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
</pre>

##Versión 2

<pre lang="c" theme="slate" line="1">
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
</pre>

##Versión 3

<pre lang="c" theme="slate" line="1">
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
</pre>

#Ejecución y rendimiento

El comando <code>time</code> me muestra los siguientes resultados:

<pre theme="slate">
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
</pre>

Las diferencias en tiempo parecen ser insignificantes, bueno, esto es porque solo estamos trabajando con un número, no obstante, intenten calcular el máximo factor primo desde 2 hasta 10,000 y verán que las diferencias se aprecian mejor.


#Conclusión
La factorización de números enteros es para nada trivial, hasta ahora no existe un algoritmo para la factorización de enteros con complejidad polinomial. El algoritmo de cifrado <a href="http://es.wikipedia.org/wiki/RSA">RSA</a> se sustenta en esta complejidad.


#Referencias
<table border="0">
    <tr>
        <td>[1]</td><td>Thomas Koshy, Elementary number theory with applications</td>
    </tr>
    <tr>
        <td>[2]</td><td>http://en.wikipedia.org/wiki/Integer_factorization</td>
    </tr>
</table>


#Descargas
<table border="0">
    <tr>
        <td>Solución: Versión 1</td> <td><a href="../../files/src/pe_3_v1.c">pe_3_v1.c</a></td>
    </tr>
    <tr>
        <td>Solución: Versión 1</td> <td><a href="../../files/src/pe_3_v2.c">pe_3_v2.c</a></td>
    </tr>
    <tr>
        <td>Solución: Versión 1</td> <td><a href="../../files/src/pe_3_v3.c">pe_3_v3.c</a></td>
    </tr>
</table>
