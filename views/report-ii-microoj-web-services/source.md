<p>Este es el reporte correspondiente al proyecto número 2 de la materia Desarrollo de Aplicaciones para Tecnologías Móviles.</p>

## Definición del Problema

<p>Este proyecto consiste en desarrollar un Web Service que manipule una base de datos a petición de los clientes.</p>

<blockquote>Desarrolle un Web Service con los servicios necesarios para manipular una base de datos (backend) y además una aplicación cliente para que los usuarios puedan acceder a las servicios (frontend).</blockquote>


## Definiciones

<p>Antes de continuar es necesario conocer algunas definiciones para comprender mejor el trabajo que vamos a realizar.</p>

### Web Service

<blockquote>Un Web service es un sistema de software diseñado para soportar interacción máquina-a-máquina de manera interoperable a través de una red. Éste sistema tiene una interfaz descrita en un formato que puede ser procesado por la máquina (específicamente WSDL). Otros sistemas interactúan con el Web service en una manera prescrita por su definición usando mensajes SOAP, comúnmente transmitidos usando HTTP con una serialización XML en conjunto con otros estándares Web. <%= cite('w3c_ws'); %></blockquote>


## Propuesta de solución

<p>El problema nos solicita dos cosas, proveer servicios y manipular una base de datos. En vista que el problema no especifica que servicios ni que datos manipular, tenemos la libertad de enfocar el proyecto a la problemática que más nos agrade.</p>

<p>Vamos a desarrollar un mina sistema de juez en línea como <a href="http://uva.onlinejudge.org/" target="__blank">UVa</a>, <a href="http://lightoj.com/" target="__blank">LightOJ</a> u <a href="http://omegaup.com/" target="__blank">OmegaUp</a>, el cual consiste en dos partes, un servidor (el juez) y uno o más clientes (los solucionadores de problemas).</p>

### El servidor

<p>Es aquí donde vamos a implementar el web service para que proporcione los siguientes servicios:</p>

<ul>
  <li>Crear un problema con sus casos de prueba y almacenarlos en una base de datos.</li>
  <li>Aceptar soluciones de parte de los usuarios y almacenarlas en la base de datos.</li>
  <li>Compilar y ejecutar la solución y reportar los resultados.</li>
</ul>

<p>Esta parte la vamos a realizar en PHP.</p>

### El cliente

<p>Una pequeña aplicación Web en Ruby on Rails que permita a los usuarios realizar los siguientes operaciones.</p>

<ul>
  <li>Crear problemas.</li>
  <li>Enviar soluciones (código fuente).</li>
  <li>Visualizar los resultados de la solución enviada.</li>
</ul>

<p>El nombre de mi juez en línea sera <strong>Micro OJ</strong>, por razones obvias.</p>

## Requisitos

<ul>
  <li><a href="/?p=858">Instalar y configurar un entorno LAMP</a></li>
  <li><a href="/?p=862">Instalar y configurar Ruby on Rails</a></li>
  <li>El servidor debe tener instalados los compiladores para C, C++ y Python.</li>
</ul>

## El servidor

<p>En esta parte vamos a implementar el Web Service. Antes que nada veamos nuestro modelo de base de datos.</p>

![Modelo de la base de datos](/report-ii-microoj-web-services/ws_01.png)

<p><strong>NOTA:</strong> Vamos a hacer una mezcla rara de ingles y español porque sino el profesor no va creer que el trabajo es nuestro. </p>

<p>El Web Service va a consistir de los siguientes servicios.</p>

### Servicios

<table></td></tr>
  <tr><td><strong>create_problem</strong></td><td>               Permite a los usuarios almacenar un problema y sus casos de prueba en la base de datos. </td></tr>
  <tr><td><strong>get_all_problems</strong></td><td>             Recupera todos los problemas de la base de datos y se los retorna al cliente.</td></tr>
  <tr><td><strong>save_solution</strong></td><td>                Recibe una solución por parte del cliente (código fuente).</td></tr>
  <tr><td><strong>compile_solution</strong></td><td>             Compila una solución y retorna el resultado (compila o no).</td></tr>
  <tr><td><strong>get_last_error</strong></td><td>               Retorna al cliente el error ocurrido al compilar una solución.</td></tr>
  <tr><td><strong>save_test_case</strong></td><td>               Recibe un caso de prueba para un problema en específico y lo almácena en la base de datos.</td></tr>
  <tr><td><strong>test_solution</strong></td><td>                Recibe el ID de una solución, la compila, la ejecuta con los casos de prueba correspondientes al problema y reporta los resultados al cliente (PASSO o FALLO).</td></tr>
  <tr><td><strong>create_user</strong></td><td>                  Crear un usuario en la BD.</td></tr>
  <tr><td><strong>get_user</strong></td><td>                     Retorna el ID y nombre de un usuario en particular.</td></tr>
  <tr><td><strong>find_user_by_remember_token</strong></td><td>  Operación auxiliar para el inicio de sesión.</td></tr>
  <tr><td><strong>update_user_remember_token</strong></td><td>   Operación auxiliar para el inicio de sesión.</td></tr>
  <tr><td><strong>get_user_data</strong></td><td>                Recibe un usuario y contraseña y retorna los datos completos del usuario.</td></tr>
  <tr><td><strong>authenticate_user</strong></td><td>            Verifica si un usuario existe en la base de datos con con el nombre de usuario y contraseña provista.</td></tr>
  <tr><td><strong>get_problem</strong></td><td>                  Retorna la descripción de un problema en particular (id, título y descripción).</td></tr>
  <tr><td><strong>get_all_users</strong></td><td>                Retorna la lista de todos los usuario (únicamente el ID y el nombre).</td></tr>
</table></td></tr>

PHP cuenta con soporte nativo para SOAP, pero nosotros vamos a emplear NuSOAP porque nos permite generar el archivo WSDL. El código que implementa el Web Service consta de aproximadamente de 800 líneas y por lo tanto no vamos a entrar en detalles de la implementación, sin embargo, el código no es complejo, con un conocimiento básico de PHP podrán entenderlo.

### Definición de un servicio

<p>Los servicios son funciones normales en PHP, la diferencia es que tenemos que registarlas, por ejemplo, veamos como crear el servicio <strong>create_problem</strong>.</p>

<p>Función:</p>

Embed: `create-problem.php`

<p>Registro del servicio:</p>

Embed: `register.php`

<p>El nombre del servicio comienza con _Judge._ porque la función es parte de la clase _Judge_. El primer argumento es el nombre del servicio, el segundo argumento es un arreglo especificando los datos que require el servicio, el tercer array es para especificar los datos que retorna el servicio, el último argumento es simplemente para documentación.</p>

### Crear un tipo de dato complejo

<p>Para algunos de los servicios retornamos más de un dato, por ejemplo, _get_problem_ y _get_user_data_  que retornan una estructura con los datos del problema y del usuario respectivamente, o _get_all_problems_ que retorna una lista de problemas. Veamos como crear un tipo de dato complejo y después un arreglo de objetos complejos.</p>

Embed: `add-complex-type.php`

<p>En este código especificamos el nombre del tipo de dato, los campos que contiene, los tipos de datos de cada campo, etc. Ahora un arreglo de objetos tipo <strong>Problem</strong>.</p>

Embed: `add-complex-type-2.php`

<p>Y es así como se procede con el resto de los servicios.</p>

## El cliente

<p>Esta la parte más extensa y que necesitará de mucha paciencia, hacer una descripción sería abrumador y aburrido, por lo que únicamente vamos a ver las partes más importantes.</p>

<p>Esta parte consume mucho tiempo principalmente porque hay que aprender el lenguaje Ruby y ademas como utilizar el framework Ruby on Rails, pero si ya conocen bien éstas dos herramientas supongo terminarán mucho más rápido. Mi recomendación para Ruby on Rails es <a href="http://ruby.railstutorial.org">Ruby on Rails Tutorial</a> por Michael Hartl, el cual seguí para realizar el cliente.</p>

### Cliente SOAP

<p>Para poder utilizar los servicios del Web Service será necesaria una herramienta que sea capaz de comunicarse con el servidor utilizando el protocolo SOAP, y esa herramienta se llama <a href="http://savonrb.com/" target="_blank">Savon</a>, un cliente SOAP para el lenguaje Ruby.</p>

<p>Veamos como establecer comunicación con el servidor para crear un usuario.</p>

Embed: `client-conn.rb`

<p>Al ejecutarlo debe arrojar algo similar a esto:</p>

Embed: `client-conn-output.txt`

<p>El ejemplo anterior da por hecho que los servidores Apache y MySQL están encendidos y que la base de datos ya esta instalada. </p>

<p><strong>NOTA:</strong> Con el código fuente incluyo el modelo de la base de datos, fue diseñado utilizando Workbench y por lo tanto podrán exportar la base de datos desde ahí.</p>

### La interfaz

<p>Una imagen dice más que mil palabras, como todos sabemos, así que allá vamos.</p>

![Página principal de MicroOJ](/report-ii-microoj-web-services/ws_02.png)

![Formulario de registro de usuarios](/report-ii-microoj-web-services/ws_03.png)

![Formulario de inicio de sesión](/report-ii-microoj-web-services/ws_04.png)

![Lista de problemas](/report-ii-microoj-web-services/ws_05.png)

<p>Cada problema debe mostrar la opción de enviar una solución, sin embargo, nótese que en la imagen esta opción no figura, esto es porque el usuario no ha iniciado sesión y únicamente los usuarios registrados pueden enviar soluciones.</p>


![Usuario que ha iniciado sesión](/report-ii-microoj-web-services/ws_06.png)

<p>En esta imagen observe que en la barra izquierda ha aparecido una nueva operación, "Crear problemas", esta operación esta disponible únicamente para el usuario administrador.</p>

![Formulario para registrar un problema](/report-ii-microoj-web-services/ws_07.png)


![Los usuarios pueden enviar soluciones](/report-ii-microoj-web-services/ws_08.png)


![Formulario para enviar soluciones](/report-ii-microoj-web-services/ws_09.png)

<p>El editor de código es Ace (<a href="http://ace.c9.io/">http://ace.c9.io/</a>).</p>

![Resultados de la solución](/report-ii-microoj-web-services/ws_10.png)

<p>El diseño de la interfaz fue hecho utilizando Bootstrap (<a href="http://getbootstrap.com/2.3.2/index.html">http://getbootstrap.com/2.3.2/index.html</a>).</p>

## Desarrollo del cliente

<p>Ahora que ya vimos como trabaja el cliente, es momento de explicar a grandes rasgos como se desarrollo.</p>

### Creación del proyecto

<p>En este punto vamos a asumir que ROR ya esta instalado y configurado. Ejecuta los siguientes comandos para crear el proyecto.</p>

Embed: `create-project.sh`

<p>El tercer comando genera el esquelo de nuestra aplicación.</p>

![Esqueleto de una aplicación ROR](/report-ii-microoj-web-services/ws_11.png)

<p>La mayor parte de la acción ocurre en el subdirectorio _app_, especificamente en los subdirectorios _app/views_, _app/controllers_ y _app/models_, esta estructura corresponde al patron de diseño <a href="https://en.wikipedia.org/wiki/Model%E2%80%93view%E2%80%93controller" target="_blank">Model View Controller</a>. </p>

### Contenido de nuestro proyecto

<p>Nuestra aplicación consiste de 5 vistas:</p>

<ul>
  <li><strong>problems</strong> Para crear y visualizar problemas.</li>
  <li><strong>solutions</strong> Para enviar soluciones y visualizar resultados.</li>
  <li><strong>users</strong> Crear y mostrar información sobre usuarios.</li>
  <li><strong>sessions</strong> Para el inicio de sesión.</li>
  <li><strong>static_pages</strong> Estructura y diseño del sitio, contenido estático.</li>
</ul>

<p>Cada vista tiene su respectivo controlador en la carpeta _app/controllers_:</p>

<ul>
  <li><strong>problems_controller.rb</strong></li>
  <li><strong>sessions_controller.rb</strong></li>
  <li><strong>solutions_controller.rb</strong></li>
  <li><strong>static_pages_controller.rb</strong></li>
  <li><strong>users_controller.rb</strong></li>
</ul>

<p>Utilizamos también tres modelos para almacenar y manipular nuestros datos, estos archivos se ubican en la carpeta _app/models_:</p>

<ul>
  <li><strong>problem.rb</strong></li>
  <li><strong>solution.rb</strong></li>
  <li><strong>user.rb</strong></li>
</ul>

### Creación de un usuario

<p>La alta de usuarios ocurre de la siguiente manera. El archivo _app/views/users/new.html.erb_ contiene el diseño del formulario.</p>

<p>El código que se encarga de crear al nuevo usuario se encuentra en el archivo _app/controllers/users_controller.rb_. El método _new_ se ejecuta cuando el usuario accede al formulario de registro, lo que hace es crear un objeto de tipo <strong>User</strong>, cuyos datos miembro estan enlazados a los campos del formulario.</p>

Embed: `new-action.rb`

<p>El método _create_ se ejecuta en cuanto el usuario envía los datos de registro. Aquí se realiza la validación, y en caso de que la validación sea satisfactoria se procede a enviar los datos al servidor. En caso contrario se redirecciona nuevamente al formulario con el mensaje de error correspondiente.</p>

Embed: `create-action.rb`

### Inicio de sesión

<p>El diseño del formulario se encuentra en el archivo _app/views/sessions/new.html.erb_.</p>

<p>La código que se encarga de crear la sesión se encuentra en el archivo _app/controllers/sessions_controller.rb_, en el método _create_:</p>

Embed: `sessions-create-action.rb`

### Cierre de sesión

<p>Cerrar sesión básicamente equivale a destruir los datos del usuario actual para que ya no se pueda comunicar con el servidor como usuario registrado, esta acción se encuentra en el método _destroy_, en el mismo archivo del paso anterior.</p>

Embed: `sessions-destroy-action.rb`

<p>El método destroy llama a otro método, _sign_out_, el cual se encuentra en el archivo _app/helpers/sessions_helper.rb_, junto con otros métodos auxiliares para el manejo de sesiones.</p>

Embed: `sessions-sign-out.rb`

### Creación de un problema

<p>La lógica para crear un problema y enviarlo al servidor es la siguiente.</p>

<p>El archivo _app/views/problems/new.html.erb_ contiene el diseño del formulario que se muestra en la figura .</p>
 
<p>El archivo _app/controllers/problems_controller.rb_ contiene la lógica de la creación. El método _new_ crea un objeto de tipo <strong>Problem</strong>, cuyos datos miembro estan enlazados a los campos del formulario.</p>

Embed: `problems-new-action.rb`

<p>Cuando el usuario envía el problema, el método _create_ se encarga de realizar la conexión al servidor, enviar los datos y proveer una respuesta al usuario.</p>

Embed: `problems-create-action.rb`

### Envio de una solución

<p>El formulario para el envio de soluciones se localiza en el archivo _app/views/solutions/new.html.erb_. El controlador <strong>Solutions</strong> es el que se encarga de la lógica de esta operación:</p>

Embed: `solutions-create-action.rb`

<p>Estas son las partes más importantes, creo que con esto podrán entender el resto de las operaciones.</p>

### Notas sobre el uso de la base de datos en ROR

<p>Como habrán  observado, empleamos tres tablas para almacenar nuestros datos, sin embargo, los datos nunca son almacenados en estas tablas ya que todo se envía al servidor remoto, esta es una alteración que he tenido que realizar para aprovechar las facilidades de Ruby on Rails pero a la vez cumplir con el requisito de emplear un Web service.</p>

<p>Al utilizar los modelos que proporciona Rails se nos facilita mucho la creación de formularios y la validación de los datos.</p>

<p>Si prescindiéramos del Web service y empleáramos las bases de datos nativas de Rails, la complejidad del cliente sería mucho menor.</p>

## Código fuente

<p>El código tanto del cliente como del servidor están disponibles en Bitbucket en las siguientes direcciones:</p>

<ul>
  <li><a href="https://bitbucket.org/rendon/microoj/admin">https://bitbucket.org/rendon/microoj</a></li>
  <li><a href="https://bitbucket.org/rendon/microoj_ws">https://bitbucket.org/rendon/microoj_ws</a></li>
</ul>

<p>O bien pueden clonar los repositorios desde la consola:</p>

Embed: `clone-projects.sh`

<p>La licencia de ambos proyectos es GPLv3, con excepción de los componentes empleados, los cuales tienen sus propias licencias.</p>

## Por hacer

<p>Un sistema de juez en línea es más complejo de lo que se muestra en esta práctica, a continuación se listan algunas características deseables:</p>

<ul>
  <li>Mejorar el manejo de usuarios. Que los usuarios puedan ver el perfil de los demás participantes y ver su progreso.</li>
  <li>Reportar estadísticas de cada usuario, como son, problemas resueltos, número de intentos, cuantos de ellos ha sido aceptados, cuantos rechazados, etc. Toda esta información debería ser mostrada en el perfil del usuario.</li>
  <li>Implementar un sistema de <em>Ranking</em>, en mi experiencia, esto es un factor de motivación.</li>
  <li><strong>RETO:</strong> Soportar concursos en tiempo real.</li>
</ul>

## Referencias

- [Web Services Architecture](http://www.w3.org/TR/ws-arch/)
- [Creating Web Services with PHP and SOAP](http://www.sitepoint.com/web-services-with-php-and-soap-1/) 
- [Documentación de NuSOAP](http://nusoap.sourceforge.net/)
- [Ubuntu, Ruby, RVM, Rails, and You](http://ryanbigg.com/2010/12/ubuntu-ruby-rvm-rails-and-you/)
- [Ruby on Rails Tutorial](http://ruby.railstutorial.org/)
- [Documentación de Savon](http://savonrb.com/)

