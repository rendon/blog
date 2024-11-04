<!-- vim: set spelllang=es_MX: -->

---
tags:
    - math
    - algorithms
    - post
created: 2016-02-18
updated: 2024-05-07
---
# Big Mod

En una división entera se distinguen cuatro elementos, *dividendo*, *divisor*, *cociente* y *módulo o residuo*. Donde el dividendo es la cantidad a dividir, divisor el valor contra el cual se hará la división, el resultado es el cociente y residuo la cantidad sobrante. Por ejemplo, sea *n* = 123 y *d* = 4, al realizar la división obtenemos un cociente *c* igual a 30 y un residuo *r* igual a 3.

El objetivo de este documento es describir dos métodos que permiten calcular el módulo de una división entera. Usted podría pensar ¿que difícil es eso? y yo le contesto, no es difícil, pero para números muy muy grandes resulta que no es tan sencillo. Con los métodos que aquí les presento ustedes serán capaces de obtener el módulo de divisiones enteras con un dividendo de cientos, miles, o incluso millones de dígitos.

La mayoría de los lenguajes de programación tienen un operador para la operación módulo, en C/C++, Java, C# y similares el operador es el signo de porcentaje.

```int n = 123 % 4; // n = 3```

Pues resulta que en algún momento de tu vida como programador te encuentras con el problema de calculas residuos, pero no cualquier cosa, sino más o menos algo como 

<blockquote>
  Dados tres números enteros *b*, *p* y *m* donde 0 <= *b, p* <= 2^30 y 1 <= *m* <= 2^30, calcular el residuo de *(b^p) % m*.
</blockquote>

O también

<blockquote>
  Sea *n* un número de hasta un millón de dígitos, representado como una cadena de caracteres y un entero *m* tal que *m* es mayor que cero y *m* es menor o igual a 2^63 - 1, determinar si *n* es divisible sobre *m*.
</blockquote>

Interesante he!. Y bien, a pesar de que a primera vista estos dos problemas pueden parecer muy complejos en este artículo les mostrare como emplear algo de teoría de números que nos permitan dar solución a estos problemas de una forma muy sencilla y elegante, tan solo unas cuantas líneas de código.

## Módulo cuando conocemos los factores del dividendo

Si conocemos los factores del dividendo entonces se puede aplicar la siguiente propiedad para el módulo:

$$(abc) \bmod m = ((a \bmod m)(b \bmod m)(c\bmod m))\bmod m$$

Por ejemplo, sea *n = 105* y *m = 9*, entonces n%m = ((3 % 9) * (5 % 9) * (7 % 9)) % 9 = (3 * 4 * 2) % 9 = 24 % 9 = 6, lo cual es fácil comprobar. Cuando tenemos un número *b* elevado a una potencia *p* sabemos que eso equivale a multiplicar la base *b* un número de veces igual a *p*, por ejemplo, 3^4 = 3 * 3 * 3 * 3. Entonces podemos aplicar **(1)** para el primer problema *(b^p) % m*. Como *p* puede ser muy grande entonces usamos [exponenciación por cuadrados repetidos](/recursion). Una posible implementación en C es la siguiente.


```c
int modpow(int b, int p, int m)
{
    int pow = 1;

    while (p > 0) {
        if (p % 2 == 1) {
            pow = (pow * b) % m;
        }

        b = (b * b) % m;
        p /= 2;
    }

    return pow % m;
}

```

## Modulo cuando conocemos los dígitos del dividendo

Del teorema fundamental de la numeración tenemos que cualquier numero se puede obtener a partir de sus dígitos de siguiente manera:

$$N=d\_{n-1}b^{n-1} +...+ d\_{1}b^{1} + d\_{0}b^{0}$$

Véase [como convertir números a cadenas y viceversa para más información](/numeros-y-cadenas). Además existe otra propiedad similar a  pero para la suma.

$$(a + b + c) \bmod m = ((a \bmod m) + (b \bmod m) + (c \bmod m)) \bmod m$$

Con toda esta información podemos formular el siguiente algoritmo que resuelve el problema que estamos tratando.

```c
int mod(const char* digits, int m)
{
    int i, n = 0;
    int size = strlen(digits);

    for (i = 0; i < size; i++) {
        n = n * 10 + digits[i] - '0';
        n = n % m;
    }

    return n % m;
}

```

Si el resultado que devuelve esta función es cero entonces *n* es divisible por *m*.

A continuación les dejo algunos problemas para que practiquen:

- [Big mod](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=5&page=show_problem&problem=310)
- [ProjectEuler.net problema 97](http://projecteuler.net/problem=97)
- [PowerDigit](http://community.topcoder.com/stat?c=problem_statement&pm=4515)

## Conclusión

La teoría de números es muy interesante, es posible dar solución a problemas complejos de manera muy elegante.

## Referencias

1. Art of Programming Contest, 2ed, Ahmed Shamsul Arefin
2. Elementary Number Theory With Applications, 2ed, Thomas Koshy
