<!-- vim: set spelllang=es_mx: -->

# ProjectEuler - Problema 1
2016-02-18 2024-05-07 #algorithms #data-structures #post

Un saludo a todos. Les comento que he decidido empezar a escribir sobre las soluciones de los problemas que a veces resuelvo, esto con el fin de mejorar mi capacidad de análisis, así como mi habilidad pedagogica.

## Problema

<blockquote>
  Si listamos todos los números naturales menores a 10 que son multiplos de 3 o de 5, obtenemos 3, 5, 6 y 9. La suma de estos multiplos es 23.
  Encuentre la suma de todos los multiplos de 3 o de 5 menores que 1000.
</blockquote>
Versión original: [Problem 1](http://projecteuler.net/index.php?section=problems&id=1)


## Análisis
<p>Lo primero que es necesario identificar  es que se  nos esta pidiendo. Nuestra tarea consiste en encontrar todos aquellos números enteros en el rango de 1 a 999 que sean divisibles ya sea por 3 ó bien por 5, es decir, aquellos números que tienen división exacta con estos dos números. O bien, en otras palabras, para todo numero 1<= i < 1000, <i>i <b>mod</b> 3 = 0</i> ó <i>i <b>mod</b> 5 = 0</i>, donde <b>mod</b> corresponde al residuo de una división entera.</p>

## Solución [código]
Existe más de una forma de dar solución a este problema:

<p>La manera más sencilla es iterar en el rango dado con <i>i</i> y realizar la operación modulo con 3 y 5 y si alguna de ellas resulta verdadera entonces sumamos <i>i</i> a la suma total.</p>

Una segunda aproximación al problema un poco más eficiente consiste en calcular todos los múltiplos de 3 y de 5 menores que 1000 y almacenarlos formando dos conjuntos. Note que ciertos valores pueden ser múltiplos de 3 tanto como de 5, siendo 15 un claro ejemplo, por lo tanto es necesario eliminar las repeticiones(A unión B) para que no se altere la suma final. Después de esto simplemente sumamos todos los elementos de ambos conjuntos.

A continuación se muestran las implementaciones de estas dos estrategias.


```c
#include <stdio.h>
int main()
{
    int i, sum = 0;

    for (i = 3; i < 1000; i++) {
        if (i % 3 == 0 || i % 5 == 0) {
            sum += i;
        }
    }

    printf("%d\n", sum);
    return 0;
}

```


```c
#include <iostream>
#include <set>

using namespace std;

int main()
{
    set<int> M;
    set<int>::iterator it;
    int i, sum = 0;

    for (i = 3; i < 1000; i += 3) {
        M.insert(i);
    }

    for (i = 5; i < 1000; i += 5) {
        M.insert(i);
    }

    for (it = M.begin(); it != M.end(); it++) {
        sum += *it;
    }

    cout << sum << endl;
    return 0;
}

```

## Conclusión

La divisibilidad entre números enteros es determinada por la operación modulo. Recuerde que un conjunto no tiene elementos repetidos.

En la segunda implementación he usado la clase `set` de C++ con dos propósitos: facilitar la implementación y para que aquellos que no la conozcan puedan empezar a ver su utilidad. Hasta la próxima.

## Referencias
<ol>
  <li>- Mi solución. ;)</li>
</ol>
