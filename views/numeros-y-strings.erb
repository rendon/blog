"=========== Meta ============
"StrID : 43
"Title : Números y Strings
"Slug  : numeros-y-strings
"Cats  : Sin categoría
"Tags  : 
"=============================
"EditType   : post
"EditFormat : Markdown
"TextAttach : wpid1413-vimpress_5376b6fc_mkd.txt
"========== Content ==========
[php]initialize();[/php]

[php]section("Introducción");[/php]

Cada vez que utilizamos números ya sea escribiéndolos en un cuaderno, en la computadora, leyéndolos de uno u otro medio realmente lo que ocurre es que leemos una secuencia de símbolos (en nuestro caso dígitos) a los que según nuestro acervo cognitivo le damos un significado y un valor. Las computadoras trabajan de manera similar, sabemos bien que la computadora no <em>"piensa"</em>, por ende necesitamos ayudarle un <em>mucho</em> para que de igual forma dada una secuencia de caracteres (nuevamente me refiero a los dígitos) tome el valor que numérico que representa dicha cadena.

Supongan que tienen un número entero y a partir de él deseamos obtener sus dígitos, sí, poder manejar cada uno de los dígitos del número en cuestión de manera individual, y viceversa, dado un string (cadena de caracteres) necesitamos tomar su valor numérico.  

La mayoría de los lenguajes de alto nivel incorporan métodos predefinidos dentro de sus bibliotecas estándar. Java por ejemplo tiene dentro de la clase `Integer` el método `parseInt(String str)`, C# cuenta con ` System.Convert.ToInt32(str) `, en lenguaje C existe la función `int atoi (const char *str)`, etc. Para descomponer un número en sus dígitos no conozco un método que haga exactamente eso, es decir que te regrese, por decir algo, un arreglo de enteros que contenga cada uno de los dígitos. Más sin embargo si existen métodos que transforman un número en un string, el proceso inverso. Ya teniendo el string lo demás es muy simple.

Si bien podemos limitarnos a simplemente emplear dichos métodos cabe decir que es importante saber cual es el procedimiento que hace posible estas operaciones, nunca se sabe cuando se puede ocupar, es por eso que aquí trato de explicar como funciona esto, al menos la forma que yo conozco.

[php]section("Descomponer número en dígitos");[/php]

El algoritmo para este problema es muy sencillo y se basa en divisiones y residuos(véase <a href="/big-mod" target="_blank">Big Mod</a> para más información. Veamos un ejemplo.

[php]figure('descomposicion_digitos', 'Descomposición de un número en dígitos', 'descomposicion_digitos', 'png', 'ES');[/php]


Se observa que si bien obtenemos los dígitos estos se encuentran en orden inverso, por ello invertimos el orden de los dígitos al final del ciclo en el siguiente código:


<pre lang="cpp" theme="slate" line="1">
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
</pre>

En este código se ha utilizado el número 10 como divisor lo cual es así ya que la base numérica es decimal. Cambien el 10 por un 2 y vean que sucede... ¿A caso son números binarios lo que veo?, ¿que tal con otras bases en vez de 2 ó 10?

[php]subsection("Obtener valor numérico a partir de un string");[/php]

Ahora vamos con el caso opuesto, tenemos los dígitos en una cadena de caracteres y de ahí obtener el valor correspondiente en entero.

El algoritmo que se describe a continuación no es más que el que dicta el <a href="http://es.wikipedia.org/wiki/Sistema_de_numeraci%C3%B3n#Teorema_Fundamental_de_la_numeraci.C3.B3n" target="_blank">teorema fundamental de la numeración</a>, que en pocas palabras dice que cualquier número en base <strong><em>b</em></strong> puede ser obtenido a partir de sus dígitos según la siguiente fórmula( esta no es una definición completa).

[php]equation("N = d\_{n - 1}b^{n - 1} + ... + d\_{1}b^{1} + d\_{0}b^{0}", "tfn");[/php]


Donde $$n$$ es la cantidad de dígitos menos 1 ya que los exponentes se empiezan a numerar a partir del 0 (cero) y $$d\_i$$ es cada uno de los dígitos . Veamos un ejemplo


$$! \large 354 = 3 * 10^2 + 5 * 10^1 + 4 * 10^0$$ 


Ahora que tenemos las bases podemos pasar al algoritmo en cuestión.


<pre lang="cpp" theme="slate" line="1">
int to_int(string number)
{
    int n = 0;
    for (int i = 0; i < int(number.length()); i++)
        n = n * 10 + (number[i] - '0');

    return n;
}
</pre>


Como podrán ver son algoritmos muy sencillos y fáciles de entender. Es recomendable aprender muy bien estos algoritmos ya que nunca sabemos cuando los podemos utilizar, además de que siempre es bueno saber el cómo de las cosas :).

Por último solo les comento que estos algoritmos son útiles en cierto tipo de problemas, especialmente de concursos de programación donde se pone a prueba el dominio de este tipo de algoritmos elementales, generalmente problemas clasificados como <em>fácil</em>, <em>Level 1</em> o <em>Appetizer</em>. Aquí les dejo unos dos ejemplos.


<blockquote>
Un número palíndromo es aquel que se puede leer igual en ambas direcciones. El palíndromo más grande formado como producto de 2 número de dos dígitos es 9009 = 91 * 99.
<br><br>
Encuentre el palíndromo numérico más grande formado por el producto de 2 números de tres dígitos.
</blockquote>
<p align="right"><em><a href="http://www.projecteuler.net" target="_blank">projecteuler.net</a></em> Problem 4.



<blockquote>
El número decimal, 585<sub>10</sub> = 1001001001<sub>2</sub>(binario), es un palíndromo en ambas bases.
<br><br>
Encuentre la suma de todos los número, menores que un millón, que son palíndromos en base 10 y en base 2.
<br><br>
(Por favor note que el número palíndromo no debe incluir ceros a la izquierda).


</blockquote>
<p align="right"><em><a href="http://www.projecteuler.net" target="_blank">projecteuler.net</a></em> Problem 36.


[php]section("Referencias");[/php]

<ul>
    <li> <a href="http://es.wikipedia.org/wiki/Sistema_de_numeraci%C3%B3n" target="_blank">Sistema de numeración</a></li>
    <li> <a href="http://en.wikipedia.org/wiki/Horner_scheme" target="_blank">Horner scheme</a></li>
</ul>

[php]finalize();[/php]
