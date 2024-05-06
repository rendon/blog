<% title = 'Configurar Entorno LAMP' %>
<p>Como parte de un reporte de proyecto necesito un manual sobre como instalar y configurar un entorno LAMP (Linux + Apache + MySQL + PHP), si bien es cierto que en Internet hay gran cantidad de tutoriales, para mi reporte necesito una fuente confiable, algo de lo que este yo seguro de que funciona, y como dice el dicho, si quieres algo bien hecho, hazlo tu mismo. En este tutorial vamos a ver como obtener y configurar un entorno LAMP en GNU/Linux Debian Wheezy.</p>

## Instalación

<p>Si tienes bien configurados tus repositorios lo único que tienes que hacer es ejecutar el siguiente comando como usuario root:</p>

Embed: `install.sh`

<p>El comando anterior instala y configura el servidor HTTP Apache, version 2.x, el servidor MySQL (actualmente la versión 5.x), la versión 5.x del lenguaje PHP y por último el módulo que permite manipular bases de datos MySQL desde PHP.</p>

<p>Por defecto Apache y MySQL estan configurados para ejecutarse cada vez que iniciemos el sistema, sin embargo esto llega a consumir muchos recursos, los siguientes comandos harán que los servicios se inicien de forma manual.</p>

Embed: `remove-services.sh`

<p>Para iniciar y/o apagar Apache utiliza estos comandos:</p>

Embed: `start-stop-apache.sh`

<p>Para MySQL:</p>

Embed: `start-stop-mysql.sh`

<p>Todo esto como usuario root, por supuesto.</p>
