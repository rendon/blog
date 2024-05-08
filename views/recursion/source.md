<!-- vim: set spelllang=es_MX: -->

# Recursión
2016-02-18 2024-05-07 #algorithms #data-structures #post

La recursión es una técnica de diseño de algoritmos muy útil que permite formular soluciones de forma natural a un gran número de problemas. En este documento trato de dar una breve introducción a este tema mediante algunos sencillos ejemplos. Se proporciona una breve descripción del problema, el análisis de la solucion recursiva y además el código de la solución con el fin de que al lector le sea posible poner en práctica cada algoritmo de manera inmediata.


<blockquote>
En ciencias de la computación, la recursión es una técnica de diseño de algoritmos donde un método, procedimiento o función hace llamadas a sí mismo, evitando caer en un ciclo infinito, ya que el algoritmo debe terminar en algun momento, una caracteristica de todo algoritmo.
</blockquote>


Un algoritmo recursivo consiste en simplificar un problema en cada llamada recursiva y que a su vez tiene una solución muy parecida a la original.


Como ya se dijo, nuestro algoritmo debe terminar en algún momento, es decir, debe existir un estado donde el problema es lo bastante simple para ser resuelto directamente sin necesidad de seguir con las llamadas recursivas. A este estado se le conoce como *caso base*. Cada algoritmo recursivo debe tener al menos un caso base.


Los algoritmos recursivos están muy relacionados con otra técnica de diseño de algoritmos: divide y vencerás. Un algoritmo divide y venceras consite en dividir un problem complejo en subproblemas del mismo tipo más simples, resolver cada uno de ellos y por último combinar las subsoluciones para dar lugar a la solución del problema original. Más adelante veremos un ejemplo.


## Ejemplos de problemas recursivos

Si una imagen dice más que mil palabras entonces un código también.


## Factorial

La función factorial tiene la siguiente definición:


$$n!= \begin{cases} 1 & \text{si n = 0} \\\\ n(n - 1)!& \text{si n > 0} \end{cases} $$


Antes de proceder con la implementación veamos un ejemplo para ver como se comporta esta función. Sea *n = 4*.


```
4! = 4 * 3! = 4 * (3 * 2!) = 4 * (3 * (2 * 1!)) = 4 * (3 * (2 * (1 * 0!))) = 4 * (3 * (2 * (1 * 1))) = 24.
```


Veamos ahora una implementación de esta función en C.


```c
int factorial(int n)
{
    if (n == 0) return 1;
    else return n * factorial(n - 1);
}

```

La condición en la línea 2 es nuestro caso base, el problema se puede resolver directamente sin necesidad de continuar con la recursión. Más adelate cuando generemos permutaciones vera la relación que existe entre la función factorial y el número de permutaciones.


## Máximo común divisor

En matemáticas el máximo común divisor de dos o más números diferentes de cero es el máximo entero que divide a estos mismos de manera exacta, es decir, con residuo igual a cero. A continuación se describe el método de euclides para determinar el MCD de dos números.


Dados dos números $a$ y $b$ tal que $a>b$, el método de Euclides para encontrar el MCD de estos dos números consiste en obtener el residuo de la división entera de *a* sobre *b*, $r = a \bmod b$, ahora *a* pasa a ser *b* y *b* pasa a ser *r*. Estos pasos se repiten hasta encontrar un residuo igual a cero. El último residuo diferente de cero es el MCD que buscamos.

Un ejemplo siempre ayuda. Sea $a=489$ y $b = 324$.

1. $r = 489  \bmod  324 = 165$ ahora $a = 324$ y $b = 165$.
2. $r = 324  \bmod  165 = 159$, ahora $a = 165$ y $b = 159$.
3. $r = 165  \bmod  159 = 6$, ahora $a = 159$ y $b = 6$.
4. $r = 159  \bmod  6 = 3$, ahora $a = 6$ y $b = 3$.
5. $r = 6  \bmod  3 = 0$, ahora $a = 3$ y $b = 0$.

En este punto *b* vale cero y por tanto el algoritmo ha terminado, el último residuo diferente de cero es 3 y por ende el MCD(489, 324) = 3. Veamos una implementación recursiva en C.


```c
int gcd(int a, int b) // a > b
{
    if (b == 0) return a;
    else return gcd(b, a % b);
}

```

## Exponenciación rápida

Dados dos números $a$ y $b$, $a^b$ es equivalente a multiplicar $a$ por sí misma $n$ veces. En términos matemáticos esto es exponenciación. Se pide un algoritmo que obtenga $a^n$ de manera eficiente.

Al parecer es un problema muy simple, basta con iterar *n* veces multiplicando *a* por sí misma, resultando en un algoritmo lineal respecto a *n*.

Un algoritmo lineal tiene un buen desempeño sin embargo existen problemas donde donde esto no es suficiente, uno de esos problemas es calcular el modulo (`%` en C/C++, Java, y otros lenguajes) de un número $a^n \bmod k$ donde $a^n$ es un número muy muy grande. Este problema lo abordaré en otro artículo, de momento enfoquemonos en la exponenciación.

El algoritmo recursivo que aquí se describe se base en la regla de exponenciación que nos dice que $(a^n)^m = a^{nm}$ con la cual podemos reformular $a^n$ como $(a^2)^{n/2} (n \bmod 2)$. Aprovechando esta propiedad se puede diseñar un algoritmo de complejidad $O(\log_{2} n)$.


```c
int power(int a, int n)
{
    if (n == 0)
        return 1;
    if (n%2 == 0)
        return square(power(a, n / 2)); // square(a) returns a^2
    else
        return a * power(a, n - 1);
}

```

Establecemos el caso base en la línea 3 gracias a que por definición cualquier número elevado a una potencia cero es igual a la unidad.

## Sucesión de Fibonacci

Leonardo de Pisa, matemático italiano que vivió en el siglo XIII, también conocido como Fibonacci, describió una sucesión numérica cuyos primeros dos valores son 0 y 1. Cada elemento posterior se obtiene como la suma de los dos elementos anteriores, así los primeros 7 elementos de la sucesión son:

0, 1, 1, 2, 3, 5, 8, ...


Fibonacci describió dicha sucesión como la solución al siguiente problema.

<blockquote>
"Un criador de conejos, en cierto mes no tiene ningún conejo(mes cero), al mes compra un par de conejos(macho y hembra) bebes(mes 1), al mes los conejos ya son adultos y la coneja se embaraza(mes 2), al mes la pareja pare un par de conejos(macho y hembra nuevamente) y ahora se tienen dos parejas de conejos(mes 3), la coneja de la pareja original se vuelve a embarazar y al siguiente mes pare otro par de conejos(macho y hembra, siempre sera así :D), y ya tenemos 3 pares de conejos(mes 4). La coneja de la pareja original vuelve a embarazarse y ademas la coneja de la primera partición, que ya es adulta, se embaraza también. Al mes cada pareja pare una pareja de conejos y ahora la población asciende a 5 parejas(mes 5). Las dos conejas del paso anterior se vuelven a embarazar y la coneja de la segunda partición ya es adulta y también se se embaraza dando lugar a 3 nuevos pares de conejos al siguiente mes que sumados a los ya existentes ahora tenemos 8 parejas(mes 6), y así sucesivamente."
</blockquote>

En términos matemáticos esta sucesión se describe con la siguiente función:

$$f(n) = \begin{cases} 0 & \text{si n = 0} \\\\ 1 & \text{si n = 1} \\\\ f(n - 1) + f(n - 2) & \text{si n > 1} \end{cases}$$


```c
int fibonacci(unsigned int n)
{
    if (n == 0 || n == 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

```

Note que el parámetro es de tipo `unsigned int` para asegurar que *n* siempre será mayor o igual a cero(el compilador nos advertirá), según lo especifica la función de fibonacci.

## Triangulo de pascal

El [triangulo de pascal](http://es.wikipedia.org/wiki/Tri%C3%A1ngulo_de_Pascal) es un arreglo triangular que contiene en la fila *n* los coeficientes binomiales que resultan al desarrollar $(a + b)^n$. Las primeras 6 filas de este triangulo son:

<pre>
1
1 1
1 2 1
1 3 3 1
1 4 6 4 1
1 5 10 10 5 1
```


Inicialmente se empieza con un solo elemento, el 1 el punto más alto del triángulo. Para cada renglón posterior se coloca un 1 en cada extremo del renglón y el resto de los términos se calculan como la suma del elemento superior izquierdo más el elemento superior, es decir `P(i, j) = P(i - 1, j - 1) + P(i - 1, j)`. Nos encontramos nuevamente con una función recursiva. Sabemos que el valor en la primer y última columna de cada fila es igual a 1 y con ello formulamos nuestro caso base como `P(i, 1) = 1` y `P(i, j) == 1` si `i = j`.

La código que se muestra a continuación calcula el valor ubicado en la fila *i*, columna *j*  del triángulo de pascal. Cabe decir que esta versión del algoritmo es muy ineficiente pero se muestra por cuestiones didácticas.


```c
int pascal(int i, int j)
{
    if (i == j || j == 1) return 1;
    return pascal(i - 1, j - 1 + pascal(i - 1, j);
}

```
    
<!--Búsqueda-->
## Búsqueda binaria

Sea *A[0...n -1]* un arreglo de elementos ordenados, existe un algoritmo de búsqueda que permite encontrar(si existe) un elemento en el arreglo con complejidad O(log (n)). Este algoritmo es conocido como búsqueda binaria ya que en cada paso reduce el campo de búsqueda a la mitad. Para este ejemplo *A* contiene números enteros aunque puede ser cualquier tipo de dato, salvo algunas pequeñas diferencias.

La búsqueda binaria trabaja más o menos así: sea *v* el valor que buscamos y *A* un arreglo con los  elementos sobre los que realizaremos la búsqueda, ordenados en forma ascendente(en orden descendente no implica mayor complicación). Nos colocamos a la mitad del arreglo que contiene los elementos, es decir *A[A.size/2]*, comparamos el valor que se encuentra en esta posición con *v*, y pueden suceder tres casos, si son iguales entonces ya encontramos lo que andabamos buscando y termina la búsqueda de manera satisfactoria, si *v* es mayor entonces el valor que buscamos posiblemente se encuentra en la segunda mitad, es decir *A[A.size/2 + 1]* a *A[A.size - 1]*, y podemos estar seguros de que no se encuentra en la primera mitad gracias a que los elementos están ordenados. Si *v* es menor entonces descartamos la segunda mitad dejando a la primera mitad como la posible contenedora de *v*. Hecho esto hemos reducido el campo de búsqueda a la mitad, se descarta una de las mitades y repetimos el mismo procedimiento con la mitad restante, hasta encontrar el elemento que buscamos o hasta que comprobar que el elemento buscado no se encuentra en *A*.

Quizás una imagen ayuda un poco a entender este procedimiento.

![Búsqueda Binaria](/recursion/binary_search.png)

Una posible implementación de este algoritmo de forma recursiva es la siguiente.


```c
bool binary_search(int A[], int v, int l, int u)
{
    int m = (l + u)/2;
    if (l > u)
        return false;
    if (v == A[m])
        return true;
    else if(v < A[m])
        return binary_search(A, v, l, m - 1);
    else
        return binary_search(A, v, m + 1, u);
}

```

## Permutaciones

Dada una lista de elementos sin que se repita ninguno de ellos se pide encontrar el número de permutaciones de dichos elementos y mostrar dichas permutaciones.

Una permutación no es mas que el reordenamiento de un cierto número de objetos. Cuando se pide generar todas las permutaciones de un conjunto de elementos(al hablar de conjunto se sabe que no debe haber elementos repetidos) el problema se reduce a generar todas las reordenaciones posibles tales que no halla dos reordenaciones idénticas. Por ejemplo, el conjunto `{1, 2, 3}` tiene 6 permutaciones que son `{1, 2, 3}, {1, 3, 2}, {2, 1, 3}, {2, 3, 1}, {3, 1, 2} ,{3, 2, 1}`.

El problema nos solicita dos cosas, primero, el número de permutaciones, y segundo, cuales son dichas permutaciones. La primera petición es muy fácil, ya lo hemos hecho anteriormente, se trata de la función factorial que desarrollamos como primer ejemplo de recursión que calcula ni más ni menos el número de permutaciones para un conjunto de *n* elementos.

La segunda parte del problema es un poquito más complicada, así que procedamos con el análisis del problema. Veamos el las permutaciones para conjuntos de 1, 2 y 3 elementos.

<table class="article_table">
    <tr>
        <td>{1} = </td> <td>{1}</td>
    </tr>
    <tr>
        <td>{1, 2} = </td> <td>{1, 2}, {2, 1}</td>
    </tr>
    <tr>
        <td>{1, 2, 3} =  </td> <td>{1, 2, 3}, {1, 3, 2}, <br>{2, 1, 3}, {2, 3, 1}, <br>{3, 1, 2}, {3, 2, 1}</td>
    </tr>
</table>


Para un elemento la única permutación es sí mismo. Para dos elementos colocamos el primer elemento seguido por el segundo para la primera permutación y después invertimos el orden para obtener la segunda permutación. Ponga atención en las permutaciones del conjunto de 3 elementos. Note que primero se generan todas las permutaciones que empiezan con el primer elemento, después las que empiezan con el segundo elemento y de igual manera para el tercer elemento. Además note que existen dos permutaciones diferentes que empiezan con el primer elemento, dos que empiezan con el segundo elemento y dos para el tercero, una para cada permutación de los dos elementos restantes. 

Esto muestra que podemos reducir el problema a un algoritmo recursivo que para *n* elementos se deben generar todas las permutaciones formadas por todas las permutaciones de *n - 1* elementos precedidas del elemento n.


```c
// inicialmente se llama  a perm con el total de elementos en el conjunto
void perm(int n)
{
    int i, tmp;
    // Caso base: A[0..N-1] contiene la permutacion, podemos hacer lo
    // que sea con ella, que tal imprimirla :)
    if (n == 0) { 
        for (i = 0; i < N; i++)
            printf("%d", A[i]);
        printf("\n");
    } else {
        for (i = 0; i < n; i++) { // Para cada elemento en A
            tmp = A[n - 1];       // Mandamos el elemento i al final
            A[n - 1] = A[i];      // del arreglo con un intercambio
            A[i] = tmp;
            
            // Ahora generamos las permutaciones
            // de los n - 1 elementos restantes
            perm(n - 1);    
        
            tmp = A[n - 1]; // Regresamos el elemento i a su lugar
            A[n - 1] = A[i];
            A[i] = tmp;
        }
    }
}

```
```
```

En las líneas 14 a 16 hacemos que el elemento actual pase al final del arreglo mediante un intercambio, dicho intercambio obviamente es para no perder el elemento que esta en la última posición. Esta sección del código corresponden a "anteponer" cada uno de los n elementos y la línea 20 corresponde a generar todas las permutaciones de los *n - 1* elementos restantes. Quizás notaran que realmente no anteponemos los elementos sino que más bien lo ponemos al final lo cual no altera el funcionamiento del algoritmo. Las permutaciones que genera este algoritmo están desordenadas y es necesario ordenarlos si así lo necesitamos. Existen algoritmos que generan permutaciones "casi" ordenadas pero se los dejo de tarea por si les interesa.

<!--Conclusión-->
## Recursión vs Iteración

Todo algoritmo recursivo puede ser implementado en forma iterativa, y viceversa. Esta afirmación no fue muy aceptada por mí en un principio, pero ahora, con un poquito más de entendimiento, les puedo decir que es verdad. Para que se convenzan veamos como lucen las versiones iterativas de algunos problemas antes mencionados.


### Factorial


```c
int factorial2(int n)
{
    int f = 1;
    for (int i = 2; i <= n; i++) {
        f *= i;
    }

    return f;
}

```

### MCD


```c
int gcd2(int a, int b) // a > b
{
    int tmp;

    while (b != 0) {
        tmp = b;
        b = a % b;
        a = tmp;
    }

    return a;
}

```

### Fibonacci


```c
int fibonacci(unsigned int n)
{
    int a = 0, b = 1, c = 1, i;
    if (n == 0)
        return 0;

    if (n == 1 || n == 2)
        return 1;

    for (i = 3; i <= n; i++) {
        a = b;
        b = c;
        c = a + b;
    }

    return c;
}

```

### Exponenciación rápida


```c
int power2(int a, int n)
{
    int p = 1;
    if (n == 0)
        return 1;

    while (n > 0) {
        if (n % 2 == 1) {
            p *= a;
            n--;
        } else {
            p *= p;
            n /= 2;
        }
    }

    return p;
}

```

Algunos no son tan fáciles de portar a iterativo. De manera interna la recursión trabaja con una pila, cada llamada recursiva significa crear una copia de todos los valores actuales en la función y ponerlos en la pila, para después cuando termine la ejecución de la llamada recursiva se puedan restaurar los valores tal y como estaban. En muchos casos es necesario utilizar una pila explícitamente para su versión iterativa.


## Otros problemas recursivos

Existen muchos problemas que se definen recursivamente, algunos de ellos son: 

<ol>
  <li>[Función de Ackermann](http://es.wikipedia.org/wiki/Funci%C3%B3n_de_Ackermann)</li>
  <li>[Números de Catalan](http://es.wikipedia.org/wiki/N%C3%BAmeros_de_Catalan)</li>
  <li>[Torres de hanoi](http://es.wikipedia.org/wiki/Torres_de_Han%C3%B3i)</li>
  <li>[Fractales](http://es.wikipedia.org/wiki/Fractal)</li>
  <li>Otros...</li>
</ol>

## Conclusión

Resolver problemas es un arte y como todo artista es necesario aprender técnicas que nos permitan mejorar nuestras habilidades, la recursión de una de muchas técnicas que existen para atacar problemas de programación. Técnicas como el backtracking usan, divide y vencerás y búsqueda exhaustiva emplean recursión, entre otras. Este documento abarca solo una pequeña parte del tema de la recursividad, se recomienda al lector indagar más sobre el tema.

Hasta aquí con la recursividad, para más información véase *recursión*.

## Referencias

<table border="0">
    <tr> <td>[1]</td> <td>Dasgupta, C. H. Papadimitriou, and U. V. Vazirani, <b>Algorithms</b> 2006.</td> </tr>
    <tr> <td>[2]</td> <td>Luis E. Vargas Azcona, <b>Problemas y algoritmos.</b></td> </tr>
    <tr> <td>[3]</td> <td>Steven Halim, <b>Competitive programming.</b></td> </tr>
</table>
