<p>Un saludo a todos. Les comento que he decidido empezar a escribir sobre las soluciones de los problemas que a veces resuelvo, esto con el fin de mejorar mi capacidad de análisis, así como mi habilidad pedagogica.</p>

## Problema

<blockquote>
  <p>Si listamos todos los números naturales menores a 10 que son multiplos de 3 o de 5, obtenemos 3, 5, 6 y 9. La suma de estos multiplos es 23.</p>
  <p>Encuentre la suma de todos los multiplos de 3 o de 5 menores que 1000.</p>
</blockquote>
<p>Versión original: <a href="http://projecteuler.net/index.php?section=problems&id=1">Problem 1</a></p>


## Análisis
<p>Lo primero que es necesario identificar  es que se  nos esta pidiendo. Nuestra tarea consiste en encontrar todos aquellos números enteros en el rango de 1 a 999 que sean divisibles ya sea por 3 ó bien por 5, es decir, aquellos números que tienen división exacta con estos dos números. O bien, en otras palabras, para todo numero 1<= i < 1000, <i>i <b>mod</b> 3 = 0</i> ó <i>i <b>mod</b> 5 = 0</i>, donde <b>mod</b> corresponde al residuo de una división entera.</p>

## Solución [código]
<p>Existe más de una forma de dar solución a este problema:</p>

<p>La manera más sencilla es iterar en el rango dado con <i>i</i> y realizar la operación modulo con 3 y 5 y si alguna de ellas resulta verdadera entonces sumamos <i>i</i> a la suma total.</p>

<p>Una segunda aproximación al problema un poco más eficiente consiste en calcular todos los múltiplos de 3 y de 5 menores que 1000 y almacenarlos formando dos conjuntos. Note que ciertos valores pueden ser múltiplos de 3 tanto como de 5, siendo 15 un claro ejemplo, por lo tanto es necesario eliminar las repeticiones(A unión B) para que no se altere la suma final. Después de esto simplemente sumamos todos los elementos de ambos conjuntos.</p>

<p>A continuación se muestran las implementaciones de estas dos estrategias.</p>

Embed: `a.c`

Embed: `b.c`

## Conclusión

<p>La divisibilidad entre números enteros es determinada por la operación modulo. Recuerde que un conjunto no tiene elementos repetidos.</p>

<p>En la segunda implementación he usado la clase `set` de C++ con dos propósitos: facilitar la implementación y para que aquellos que no la conozcan puedan empezar a ver su utilidad. Hasta la próxima.</p>

## Referencias
<ol>
  <li>- Mi solución. ;)</li>
</ol>
