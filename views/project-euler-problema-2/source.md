<!-- vim: set spelllang=es_mx: -->

# ProjectEuler - Problema 2
2016-02-18 2024-05-07 #algorithms #data-structures #post

La sucesión de fibonacci es muy famosa y es común encontrarla en problemas de concursos de programación. Un problema clásico para ejemplificar la [recursión](/?p=35) y uno de los problemas más sencillos para demostrar el poder de la *programación dinámica*. El inventor de dicha secuencia fue el matemático italiano [Leonardo de pisa](http://en.wikipedia.org/wiki/Fibonacci) y se define de la siguiente forma.

$ \large f(n) =  \begin{cases} 0 & \text{si n = 0} \\ 1 & \text{si n = 1} \\\\ f(n - 1) + f(n - 2) & \text{si n > 1} \end{cases} $

Existe mucha información al respecto, la cual recomiendo explorar si desean ampliar su conocimiento a cerca de esta función.

## Problema
<blockquote>
  Cada término en la sucesión de Fibonacci se obtiene al sumar los dos términos anteriores. Empezando con 1 y 2, los primeros 10 términos serían:
<br><br>
    1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...
<br><br>
Considerando los términos en la sucesión de Fibonacci cuyos valores no exceden los cuatro millones, encuentre la suma de los términos que son pares.
</blockquote>

Versión original: [Problem 2](http://projecteuler.net/index.php?section=problems&id=2)

## Análisis

Identificamos bien que es lo que se nos esta pidiendo. Se pide generar cierta cantidad de términos de la sucesión de Fibonacci empezando con 1 y 2 y terminar cuando encontremos un término que exceda los cuatro millones, el cual no deberá ser tomado en cuenta. De estos términos debemos tomar aquellos que son pares y sumarlos, la suma es el valor que estamos buscando.

Generar términos de la sucesión de Fibonacci no representa ninguna complicación por lo que pasamos directamente a la implementación de la solución.


## Solución

A pesar de que la sucesión de Fibonacci es recursiva por naturaleza es bien sabido que la implementación iterativa es por mucho más eficiente que su correspondiente recursiva. A continuación mi implementación.


```c
#include <stdio.h>

int main()
{
    int a = 1, b = 2, c = 3;
    int sum = 2;	// second term

    while (c < 4000000) {
        a = b;
        b = c;
        c = a + b;

        if (c % 2 == 0) { // even ?
            sum += c;
        }
    }

    printf("sum = %d\n", sum);
    return 0;
}

```


## Conclusión
Hay mucho de que hablar de la sucesión de Fibonacci, mucho se ha escrito sobre ella y no estaría mal si investigan por su cuenta. Pueden empezar por implementar la versión recursiva. Hasta la próxima.

## Referencias

<table border="0">
    <tr>
        <td>[1]</td><td>[http://en.wikipedia.org/wiki/Fibonacci_number](http://en.wikipedia.org/wiki/Fibonacci_number)</td>
    </tr>
    <tr>
        <td>[2]</td><td>[http://projecteuler.net](http://projecteuler.net)</td>
    </tr>
</table>
