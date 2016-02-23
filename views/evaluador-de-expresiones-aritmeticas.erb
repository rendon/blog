"=========== Meta ============
"StrID : 45
"Title : Evaluador de expresiones aritméticas
"Slug  : evaluador-de-expresiones-aritmeticas
"Cats  :
"Tags  :
"=============================
"EditType   : post
"EditFormat : markdown
"TextAttach : wpid1180-vimpress_53778eff_mkd.txt
"========== Content ==========
[php]initialize();[/php]
Suponga que tiene la siguiente expresión aritmética: `3*(5*6/3)^(2+5)+1`. ¿Cuál es el resultado? Si aplicamos las reglas de precedencia adecuadas el resultado es 30000001.

En este articulo se plantea el problema de idear un algoritmo que permita evaluar este tipo de expresiones en un ordenador. A continuación se presenta una posible solución bastante sencilla y eficiente.

En la actualidad se conocen tres notaciones para representar expresiones aritméticas, <a href="http://es.wikipedia.org/wiki/Notaci%C3%B3n_polaca" target="_blank">prefija</a>, <a href="http://es.wikipedia.org/wiki/Notaci%C3%B3n_de_infijo" target="_blank">infija</a> y <a href="http://es.wikipedia.org/wiki/Notaci%C3%B3n_polaca_inversa" target="_blank">posfija</a>. Normalmente nosotros empleamos notación infija, que es aquella donde el operador se posiciona en medio de los dos operandos.

$$! \large A + B $$

Esta notación nos facilita a nosotros(los humanos) evaluar las expresiones, sin embargo para una computadora es más fácil evaluar las expresiones si se encuentran en notación posfija o prefija, la primera es aquella donde el operador se encuentra después de los dos operandos.

$$! \large A B + $$

Mientras que la notación prefija consiste en colocar primeramente el operador y después los dos operandos.

$$! \large + A B $$

Ambas notaciones, prefija y postfija facilitan la evaluación de este tipo de expresiones, siendo la notación posfija la elegida para trabajar en este artículo.


[php]section("Algoritmos");[/php]

Antes de comenzar con los algoritmos es necesario especificar los elementos validos de las expresiones que pretendemos trabajar. La siguiente tabla ilustra los operadores soportados y su precedencia.

<table>
    <tr><td>Operador</td>    <td>Precedencia</td>  <td>Operación</td>             </tr> 
    <tr><td>^</td>           <td>3</td>            <td>Exponenciación</td>        </tr>
    <tr><td>-</td>           <td>3</td>            <td>Negacion</td>              </tr>
    <tr><td>*</td>           <td>2</td>            <td>Multiplicación</td>        </tr>
    <tr><td>/</td>           <td>2</td>            <td>División</td>              </tr>
    <tr><td>%</td>           <td>2</td>            <td>Residuo</td>               </tr>
    <tr><td>+</td>           <td>1</td>            <td>Adición</td>               </tr>
    <tr><td>-</td>           <td>1</td>            <td>Sustracción</td>           </tr>
    <tr><td>(</td>           <td>-1</td>            <td>Agrupación-Apertura</td>   </tr>
    <tr><td>)</td>           <td>?</td>            <td>Agrupación-Clausura</td>   </tr>
</table>

La precedencia de una operación indica el orden que que debe realizarse, las operaciones de mayor precedencia deben realizarse primero, por ejemplo, una multiplicación debe realizarse antes que una adición, exponenciación antes que la división, operaciones de igual precedencia se evalúan de izquierda a derecha. Las operaciones agrupadas entre paréntesis tienen la más alta prioridad sin embargo se le asigna la presencia -1 porque el algoritmo así lo requiere.

Antes de proceder con la evaluación de expresiones es necesario tener en cuenta que para que el algoritmo funcione correctamente la expresión debe tener una sintaxis correcta, por ejemplo, una distribución de paréntesis adecuada, también es indispensable que la expresión emplee únicamente elementos válidos, es decir, no emplear caracteres que no sean operadores ni operandos como pueden ser <code>"$?\_%#</code>. Es difícil crear una aplicación que tome en cuenta todos los posibles casos de error que pudieran surgir, sin embargo podemos abordar los más comunes, verificar el uso de elementos validos es muy fácil y se consigue con solo iterar por toda la cadena y comprobar que los caracteres sean operadores(+-\*/^) o dígitos(0-9). La siguiente función comprueba el balanceo de paréntesis.


<pre lang="c" theme="slate" line="1">
bool check(string expression)
{
    int i;
    int top = 0;
    char stack[LIMIT];
    for (i = 0; i < expression.length(); i++) {
        if (expression[i] == '(') {
            stack[top++] = '(';
        } else if (expression[i] == ')') {
            cout << "top = " << top << endl;
            cout << stack[top - 1] << endl << endl;

            if (top == 0) {
                return false;
            }

            if (stack[top - 1] != '(') {
                return false;
            }

            top--; //pop()
        }
    }

    return top == 0;
}
</pre>


El algoritmo que aquí se emplea utiliza una <em>pila</em>, que es una estructura de datos lineal donde únicamente podemos insertar(push) o eliminar(pop) elementos por uno de sus extremos con la siguiente regla: Último en entrar, primero en salir(LIFO).

La idea es muy simple y consiste en recorrer la cadena de caracteres y cada vez que encontremos un paréntesis de apertura('(') lo metemos a una pila(push). Si encontramos un paréntesis de clausura(')') en la pila debe de haber un paréntesis de apertura y lo quitamos de la pila(pop), si no es así entonces hay un error ya que existe un paréntesis que cierra sin que exista uno que abra. Debido a que el número de paréntesis que abren debe ser igual al número de paréntesis que cierran al final la pila debe quedar vacía o de lo contrario hay error.

La función que se muestra a continuación toma una expresión aritmética que previamente ha sido analizada para comprobar el balance de paréntesis y la convierte a notación posfija.

<pre lang="c" theme="slate" line="1">
string to_postfix(string expression)
{
    int i, j, top = 0;
    char stack[LIMIT];
    char token;
    string output;
    for (i = 0; i < expression.length(); i++) {
        token = expression[i];
        if (isdigit(token)) {
            output += token;
        } else if (token == '(') {
            stack[top++] = '(';
        } else if (token == ')') {
            while (stack[top - 1] != '(') {
                output += stack[--top];
            }

            top--;
        } else if (strchr("+-*/^", token) != NULL) {
            while (precedence(token) <= precedence(stack[top - 1])) {
                output += stack[--top];
            }

            stack[top++] = token;
        }
    }

    while (top > 0) {
        output += stack[--top];
    }

    return output;
}
</pre>

El algoritmo que se emplea en la función anterior lo pueden encontrar en casi cualquier libro de estructuras de datos, generalmente cuando se abordan los temas de recursión o pilas. De todas formas aquí les dejo <a href="http://montcs.bloomu.edu/~bobmon/Information/RPN/infix2rpn.shtml" target="_blank">este link</a> donde pueden encontrar los detalles.

Teniendo la expresión en notación posfija solo nos resta la función que realiza la evaluación.

<pre lang="c" theme="slate" line="1">
double eval(string expression)
{
    int i, j, top = 0;
    double a, b, c;
    double stack[LIMIT];

    for (i = 0; i < expression.length(); i++) {
        if (isdigit(expression[i])) {
            stack[top++] = (double)(expression[i] - '0');
        } else { // Operator
            b = stack[--top];
            a = stack[--top];

            switch (expression[i]) {
            case '+':
                c = a + b;
                break;
            case '-':
                c = a - b;
                break;
            case '*':
                c = a * b;
                break;
            case '/':
                c = a / b;
                break;
            case '%':
                c = (int)a % (int)b;
                break;
            case '^':
                c = pow(a, b);
                break;
            }

            stack[top++] = c;
        }
    }

    return stack[top - 1];
}
</pre>

El algoritmo que empleamos para evaluar la expresión posfija consiste en avanzar por la expresión y si el elemento es un operando(dígito) lo ponemos en la pila, pero si es un operador(+-\*/%^) entonces retiramos los dos(las operaciones son binarias) elementos de lo más alto de la pila en orden inverso, es decir, primero el segundo operando y después el primer operando(el ultimo es el primero ;)), realizamos la operación correspondiente y colocamos el resultado en la pila y continuamos analizando la expresión. Siguiendo estos pasos al final quedara la pila con un solo elemento, el resultado.

Desafortunadamente y como ya se habrán dado cuenta nuestro algoritmo solo permite operandos de un solo dígito y por tanto si introducimos algo como "2.3+(172342+32/1.2)" el programa no producirá el resultado correcto. Bien podríamos modificar el algoritmo para que sea capaz de manejar este tipo de entradas pero lo cierto es que existen otras técnicas más adecuadas para este tipo de situaciones(las más comunes) como la que se describe en el capítulo 40 del libro <em>The complete reference C++, third edition</em> de <strong>Herbert Schildt</strong> y que abordaremos en artículos posteriores.

Les dejo el código fuente completo y algunas referencias para más información. Hasta la próxima!.

[php]section("Referencias");[/php]
<table>
  <tr><td>[1]</td><td>Jessen T. Havill, <a href="http://personal.denison.edu/~havill/algorithmics/algs/postfix.pdf" target="_blank">Postfix algorithms</a></td</tr>
  <tr><td>[2]</td><td>Robert Sedgewick, Kevin Wayne, <strong><a href="http://introcs.cs.princeton.edu/java/home/" target="_blank">Introduction to programming in Java</a></strong>, <em>Stacks and queues</em></td></tr>
</table>

[php]section("Descargas");[/php]

<table>
  <tr><td>eval.cpp</td><td><a href="../../files/src/eval.cpp">eval.cpp</a></td></tr>
</table>

[php]finalize();[/php]
