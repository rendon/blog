<!-- vim: set spelllang=es_MX: -->
---
tags:
    - algorithms
    - math
    - post
created: 2016-02-18
updated: 2024-05-07
---
# Factorial y ceros

## Introducción

Hoy vamos a platicar acerca de los factoriales, en particular de un problema muy interesante que de primera vista puede parecer muy complicado resolver. Adelante, veamos de que trata esto.

El factorial de un numero $n$ se denota con $n!$ y se define de la siguiente manera: 

$$n!= \begin{cases} 1 & \text{si n = 0} \\\\ n(n - 1)!& \text{si n > 0} \end{cases}$$


Por ejemplo 5! = 5 * 4 * 3 * 2 * 1 = 120.

El valor de un factorial es una cantidad que crece extremadamente rápido, incluso para valores de *n* muy pequeños, por ejemplo 10! = 3628800, para 50! = 30414093201713378043612608166064768844377641568960512000000000000...Esta cantidad es realmente inmensa!. Aquí viene el problema, si se dan cuenta 5! = 120, el cual tiene un cero ( 0 ) al final del numero y además 10! = 3628800 con 2 ceros al final del número resultante, por último 50! tiene 12 ceros al final del número resultante, y aun más, el numero de ceros al final del resultado aumenta cuanto más grande es el valor de *n*, supongo que si se dieron cuenta, solo por si las dudas lo remarco :).

## Un problema

<blockquote>
<h3>Problema </h3>

Dado un numero N, siendo 1 <= N <= 1000000000, calcular el numero de ceros al final del  resultado de N!.

### Entrada
Un único número entero N, 1 <= N <= 1000000000.

<h3>Salida</h3>

Un solo valor entero indicando la cantidad de ceros al final del numero resultante de N!.

<H3>Ejemplos</H3>

Ejemplo 1:
<table width="200" style="text-align: left; width: 100%;" border="1" cellpadding="2" cellspacing="2">
	<tbody>
		<tr>
			<td width="100" bgcolor = "#dddddd" style="vertical-align: top;"><b>Entrada</b><br>
			</td>
			<td width="100" bgcolor = "#dddddd" style="vertical-align: top;"><b>Salida</b><br>
			</td>
		</tr>
		<tr>
			<td  width="100" style="vertical-align: top;">4<br>
			</td>
			<td width="100"  style="vertical-align: top;">0<br>
			</td>	
		</tr>
	</tbody>
</table>

Ejemplo 2:
<table width="200" style="text-align: left; width: 100%;" border="1" cellpadding="2" cellspacing="2">
	<tbody>
		<tr>
			<td width="100"  bgcolor = "#dddddd" style="vertical-align: top;"><b>Entrada</b>
			</td>
			<td width="100" bgcolor = "#dddddd" style="vertical-align: top;"><b>Salida</b><br>
			</td>
		</tr>
		<tr>
			<td width="100"  style="vertical-align: top;">50<br>
			</td>
			<td width="100" style="vertical-align: top;">12<br>
			</td>	
		</tr>
	</tbody>
</table>
</blockquote>

Antes de continuar les sugiero que primero le piensen un poco y traten de resolver el problema por ustedes mismos, en serio!

### Primeras aproximaciones

<ul>
<li> * En un principio se me ocurre calcular los factoriales de los números, después descomponer dicho valor en sus dígitos y contar cuantos ceros hay al final del numero. *

  Mmm Bueno, los lenguajes de programación proveen tipos de datos predefinidos para números enteros, por lo general enteros de 4 y 8 bytes, un entero de 8 bytes es capaz de almacenar un valor entero de hasta $2^{64}$, lo cual equivale a un numero sin signo (unsigned en C/C++ ) de 20 dígitos. Veinte dígitos forman un número muy grande pero ya vimos que tan solo para factorial de 50 el numero resultante tiene mas de 60 dígitos .... No, creo que esta idea no funcionaria :(. 
</li>

<li>
*Otra idea! Porque no implementar un algoritmo para realizar multiplicaciones para números gigantes, no se, utilizando arreglos, o mejor utilizo *python* y aprovecho de que este lenguaje puede manejar números muy inimaginablemente grandes y nuevamente descomponer el numero en sus correspondientes dígitos y volver a contarlos.*

Bueno esto podría funcionar, sin embargo implementar el algoritmo descrito requiere mucho tiempo y es algo complicado. La segunda opción si bien es más fácil realmente es el lenguaje el que nos hace la mayoría del trabajo y no nosotros mismos. Busquemos algo más
</li>
<li>
*Que tal si de de pura casualidad existiera algún método matemático que me permitiera cuantificar la cantidad de ceros al final de un número dado sin necesidad de trabajar directamente con dicho valor!*
</li>
</ul>

Esto último seria algo maravilloso si existiera... Y que creen? SI EXISTE!.

El numero de ceros al final de un entero **N** en base _b_ es igual al exponente de la máxima potencia de _b_ que divide a N. Por ejemplo, sea N = 14000 en *base 10*, hay 3 ceros al final del número, la máxima potencia de 10 que divide a 14000 es 1000 = 10<sup>3</sup>. El exponente que al que se eleva 10 para dar 1000 es 3, hay tres ceros al final de 14000.

La cantidad de ceros al final de los factoriales es un caso especial y se calcula como sigue.

<blockquote>"El numero de ceros al final de un numero **n** en base 10 de *n! * es simplemente la multiplicidad del factor primo 5 en _n!_. Esto se puede determinar con este caso especial de la [formula de Polignac](http://en.wikipedia.org/wiki/De_Polignac%27s_formula):

$$f(n) = \sum\_{i=1}^k \left \lfloor \frac{n}{5^i} \right \rfloor = \left \lfloor \frac{n}{5} \right \rfloor + \left \lfloor \frac{n}{5^2} \right \rfloor + \left \lfloor \frac{n}{5^3} \right \rfloor + \cdots + \left \lfloor \frac{n}{5^k} \right \rfloor$$

</blockquote>

Donde k debe ser un valor tal que [latex] 5^{k+1} > n \geq 5^{n}[/latex] y . Además es necesario tener en cuenta que [latex]f(n)\leq f(n+1)[/latex] y por lo tanto cuanto mas aumente el valor de *n* el numero de ceros al final del factorial de *n* siempre sera mayor o igual a cualquier valor menor que n. **Nunca menor!**. 

Por ejemplo, calculemos la cantidad de ceros al final de 50!.

Un valor para k que cumpla [latex] 5^{k+1} > n,\, [/latex] es 2. Entonces [latex] \left \lfloor \frac{50}{5} \right \rfloor + \left \lfloor \frac{50}{5^2} \right \rfloor = 10 + 2 = 12\, [/latex].

Ahora una posible solución.


```cpp
long long z(long long n)
{
    long long zeros = 0;
    long long  k = 5;

    while (k <= n) {
        zeros += n / k;
        k *= 5;
    }

    return zeros;
}

```

Claro que hay otras formas de solucionar este problema pero creo que esto funciona bien.

La [Olimpiada Mexicana de Informática (OMI)](http://www.olimpiadadeinformatica.org.mx/) cuenta con la [OMI Training gate](http://www.cmirg.com:8081/traingate/), un portal de entrenamiento  con juez en línea donde se puede resolver problemas de tipo olimpiada y ser evaluados al instante en el servidor y devolviendo los resultados en el mismo instante. En este portal se presenta un problema llamado *K-Ceros* el cual puede ser resuelto con lo que hemos visto en este post. Puedes dirigirte a este sitio y con previo registro tener acceso a gran cantidad de problemas de tipo olimpiada de diferentes niveles de complejidad. Se los recomiendo!
	
**Tip:** Para el problema de K-Ceros utilicen una búsqueda binaria para agilizar la busqueda del resultado.

Por cierto, el problema con el que iniciamos el post es una versión simplificada del problema [Factorial](http://www.codechef.com/problems/FCTRL/), tomado de [www.codechef.com](http://www.codechef.com), un sitio donde puedes resolver problemas de todo tipo con juez en línea. La ventaja de este portal es que permite enviar soluciones en una gran variedad de lenjuajes, aproximadamente 35 lenguajes.

Bueno, hasta aqui con este tema, espero que les halla sido de interes y sobre todo de utilidad. Si te ha sido de utilidad este tema les agradeceria un comentario, ya sea para comentar, corregir o preguntar. Bueno, nos vemos en el próximo post :)!

## Código fuente

<table border="0">
  <tr>
    <td>factorial_zeros.cpp</td>
    <td> [z.cpp](z.cpp)</td>
  </tr>
</table>

## Referencias

<ol>
  <li>[http://en.wikipedia.org/wiki/Trailing_zero](http://en.wikipedia.org/wiki/Trailing_zero)</li>
</ol>
