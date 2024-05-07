<p>El día de hoy estuve resolviendo <a href="http://www.spoj.com/problems/SUMSUMS/" target="_blank">este problema</a> y les quiero compartir mi solución y un poco del análisis para poder resolverlo.</p>

<p>Debido a las restricciones del problema, realizar la simulación no es factible, así que habrá que buscar otra forma. Empecemos por analizar el ejemplo de entrada:</p>

<pre>
4   5   1
6   5   9
14  15  11
26  25  29
54  55  51
106 105 109
214 215 211
</pre>

<p>Calculemos la suma de cada fila:</p>

<pre>
4  + 5  + 1     = 10
6  + 5  + 9     = 20
14 + 15 + 11    = 40
26 + 25 + 29    = 80
54 + 55 + 51    = 160
106+ 105+ 109   = 320
214+ 215+ 211   = 640
</pre>


<p>¿Notan el patrón? ¿No? Bueno, otro ejemplo:</p>

<pre>
7      4      5      3   
12     15     14     16  
45     42     43     41  
126    129    128    130 
387    384    385    383 
1152   1155   1154   1156
</pre>

<p>Y las sumas son:</p>

<pre>
7    +  4    +  5    +  3    = 19
12   +  15   +  14   +  16   = 57
45   +  42   +  43   +  41   = 171
126  +  129  +  128  +  130  = 513
387  +  384  +  385  +  383  = 1539
1152 +  1155 +  1154 +  1156 = 4617
</pre>

<p>Las sumas a partir de la segunda fila corresponden la suma de la fila anterior multiplicada por $n - 1$, donde $n$ es el número de columnas (el número de vacas que tiene el granjero Juan), en nuestro segundo ejemplo $n = 4$ y por lo tanto $3 * 19 = 57$, $3 * 57 = 171$, etc.</p>

<p>Ahora veamos como calculamos el resultado de una de la primera columna:</p>

$1539 - 513 + 171 - 57 + 19 - 7 = 1152$
$513 - 171 + 57 - 19 + 7 = 387$

<p>Con un poco de observación llegamos a que el resultado final de  una vaca $i$ es igual a:</p>
![Formula para obtener el resultado final](/omi-tg-sumando-sumas/sumsums_formulas.png)

<p>Donde $k = n - 1$, $s1$ es la suma de la primera fila y $C_{i}$ es el valor inicial de la vaca $i$.</p>

<p>El problema en estas expresiones es que $t$ es demasiado grande como para iterar y calcular el resultado, intente simplificar el problema pero no llegue a nada, hice una <a href="http://math.stackexchange.com/questions/614236/is-there-a-formula-for-a-sequence-like-kt-kt-1kt-2-k2-k1k" target="_blank">pregunta</a> en <a href="http://math.stackexchange.com" target="_blank">math.stackexchange.com</a> y me proporcionaron una formula que en efecto responde a mi pregunta, sin embargo, no pude aplicar esa formula a este problema ya que las propiedades de módulo no se aplican con las divisiones.</p>

<p>Después de investigar llegue a que necesitamos utilizar la siguiente matriz:</p>

![Matriz base](/omi-tg-sumando-sumas/sumsums_matrix.png)

<p>Elevamos esta matriz a la potencia $t$ y podremos encontrar el valor que buscamos en $M_{0,1}$. Para que la exponenciación funcione en tiempo debemos utilizar el método de <a href="https://es.wikipedia.org/wiki/Exponenciaci%C3%B3n_binaria" target="_blank">exponenciación binaria</a> que tiene una complejidad $O(log_{2} n)$, siendo $n$ el valor del exponente.</p>

<p>Sin más aquí les dejo mi código:</p>

Embed: `sol.cpp`

<p>Hay que tener mucho cuidado con los desbordamientos en los tipos de datos y con valores negativos, en este caso en particular ayuda mucho utilizar un tipo `long long`, sin embargo, esto no es suficiente para todos los casos, es por ellos que hay que realizar la operación módulo en varios puntos.</p>

<p>Espero que les sea de utilidad. Hasta la próxima.</p>
