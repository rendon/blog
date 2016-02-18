"=========== Meta ============
"StrID : 5
"Title : Arquímedes PI
"Slug  : arquimedes-pi
"Cats  : Algoritmos,Matemática,Programación
"Tags  : 
"=============================
"EditType   : post
"EditFormat : Markdown
"TextAttach : wpid1454-wpid-wpid-vimpress_5376bc3e_mkd.txt
"========== Content ==========
[php]initialize();[/php]
[php]section("Introducción");[/php]

En matemáticas <b>$$\pi$$</b> es una constante cuyo valor es la razón entre el perímetro de un círculo con respecto a su diámetro, es decir, cuantas veces cabe el diámetro en el perímetro del círculo.

[php]figure('pi_unrolled', 'Razón entre el el perímetro y el diámetro de un círculo', 'pi_unrolled', 'gif', 'ES');[/php]

Arquímides de Siracusa(c. 287 a. C. ? c. 212 a. C.) fue un matemático griego, físico, ingeniero, inventor y astrónomo. Él fue probablemente el primero en encontrar un método para aproximar el valor de $$\pi$$ de manera iterativa.

Dada una circunferencia, el método de Arquímides consiste en dibujar un polígono inscrito y otro circunscrito y calculaba el perímetro de ambos polígonos, siendo estos perímetros el límite superior(polígono circunscrito) y límite inferior(polígono inscrito), véase figura [php]ref('arquimedes_pi');[/php].

[php]
figure('arquimedes_pi', 'Método de Arquímides para obtener PI', 'arquimedes_pi', 'png', 'ES');
[/php]

Con base en lo anterior Arquímides pudo determinar el intervalo numérico en el que se encuentra el valor exacto de $$\pi$$, ecuación [php]ref("pi_interval");[/php].

[php]equation("3+\frac{10}{71}<\pi<3+\frac{1}{7}", "pi_interval");[/php] 

Sabemos que el perímetro de una circunferencia es igual a $$2 \* \pi \* radio$$ o  $$\pi \* diametro$$ y que el perímetro de un polígono regular de <em>n</em> lados es $$n \* longitudDeLado$$. Las fórmulas [php]ref("pi_inf");[/php] y [php]ref("pi_sup");[/php] obtienen el valor aproximado de $$\pi$$ para para los límites inferior y superior para polígonos inscritos y circunscritos respectivamente.

[php]equation("p = 2rsin(\frac{\theta}{2})n \approx \pi", "pi_inf");[/php]
[php]equation("p = 2rtan(\frac{\theta}{2})n \approx \pi", "pi_sup");[/php]

Donde <em>n</em> es el número de lados del polígono, <em>r</em> el radio de la circunferencia y $$\theta$$ es el ángulo interno formado por los lados del polígono. Para un caso general podemos asumir que el diámetro del círculo es igual a la unidad, por tanto $$r=\frac{1}{2}$$, reduciendo las fórmulas [php]ref("pi_inf");[/php] y [php]ref("pi_sup");[/php] a

[php]equation("p = sin(\frac{\theta}{2})n \approx \pi", "pi_inf_gen");[/php]
[php]equation("p = tan(\frac{\theta}{2})n \approx \pi", "pi_sup_gen");[/php]


Según las fórmulas [php]ref("pi_inf_gen");[/php] y [php]ref("pi_sup_gen");[/php] solo necesitamos conocer el valor de <em>n</em> el cual lo sabemos de antemano  y el valor de $$\theta$$, que calculamos con 

[php]equation("\frac{2\pi}{n}~~~~~~siendo~\pi=3.14159", "calc_theta");[/php]

En la ecuación [php]ref("calc_theta");[/php] se remarca que en esta fórmula debe emplearse el valor de $$\pi$$ con la precisión que empleamos comúnmente para el calculo de $$\theta$$.

Por cierto, si se preguntan de donde resultan las formulas una imagen puede ayudar.

[php]figure('perimetro_pi_formulas', 'Derivación de formulas', 'perimetro_pi_formulas', 'png', 'ES');[/php]

Cuanto mayor sea el número de lados del polígono mayor sera la precisión del valor de $$\pi$$. Así, por ejemplo, para n = 3, n = 8 y n = 17280 usando un polígono inscrito tenemos que el valor aproximado de $$\pi$$ es 2.598076211353316, 3.0614674589207183 y 3.1415926362832276 respectivamente.

[php]section("Aplicaciónes");[/php]

Hoy por la mañana me levante y por suerte tenía un poco de tiempo libre así que prendí mi ordenador y decidí entrar la arena de Topcoder y practicar un poco(para no quedar en los últimos lugares como siempre) y entonces me encontré con el problema <a href="http://www.topcoder.com/stat?c=problem_statement&pm=1693" target="__blank">Archimedes</a> empleado en el SRM 151. Sinceramente no tuve idea de como resolver el problema, no soy muy matemático que digamos, así que investigue un poco y pude resolver el problema. En este post he expuesto lo que encontré, espero que les sirva. Les dejo la solución del problema en C++ por si acaso.

<pre lang="cpp">
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

class Archimedes
{
public:
    double approximatePi(int numSides) {
        double pi = acos(-1);
        double angle = 2 * pi / numSides;
        return numSides * sin(angle / 2);
    }
};

int main()
{
    Archimedes archimedes;
    cout << archimedes.approximatePi(4) << endl;
    return 0;
}
</pre>

[php]section("Referencias");[/php] 
<p>
[1] <a href="http://en.wikipedia.org/wiki/Approximations_of_%CF%80" target="_blank"> http://en.wikipedia.org/wiki/Approximations_of_%CF%80 </a><br\>
[2] <a href="http://www.pbs.org/wgbh/nova/physics/approximating-pi.html" target="_blank"> http://www.pbs.org/wgbh/nova/physics/approximating-pi.html</a>
</p>


[php]finalize();[/php]
