<!-- vim: set spelllang=es_MX: -->

# Fibonacci nuevamente
2016-02-18 2024-05-07 #algorithms #post

La sucesión de fibonacci se define de la siguiente manera:

$f(n) = \begin{cases} 0 & \text{si n = 0} \\\\ 1 & \text{si n = 1} \\\\ f(n - 1) + f(n - 2) & \text{si n > 1} \end{cases} $

Empezando con el uno los primeros 10 términos de esta sucesión son: 
  
$$F\_{1} = 1,\;\; F\_{2} = 1,\;\; F\_{3} = 2,\;\; F\_{4} = 3,\;\; F\_{5} = 5,\;\; F\_{6} = 8,\;\; F\_{7} = 13,\;\; F\_{8} = 21,\;\; F\_{9} = 34,\;\; F\_{10} = 55$$
	
	
Quizás están pensando que este post trata simplemente en implementar la función en algun lenguaje de programación y entonces probablemente su primera reacción será "ya me lo se...". ¿Pues que creen? lo que aquí les mostrare es una alternativa al calculo de los términos de fibonacci. Me refiero al *número aureo* o *golden ratio*.
	
	
$$F\_{n} = \left[\frac{\varphi^{n}}{\sqrt{5}}\right]$$
	
	
Donde los corchetes indican que el *n-esimo* término corresponde al **entero más cercano**. Y por supuesto, ***n*** es el término que deseamos conocer...Hey! Alto! Alto! Y ese "phi" de donde salio?, veamos, la constante $\varphi$ es un numero irracional con valor aproximado de 1.618033988749894848204586834365638117720309179805762862135448622705260 el cual se obtiene de la siguiente fórmula:
	

$$\varphi = \frac{1 + \sqrt{5}}{2}$$

	
Es probable que halla muchas dudas al respecto de $\varphi$, yo las tengo. Desafortunadamente yo no puedo explicarles eso así que checar [aquí para mas información](http://es.wikipedia.org/wiki/N%C3%BAmero_%C3%A1ureo).
	
	
Veamos un ejemplo. Sabemos que $F\_{10} = 55$, y según la fórmula:
	
$$F\_{10} = \left[\frac{\varphi^{10}}{\sqrt{5}}\right] \approx 55.0036361232 \rightarrow 55$$
	
Encontré esta razón en los foros de [projecteuler.net](http://projecteuler.net) después de resolver el problema 25 por fuerza bruta y me llamo mucho la atención la solución tan elegante con esta propiedad. Acá les dejo el problema para que practiquen.
	
<blockquote>
  La sucesión de Fibonacci se define por la siguiente relación recurrente.
  <br>
  <br>

  <p>F<sub>n</sub> = F<sub>n-1</sub> + F<sub>n-2</sub>, donde F<sub>1</sub> = 1 y F<sub>2</sub> = 1.</p>
  <br>
  <br>
  Por ende los primeros 12 términos son:
  <br>
  <br>
  F(1) = 1<br>
  F(2) = 1<br>
  F(3) = 2<br>
  F(4) = 3<br>
  F(5) = 5<br>
  F(6) = 8<br>
  F(7) = 13<br>
  F(8) = 21<br>
  F(9) = 34<br>
  F(10) = 55<br>
  F(11) = 89<br>
  F(12) = 144<br>
  <br>
  El 12th término, F(12), es el primer término que contiene 3 dígitos.
  <br>
  <br>
  ¿Cual es el primer término el la sucesión de fibonacci que contiene 1000 dígitos?
</blockquote>

[www.projecteuler.net, problem 25](http://www.projecteuler.net).
	

#Referencias
\[1\] [ProjectEuler.net](http://projecteuler.net), foro del problema 25.
\[2\] [Número aureo](http://es.wikipedia.org/wiki/N%C3%BAmero_%C3%A1ureo), Wikipedia.
