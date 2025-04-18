<!-- vim: set spelllang=es_MX: -->

---
tags:
    - dev
    - post
created: 2016-02-18
updated: 2024-05-07
---
# Reporte II: MicroOJ & servicios Web

Este es el reporte correspondiente al proyecto número 2 de la materia Desarrollo de Aplicaciones para Tecnologías Móviles.

## Definición del Problema

Este proyecto consiste en desarrollar un Web Service que manipule una base de datos a petición de los clientes.

<blockquote>Desarrolle un Web Service con los servicios necesarios para manipular una base de datos (backend) y además una aplicación cliente para que los usuarios puedan acceder a las servicios (frontend).</blockquote>


## Definiciones

Antes de continuar es necesario conocer algunas definiciones para comprender mejor el trabajo que vamos a realizar.

### Web Service

<blockquote>Un Web service es un sistema de software diseñado para soportar interacción máquina-a-máquina de manera interoperable a través de una red. Éste sistema tiene una interfaz descrita en un formato que puede ser procesado por la máquina (específicamente WSDL). Otros sistemas interactúan con el Web service en una manera prescrita por su definición usando mensajes SOAP, comúnmente transmitidos usando HTTP con una serialización XML en conjunto con otros estándares Web.</blockquote>


## Propuesta de solución

El problema nos solicita dos cosas, proveer servicios y manipular una base de datos. En vista que el problema no especifica que servicios ni que datos manipular, tenemos la libertad de enfocar el proyecto a la problemática que más nos agrade.

Vamos a desarrollar un mina sistema de juez en línea como [UVa](http://uva.onlinejudge.org/), [LightOJ](http://lightoj.com/) u [OmegaUp](http://omegaup.com/), el cual consiste en dos partes, un servidor (el juez) y uno o más clientes (los solucionadores de problemas).

### El servidor

Es aquí donde vamos a implementar el web service para que proporcione los siguientes servicios:

<ul>
  <li>Crear un problema con sus casos de prueba y almacenarlos en una base de datos.</li>
  <li>Aceptar soluciones de parte de los usuarios y almacenarlas en la base de datos.</li>
  <li>Compilar y ejecutar la solución y reportar los resultados.</li>
</ul>

Esta parte la vamos a realizar en PHP.

### El cliente

Una pequeña aplicación Web en Ruby on Rails que permita a los usuarios realizar los siguientes operaciones.

<ul>
  <li>Crear problemas.</li>
  <li>Enviar soluciones (código fuente).</li>
  <li>Visualizar los resultados de la solución enviada.</li>
</ul>

El nombre de mi juez en línea sera **Micro OJ**, por razones obvias.

## Requisitos

<ul>
  <li>[Instalar y configurar un entorno LAMP](/?p=858)</li>
  <li>[Instalar y configurar Ruby on Rails](/?p=862)</li>
  <li>El servidor debe tener instalados los compiladores para C, C++ y Python.</li>
</ul>

## El servidor

En esta parte vamos a implementar el Web Service. Antes que nada veamos nuestro modelo de base de datos.

![Modelo de la base de datos](/report-ii-microoj-web-services/ws_01.png)

**NOTA:** Vamos a hacer una mezcla rara de ingles y español porque sino el profesor no va creer que el trabajo es nuestro. 

El Web Service va a consistir de los siguientes servicios.

### Servicios

<table></td></tr>
  <tr><td>**create_problem**</td><td>               Permite a los usuarios almacenar un problema y sus casos de prueba en la base de datos. </td></tr>
  <tr><td>**get_all_problems**</td><td>             Recupera todos los problemas de la base de datos y se los retorna al cliente.</td></tr>
  <tr><td>**save_solution**</td><td>                Recibe una solución por parte del cliente (código fuente).</td></tr>
  <tr><td>**compile_solution**</td><td>             Compila una solución y retorna el resultado (compila o no).</td></tr>
  <tr><td>**get_last_error**</td><td>               Retorna al cliente el error ocurrido al compilar una solución.</td></tr>
  <tr><td>**save_test_case**</td><td>               Recibe un caso de prueba para un problema en específico y lo almácena en la base de datos.</td></tr>
  <tr><td>**test_solution**</td><td>                Recibe el ID de una solución, la compila, la ejecuta con los casos de prueba correspondientes al problema y reporta los resultados al cliente (PASSO o FALLO).</td></tr>
  <tr><td>**create_user**</td><td>                  Crear un usuario en la BD.</td></tr>
  <tr><td>**get_user**</td><td>                     Retorna el ID y nombre de un usuario en particular.</td></tr>
  <tr><td>**find_user_by_remember_token**</td><td>  Operación auxiliar para el inicio de sesión.</td></tr>
  <tr><td>**update_user_remember_token**</td><td>   Operación auxiliar para el inicio de sesión.</td></tr>
  <tr><td>**get_user_data**</td><td>                Recibe un usuario y contraseña y retorna los datos completos del usuario.</td></tr>
  <tr><td>**authenticate_user**</td><td>            Verifica si un usuario existe en la base de datos con con el nombre de usuario y contraseña provista.</td></tr>
  <tr><td>**get_problem**</td><td>                  Retorna la descripción de un problema en particular (id, título y descripción).</td></tr>
  <tr><td>**get_all_users**</td><td>                Retorna la lista de todos los usuario (únicamente el ID y el nombre).</td></tr>
</table></td></tr>

PHP cuenta con soporte nativo para SOAP, pero nosotros vamos a emplear NuSOAP porque nos permite generar el archivo WSDL. El código que implementa el Web Service consta de aproximadamente de 800 líneas y por lo tanto no vamos a entrar en detalles de la implementación, sin embargo, el código no es complejo, con un conocimiento básico de PHP podrán entenderlo.

### Definición de un servicio

Los servicios son funciones normales en PHP, la diferencia es que tenemos que registarlas, por ejemplo, veamos como crear el servicio **create_problem**.

Función:


```php
function create_problem($user, $password, $title, $description, $author)
{
    if ($this->authenticate_user($user, $password) != VALID_USER) {
        return INVALID_USER;
    }

    $mysqli = $this->open_db();
    $query = $this->fips($title,
                         $description,
                         $author);

    $mysqli->query("SET NAMES UTF8");
    $mysqli->query($query);
    $code = $mysqli->insert_id;

    if ($code == 0) {
        if ($mysqli->errno == ER_DUP_ENTRY) {
            return ER_TITLE_ALREADY_TAKEN;
        } else {
            return ER_FAILED_TO_INSERT_RECORD;
        }
    }

    $mysqli->close();
    return $code;
}

```

Registro del servicio:


```php
$server->register('Judge.create_problem',
    array(
        'user' => 'xsd:string',
        'password' => 'xsd:string',
        'title' => 'xsd:string',
        'description' => 'xsd:string',
        'author' => 'xsd:integer'),
    array('return' => 'xsd:integer'),
    'http://localhost/microoj_ws/judge.php'
);

```

El nombre del servicio comienza con _Judge._ porque la función es parte de la clase _Judge_. El primer argumento es el nombre del servicio, el segundo argumento es un arreglo especificando los datos que require el servicio, el tercer array es para especificar los datos que retorna el servicio, el último argumento es simplemente para documentación.

### Crear un tipo de dato complejo

Para algunos de los servicios retornamos más de un dato, por ejemplo, _get_problem_ y _get_user_data_  que retornan una estructura con los datos del problema y del usuario respectivamente, o _get_all_problems_ que retorna una lista de problemas. Veamos como crear un tipo de dato complejo y después un arreglo de objetos complejos.


```php
$server->wsdl->addComplexType('Problem', 'complexType', 'struct', 'all', '',
    array(
        'id' => array(
            'type' => 'xsd:string',
            'minOccurs' => '1',
            'maxOccurs' => '1'),
        'title' => array(
            'type' => 'xsd:string',
            'minOccurs' => '1',
            'maxOccurs' => '1'),
        'description' => array(
            'type' => 'xsd:string',
            'minOccurs' => '1',
            'maxOccurs' => '1')
        )
    );

```

En este código especificamos el nombre del tipo de dato, los campos que contiene, los tipos de datos de cada campo, etc. Ahora un arreglo de objetos tipo **Problem**.


```php
$server->wsdl->addComplexType(
    'ArrayOfProblem',
    'complexType',
    'array',
    'sequence',
    '',
    array(
        'problem' => array(
            'type'      => 'tns:Problem',
            'minOccurs' => '0', 
            'maxOccurs' => 'unbounded'
        )
    )
);

```

Y es así como se procede con el resto de los servicios.

## El cliente

Esta la parte más extensa y que necesitará de mucha paciencia, hacer una descripción sería abrumador y aburrido, por lo que únicamente vamos a ver las partes más importantes.

Esta parte consume mucho tiempo principalmente porque hay que aprender el lenguaje Ruby y ademas como utilizar el framework Ruby on Rails, pero si ya conocen bien éstas dos herramientas supongo terminarán mucho más rápido. Mi recomendación para Ruby on Rails es [Ruby on Rails Tutorial](http://ruby.railstutorial.org) por Michael Hartl, el cual seguí para realizar el cliente.

### Cliente SOAP

Para poder utilizar los servicios del Web Service será necesaria una herramienta que sea capaz de comunicarse con el servidor utilizando el protocolo SOAP, y esa herramienta se llama [Savon](http://savonrb.com/), un cliente SOAP para el lenguaje Ruby.

Veamos como establecer comunicación con el servidor para crear un usuario.


```rb
require 'savon'

client = Savon::Client.new do
    # Dirección de nuestro servicio
    wsdl.document = "http://localhost/microoj_ws/judge.php?wsdl"
end

user_name = "usuario"
password = "1a2b3c"
request = client.request "Judge.create_user" do
    soap.body = {
        :name => user_name,
        :password => password
    }
end

response = request.to_hash[:judge_create_user_response]
puts response
insert_id = response[:return].to_i
puts insert_id

```

Al ejecutarlo debe arrojar algo similar a esto:


```txt
. Logs
.
.
{:return=>"4", :"@xmlns:ns1"=>"http://schemas.xmlsoap.org/soap/envelope/"}
4

```

El ejemplo anterior da por hecho que los servidores Apache y MySQL están encendidos y que la base de datos ya esta instalada. 

**NOTA:** Con el código fuente incluyo el modelo de la base de datos, fue diseñado utilizando Workbench y por lo tanto podrán exportar la base de datos desde ahí.

### La interfaz

Una imagen dice más que mil palabras, como todos sabemos, así que allá vamos.

![Página principal de MicroOJ](/report-ii-microoj-web-services/ws_02.png)

![Formulario de registro de usuarios](/report-ii-microoj-web-services/ws_03.png)

![Formulario de inicio de sesión](/report-ii-microoj-web-services/ws_04.png)

![Lista de problemas](/report-ii-microoj-web-services/ws_05.png)

Cada problema debe mostrar la opción de enviar una solución, sin embargo, nótese que en la imagen esta opción no figura, esto es porque el usuario no ha iniciado sesión y únicamente los usuarios registrados pueden enviar soluciones.


![Usuario que ha iniciado sesión](/report-ii-microoj-web-services/ws_06.png)

En esta imagen observe que en la barra izquierda ha aparecido una nueva operación, "Crear problemas", esta operación esta disponible únicamente para el usuario administrador.

![Formulario para registrar un problema](/report-ii-microoj-web-services/ws_07.png)


![Los usuarios pueden enviar soluciones](/report-ii-microoj-web-services/ws_08.png)


![Formulario para enviar soluciones](/report-ii-microoj-web-services/ws_09.png)

El editor de código es Ace ([http://ace.c9.io/](http://ace.c9.io/)).

![Resultados de la solución](/report-ii-microoj-web-services/ws_10.png)

El diseño de la interfaz fue hecho utilizando Bootstrap ([http://getbootstrap.com/2.3.2/index.html](http://getbootstrap.com/2.3.2/index.html)).

## Desarrollo del cliente

Ahora que ya vimos como trabaja el cliente, es momento de explicar a grandes rasgos como se desarrollo.

### Creación del proyecto

En este punto vamos a asumir que ROR ya esta instalado y configurado. Ejecuta los siguientes comandos para crear el proyecto.


```sh
$ mkdir microoj
$ cd microoj
$ rails new MicroOJ

```

El tercer comando genera el esquelo de nuestra aplicación.

![Esqueleto de una aplicación ROR](/report-ii-microoj-web-services/ws_11.png)

La mayor parte de la acción ocurre en el subdirectorio _app_, especificamente en los subdirectorios _app/views_, _app/controllers_ y _app/models_, esta estructura corresponde al patron de diseño [Model View Controller](https://en.wikipedia.org/wiki/Model%E2%80%93view%E2%80%93controller). 

### Contenido de nuestro proyecto

Nuestra aplicación consiste de 5 vistas:

<ul>
  <li>**problems** Para crear y visualizar problemas.</li>
  <li>**solutions** Para enviar soluciones y visualizar resultados.</li>
  <li>**users** Crear y mostrar información sobre usuarios.</li>
  <li>**sessions** Para el inicio de sesión.</li>
  <li>**static_pages** Estructura y diseño del sitio, contenido estático.</li>
</ul>

Cada vista tiene su respectivo controlador en la carpeta _app/controllers_:

<ul>
  <li>**problems_controller.rb**</li>
  <li>**sessions_controller.rb**</li>
  <li>**solutions_controller.rb**</li>
  <li>**static_pages_controller.rb**</li>
  <li>**users_controller.rb**</li>
</ul>

Utilizamos también tres modelos para almacenar y manipular nuestros datos, estos archivos se ubican en la carpeta _app/models_:

<ul>
  <li>**problem.rb**</li>
  <li>**solution.rb**</li>
  <li>**user.rb**</li>
</ul>

### Creación de un usuario

La alta de usuarios ocurre de la siguiente manera. El archivo _app/views/users/new.html.erb_ contiene el diseño del formulario.

El código que se encarga de crear al nuevo usuario se encuentra en el archivo _app/controllers/users_controller.rb_. El método _new_ se ejecuta cuando el usuario accede al formulario de registro, lo que hace es crear un objeto de tipo **User**, cuyos datos miembro estan enlazados a los campos del formulario.


```rb
def new
    @user = User.new
end

```

El método _create_ se ejecuta en cuanto el usuario envía los datos de registro. Aquí se realiza la validación, y en caso de que la validación sea satisfactoria se procede a enviar los datos al servidor. En caso contrario se redirecciona nuevamente al formulario con el mensaje de error correspondiente.


```rb
def create
    @user = User.new(user_params)
    if @user.valid?
        client = Savon::Client.new do
            wsdl.document = WSDL_LOCATION
        end

        name = params[:user][:name]
        password = params[:user][:password]

        url = SecureRandom.urlsafe_base64
        remember_token = Digest::SHA1.hexdigest(url.to_s)
        request = client.request "Judge.create_user" do
            soap.body = {
                :user => name,
                :password => password,
                :remember_token => remember_token
            }
        end

        response = request.to_hash[:judge_create_user_response]
        id = response[:return].to_i

        if id > 0
            flash[:success] = "Bienvenido a Micro OJ"

            request = client.request "Judge.get_user_data" do
                soap.body = {
                    :user => name,
                    :password => password
                }
            end

            response = request.to_hash[:judge_get_user_data_response]
            user_data = response[:user]
            user = User.new
            user.id = user_data[:id]
            user.name = user_data[:id]
            user.password = user_data[:password]
            user.remember_token = user_data[:remember_token]

            sign_in user
            redirect_to root_path
        else
            render 'new'
        end

    else
        render 'new' # Pending
    end
end

```

### Inicio de sesión

El diseño del formulario se encuentra en el archivo _app/views/sessions/new.html.erb_.

La código que se encarga de crear la sesión se encuentra en el archivo _app/controllers/sessions_controller.rb_, en el método _create_:


```rb
def create
    client = Savon::Client.new do
        wsdl.document = WSDL_LOCATION
    end

    request = client.request "Judge.authenticate_user" do
        soap.body = {
            :user => params[:session][:name],
            :password => params[:session][:password]
        }
    end

    answer = request[:judge_authenticate_user_response][:answer].to_i
    if answer == VALID_USER
        request = client.request "Judge.get_user_data" do
            soap.body = {
                :user => params[:session][:name],
                :password => params[:session][:password]
            }
        end

        response = request.to_hash[:judge_get_user_data_response]
        user_data = response[:user]
        user = User.new
        user.id = user_data[:id]
        user.name = params[:session][:name]
        user.password = params[:session][:password]
        user.remember_token = user_data[:remember_token]

        sign_in user
        redirect_to root_path
    else
        flash.now[:error] = 'Combinación usuario/contraseña invalida'
        render 'new'
    end
end

```

### Cierre de sesión

Cerrar sesión básicamente equivale a destruir los datos del usuario actual para que ya no se pueda comunicar con el servidor como usuario registrado, esta acción se encuentra en el método _destroy_, en el mismo archivo del paso anterior.


```rb
def destroy
    sign_out
    redirect_to root_path
end

```

El método destroy llama a otro método, _sign_out_, el cual se encuentra en el archivo _app/helpers/sessions_helper.rb_, junto con otros métodos auxiliares para el manejo de sesiones.


```rb
def sign_out
    self.current_user = nil
    cookies.delete(:remember_token)
end

```

### Creación de un problema

La lógica para crear un problema y enviarlo al servidor es la siguiente.

El archivo _app/views/problems/new.html.erb_ contiene el diseño del formulario que se muestra en la figura .
 
El archivo _app/controllers/problems_controller.rb_ contiene la lógica de la creación. El método _new_ crea un objeto de tipo **Problem**, cuyos datos miembro estan enlazados a los campos del formulario.


```rb
def new
    @problem = Problem.new
end

```

Cuando el usuario envía el problema, el método _create_ se encarga de realizar la conexión al servidor, enviar los datos y proveer una respuesta al usuario.


```rb
def create
    @problem_saved = false
    parameters = problem_params
    @problem = Problem.new(parameters)
    if not @problem.valid?
        render 'new'
    else
        client = Savon::Client.new do
            wsdl.document = WSDL_LOCATION
        end

        title = parameters[:title]
        description = parameters[:description]
        author = parameters[:author]

        request = client.request "Judge.create_problem" do
            soap.body = {
                :user => current_user.name,
                :password => current_user.password,
                :title => title,
                :description => CGI.escapeHTML(description),
                :author => author
            }
        end

        response = request.to_hash[:judge_create_problem_response]
        @insert_problem_code = response[:return]

        if @insert_problem_code.to_i > 0
            @problem_saved = true
            @problem_saved_id = @insert_problem_code
            @problem_title = parameters[:title]
            @problem_statement = parameters[:description]
            @problem_author = author

            @test_cases = []
            id = @insert_problem_code.to_i
            1.upto(TEST_CASES_PER_PROBLEM) do |tc|
                input_key  = "in_" + tc.to_s
                output_key = "out_" + tc.to_s
                request = client.request "Judge.save_test_case" do
                    soap.body = {
                        :user => current_user.name,
                        :password => current_user.password,
                        :id_problem => id,
                        :input => CGI.escapeHTML(params[input_key]),
                        :output => CGI.escapeHTML(params[output_key])
                    }
                end

                response = request.to_hash[:judge_save_test_case_response]
                test_id = response[:return].to_i
                @test_cases << {"id" => test_id, "in" => params[input_key],
                                "out" => params[output_key]}
            end

            render 'saved'
        else
            msg = "Ocurrio un error al intentar guardar el problema."
            @problem.errors.add("Error:", msg)
            render 'new'
        end

    end
end

```

### Envio de una solución

El formulario para el envio de soluciones se localiza en el archivo _app/views/solutions/new.html.erb_. El controlador **Solutions** es el que se encarga de la lógica de esta operación:


```rb
def create
  @id_problem = params[:id_problem]
  @id_user = params[:id_user]
  @source_code = params[:source_code]
  @language = params[:language]

  client = Savon::Client.new do
      wsdl.document = WSDL_LOCATION
  end

  request = client.request "Judge.save_solution" do
      soap.body = {
          :user => current_user.name,
          :password => current_user.password,
          :id_problem => params[:id_problem],
          :source_code => params[:source_code],
          :language => params[:language]
      }
  end

  response = request.to_hash[:judge_save_solution_response]
  @submission_answer = response[:return]

  if @submission_answer[:error].to_i == SU_COMPILATION
      id = @submission_answer[:id].to_i
      request = client.request "Judge.test_solution" do
          soap.body = { 
              :user => current_user.name,
              :password => current_user.password,
              :id_solution => id,
          }
      end

      response = request.to_hash[:judge_test_solution_response]
      @test_results = response[:return][:item]
  else
      request = client.request "Judge.get_last_error"
      response = request.to_hash[:judge_get_last_error_response]
      @error_message = response[:message]
  end

  render 'submission_result'
end

```

Estas son las partes más importantes, creo que con esto podrán entender el resto de las operaciones.

### Notas sobre el uso de la base de datos en ROR

Como habrán  observado, empleamos tres tablas para almacenar nuestros datos, sin embargo, los datos nunca son almacenados en estas tablas ya que todo se envía al servidor remoto, esta es una alteración que he tenido que realizar para aprovechar las facilidades de Ruby on Rails pero a la vez cumplir con el requisito de emplear un Web service.

Al utilizar los modelos que proporciona Rails se nos facilita mucho la creación de formularios y la validación de los datos.

Si prescindiéramos del Web service y empleáramos las bases de datos nativas de Rails, la complejidad del cliente sería mucho menor.

## Código fuente

El código tanto del cliente como del servidor están disponibles en Bitbucket en las siguientes direcciones:

<ul>
  <li>[https://bitbucket.org/rendon/microoj](https://bitbucket.org/rendon/microoj/admin)</li>
  <li>[https://bitbucket.org/rendon/microoj_ws](https://bitbucket.org/rendon/microoj_ws)</li>
</ul>

O bien pueden clonar los repositorios desde la consola:


```sh
$ git clone https://rendon@bitbucket.org/rendon/microoj.git
$ git clone https://rendon@bitbucket.org/rendon/microoj_ws.git

```

La licencia de ambos proyectos es GPLv3, con excepción de los componentes empleados, los cuales tienen sus propias licencias.

## Por hacer

Un sistema de juez en línea es más complejo de lo que se muestra en esta práctica, a continuación se listan algunas características deseables:

<ul>
  <li>Mejorar el manejo de usuarios. Que los usuarios puedan ver el perfil de los demás participantes y ver su progreso.</li>
  <li>Reportar estadísticas de cada usuario, como son, problemas resueltos, número de intentos, cuantos de ellos ha sido aceptados, cuantos rechazados, etc. Toda esta información debería ser mostrada en el perfil del usuario.</li>
  <li>Implementar un sistema de *Ranking*, en mi experiencia, esto es un factor de motivación.</li>
  <li>**RETO:** Soportar concursos en tiempo real.</li>
</ul>

## Referencias

- [Web Services Architecture](http://www.w3.org/TR/ws-arch/)
- [Creating Web Services with PHP and SOAP](http://www.sitepoint.com/web-services-with-php-and-soap-1/) 
- [Documentación de NuSOAP](http://nusoap.sourceforge.net/)
- [Ubuntu, Ruby, RVM, Rails, and You](http://ryanbigg.com/2010/12/ubuntu-ruby-rvm-rails-and-you/)
- [Ruby on Rails Tutorial](http://ruby.railstutorial.org/)
- [Documentación de Savon](http://savonrb.com/)
