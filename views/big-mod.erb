"=========== Meta ============
"StrID : 31
"Title : Big Mod
"Slug  : big-mod
"Cats  : Algoritmos,Matemática,Programación
"Tags  : ACM, aritmetica modular, big mod, modpow, modulo, projecteuler, topcoder
"=============================
"EditType   : post
"EditFormat : Markdown
"TextAttach : wpid1157-wpid-vimpress_537694a6_mkd.txt
"========== Content ==========
[php]initialize();[/php]

En una división entera se distinguen cuatro elementos, <em>dividendo</em>, <em>divisor</em>, <em>cociente</em> y <em>módulo o residuo</em>. Donde el dividendo es la cantidad a dividir, divisor el valor contra el cual se hara la división, el resultado es el cociente y residuo la cantidad sobrante. Por ejemplo, sea <em>n</em> = 123 y <em>d</em> = 4, al realizar la división obtenemos un cociente <em>c</em> igual a 30 y un residuo <em>r</em> igual a 3.

El objetivo de este documento es describir dos metodos que permiten calcular el módulo de una división entera. Usted podría pensar ¿que difícil es eso? y yo le contesto, no es dificil, pero para numeros muy muy grandes resulta que no es tan sencillo. Con los metodos que aquí les presento ustedes serán capaces de obtener el módulo de divisiones enteras con un dividendo de cientos, miles, o incluso millones de dígitos.

La mayoría de los lenguajes de programación tienen un operador para la operación módulo, en C/C++, Java, C# y similares el operador es el signo de porcentaje.

<pre lang="c">int n = 123 % 4; // n = 3</pre>

Pues resulta que en algun momento de tu vida como programador te encuentras con el problema de calculas residuos, pero no cualquier cosa, sino más o menos algo como 

<blockquote>
  Dados tres números enteros <em>b</em>, <em>p</em> y <em>m</em> donde 0 <= <em>b, p</em> <= 2^30 y 1 <= <em>m</em> <= 2^30, calcular el residuo de <em>(b^p) % m</em>.
</blockquote>

O también

<blockquote>
  Sea <em>n</em> un número de hasta un millon de dígitos, representado como una cadena de caracteres y un entero <em>m</em> tal que <em>m</em> es mayor que cero y <em>m</em> es menor o igual a 2^63 - 1, determinar si <em>n</em> es divisible sobre <em>m</em>.
</blockquote>

Interesante heee!. Y bien, a pesar de que a primera vista estos dos problemas pueden parecer muy complejos en este artículo les mostrare como emplear algo de teoría de números que nos permitan dar solución a estos problemas de una forma muy sencilla y elegante, tan solo unas cuantas líneas de código.

#Módulo cuando conocemos los factores del dividendo

Si conocemos los factores del dividendo entonces se puede aplicar la siguiente propiedad para el módulo:

[php]equation("(abc) \bmod m = ((a \bmod m)(b \bmod m)(c\bmod m))\bmod m", "multiply_mod");[/php] 

Por ejemplo, sea <em>n = 105</em> y <em>m = 9</em>, entonces n%m = ((3 % 9) * (5 % 9) * (7 % 9)) % 9 = (3 * 4 * 2) % 9 = 24 % 9 = 6, lo cual es fácil comprobar. Cuando tenemos un número <em>b</em> elevado a una potencia <em>p</em> sabemos que eso equivale a multiplicar la base <em>b</em> un número de veces igual a <em>p</em>, por ejemplo, 3^4 = 3 * 3 * 3 * 3. Entonces podemos aplicar <strong>(1)</strong> para el primer problema <em>(b^p) % m</em>. Como <em>p</em> puede ser muy grande entonces usamos <a href="/recursion" target="_blank">exponenciación por cuadrados repetidos</a>. Una posible implementación en C es la siguiente.


<pre lang="c">
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
</pre>


#Modulo cuando conocemos los dígitos del dividendo

Del teorema fundamental de la numeración tenemos que cualquier numero se puede obtener a partir de sus dígitos de siguiente manera:

[php]equation("N=d\_{n-1}b^{n-1} +...+ d\_{1}b^{1} + d\_{0}b^{0}", "tfn");[/php]

Véase <a href="/numeros-y-strings/" target="_blank">como convertir números a string y viceversa para más información</a>. Además existe otra propiedad similar a [php]ref("multiply_mod");[/php] pero para la suma.

[php]equation("(a + b + c) \bmod m = ((a \bmod m) + (b \bmod m) + (c \bmod m)) \bmod m", "sum_mod");[/php]

Con toda esta información podemos formular el siguiente algoritmo que resuelve el problema que estamos tratando.

<pre lang="c">
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
</pre>

Si el resultado que devuelve esta función es cero entonces <em>n</em> es divisible por <em>m</em>.

A continuación les dejo algunos problemas para que practiquen:

- [Big mod](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=5&page=show_problem&problem=310" targer="_blank")
- [ProjectEuler.net problema 97](http://projecteuler.net/problem=97" targer="_blank")
- [PowerDigit](http://community.topcoder.com/stat?c=problem_statement&pm=4515" target="_target")

#Conclusión

La teoría de números es muy interesante, es posible dar solución a problemas complejos de manera muy elegante.

#Referencias

<table border="0">
<tr><td>[1]</td><td><em>Art of Programming Contest</em>, 2ed, Ahmed Shamsul Arefin</td></tr>
<tr><td>[2]</td><td><em>Elementary Number Theory With Applications</em>, 2ed, Thomas Koshy</td></tr>
</table>

[php]finalize();[/php]
