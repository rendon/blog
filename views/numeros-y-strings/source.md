<!-- vim: set spelllang=es_MX: -->
# Números y cadenas
2016-02-18 2024-05-07 #algorithms #data-structures #post

## Introducción

Cada vez que utilizamos números ya sea escribiéndolos en un cuaderno, en la computadora, leyéndolos de uno u otro medio realmente lo que ocurre es que leemos una secuencia de símbolos (en nuestro caso dígitos) a los que según nuestro acervo cognitivo le damos un significado y un valor. Las computadoras trabajan de manera similar, sabemos bien que la computadora no *"piensa"*, por ende necesitamos ayudarle un *mucho* para que de igual forma dada una secuencia de caracteres (nuevamente me refiero a los dígitos) tome el valor que numérico que representa dicha cadena.

Supongan que tienen un número entero y a partir de él deseamos obtener sus dígitos, sí, poder manejar cada uno de los dígitos del número en cuestión de manera individual, y viceversa, dado un string (cadena de caracteres) necesitamos tomar su valor numérico.  

La mayoría de los lenguajes de alto nivel incorporan métodos predefinidos dentro de sus bibliotecas estándar. Java por ejemplo tiene dentro de la clase `Integer` el método `parseInt(String str)`, C# cuenta con `System.Convert.ToInt32(str)`, en lenguaje C existe la función `int atoi (const char *str)`, etc. Para descomponer un número en sus dígitos no conozco un método que haga exactamente eso, es decir que te regrese, por decir algo, un arreglo de enteros que contenga cada uno de los dígitos. Más sin embargo si existen métodos que transforman un número en un string, el proceso inverso. Ya teniendo el string lo demás es muy simple.

Si bien podemos limitarnos a simplemente emplear dichos métodos cabe decir que es importante saber cual es el procedimiento que hace posible estas operaciones, nunca se sabe cuando se puede ocupar, es por eso que aquí trato de explicar como funciona esto, al menos la forma que yo conozco.

## Descomponer número en dígitos

El algoritmo para este problema es muy sencillo y se basa en divisiones y residuos(véase [Big Mod](/big-mod) para más información. Veamos un ejemplo.

![Descomposición de un número en dígitos](/numeros-y-strings/descomposicion_digitos.png)


Se observa que si bien obtenemos los dígitos estos se encuentran en orden inverso, por ello invertimos el orden de los dígitos al final del ciclo en el siguiente código:


```cpp
string to_string(int n)
{
    string digits = "";

    while (n > 0) {
        digits += (char)(n % 10 + '0');
        n /= 10;
    }

    reverse(digits.begin(), digits.end());
    return digits;
}

```

En este código se ha utilizado el número 10 como divisor lo cual es así ya que la base numérica es decimal. Cambien el 10 por un 2 y vean que sucede... ¿A caso son números binarios lo que veo?, ¿que tal con otras bases en vez de 2 ó 10?

### Obtener valor numérico a partir de un string

Ahora vamos con el caso opuesto, tenemos los dígitos en una cadena de caracteres y de ahí obtener el valor correspondiente en entero.

El algoritmo que se describe a continuación no es más que el que dicta el [teorema fundamental de la numeración](http://es.wikipedia.org/wiki/Sistema_de_numeraci%C3%B3n#Teorema_Fundamental_de_la_numeraci.C3.B3n), que en pocas palabras dice que cualquier número en base ***b*** puede ser obtenido a partir de sus dígitos según la siguiente fórmula( esta no es una definición completa).

$$N = d\_{n - 1}b^{n - 1} + ... + d\_{1}b^{1} + d\_{0}b^{0}$$


Donde $n$ es la cantidad de dígitos menos 1 ya que los exponentes se empiezan a numerar a partir del 0 (cero) y $d\_i$ es cada uno de los dígitos . Veamos un ejemplo


$ \large 354 = 3 * 10^2 + 5 * 10^1 + 4 * 10^0$ 


Ahora que tenemos las bases podemos pasar al algoritmo en cuestión.


```cpp
int to_int(string number)
{
    int n = 0;
    for (int i = 0; i < int(number.length()); i++)
        n = n * 10 + (number[i] - '0');

    return n;
}

```

Como podrán ver son algoritmos muy sencillos y fáciles de entender. Es recomendable aprender muy bien estos algoritmos ya que nunca sabemos cuando los podemos utilizar, además de que siempre es bueno saber el cómo de las cosas :).

Por último solo les comento que estos algoritmos son útiles en cierto tipo de problemas, especialmente de concursos de programación donde se pone a prueba el dominio de este tipo de algoritmos elementales, generalmente problemas clasificados como *fácil*, *Level 1* o *Appetizer*. Aquí les dejo unos dos ejemplos.


<blockquote>
  Un número palíndromo es aquel que se puede leer igual en ambas direcciones. El palíndromo más grande formado como producto de 2 número de dos dígitos es 9009 = 91 * 99.
  <br><br>
  Encuentre el palíndromo numérico más grande formado por el producto de 2 números de tres dígitos.
</blockquote>
<p align="right">*[projecteuler.net](http://www.projecteuler.net)* Problem 4.


<blockquote>
  <p>El número decimal, 585<sub>10</sub> = 1001001001<sub>2</sub>(binario), es un palíndromo en ambas bases.</p>
  <br><br>
Encuentre la suma de todos los número, menores que un millón, que son palíndromos en base 10 y en base 2.
  <br><br>
  (Por favor note que el número palíndromo no debe incluir ceros a la izquierda).
</blockquote>
<p align="right">*[projecteuler.net](http://www.projecteuler.net)* Problem 36.


## Referencias

<ul>
    <li> [Sistema de numeración](http://es.wikipedia.org/wiki/Sistema_de_numeraci%C3%B3n)</li>
    <li> [Horner scheme](http://en.wikipedia.org/wiki/Horner_scheme)</li>
</ul>
