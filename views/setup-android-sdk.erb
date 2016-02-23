"=========== Meta ============
"StrID : 825
"Title : Instalación y configuración del Android SDK
"Slug  : setup-android-sdk
"Cats  : 
"Tags  : 
"=============================
"EditType   : post
"EditFormat : markdown
"TextAttach : vimpress_53796785_mkd.txt
"========== Content ==========
Como parte de un reporte de proyecto necesito un manual sobre como instalar y configurar el SDK de Java, si bien es cierto que en Internet hay gran cantidad de tutoriales, para mi reporte necesito una fuente confiable, algo de lo que este yo seguro de que funciona, y como dice el dicho, si quieres algo bien hecho hazlo tu mismo. En este tutorial vamos a ver como obtener y configurar el Android SDK en GNU/Linux Debian Wheezy.


[php]section("Descargar el Android SDK");[/php]

Ve a la pagina principal para desarrolladores android y en la sección SDK (<a href="https://developer.android.com/sdk/index.html">https://developer.android.com/sdk/index.html</a>) descarga la versión para Linux que corresponda a tu plataforma(32 o 64 bits). Hay dos formas de trabajar con android, con un plugin para Eclipse (ADT Bundle) o desde la línea de comandos (SDK Tools Only), nosotros vamos a emplear ésta última opción pues es ideal para familiarizarse con el SDK.
El archivo tiene un nombre parecido a <code>android-sdk_r22.x.x-linux.tgz</code> y pesa aproximadamente 100 MB.


[php]section("Instalación");[/php]

El archivo que acabamos de descargar contiene los binarios del SDK, por lo que no habra que compilar nada, únicamente descomprimirlo en un directorio adecuado, en nuestro caso lo haremos en el directorio <code>/opt</code>. Como usuario <strong>root</strong> ejecuta los siguientes comandos.

<pre lang="bash" theme="slate">
mv /home/usuario/descargas/android-sdk_r22.x.x-linux.tgz /opt
cd /opt
tar xvf android-sdk_r22.x.x-linux.tgz
</pre>

El último comando debio crear un direcotorio con el nombre <code>android-sdk-linux</code> dentro del directorio <code>/opt</code>.

[php]section("Registrar el SDK en la variable de entorno PATH");[/php]

La variable de entorno PATH es es una variable especial ya que almacena los nombres de los directorios donde el sistema busca los programas instalados, nosotros vamos a registrar el SDK para que cuando ejecutamos algun programa del SDK, el sistema sepa donde encontrarlo. Abrimos el archivo <code>.bashrc</code> ubicado en el directorio home y agregamos la siguiente línea.

<pre lang="bash" theme="slate">
export PATH="${PATH}:/opt/android-sdk-linux/tools:/opt/android-sdk-linux/platform-tools"
</pre>


[php]section("Descargar la API");[/php]

Una API es una interfaz que proporciona facilidades a los desarrolladores para que puedan crear aplicaciones sin tanto problema puesto que abstrae la complejidad y el desarrollador se concentra más en el <em>qué</em> y no en el <em>cómo</em>. La API de Android es una colección de classes en Java que por defecto no se incluyen el archivo que descargamos y será necesario descargarlas de internet. En la línea de comandos ejecuta el comando <code>android</code>, les aparecerá la siguiente ventana.

[php]figure('android_sdk_01','Administrador del Android SDK', '', 'png', 'ES');[/php]

Nosotros vamos a desarrollar una aplicación para la versión 2.3 de Android (Versión 10 de la API) por lo que selecionaremos esa opción y procederemos a descargar.

[php]section("Ant");[/php]

Ant es una herramienta para administrar la compilación de aplicaciones Java, esta no se incluye en el SDK de Android y es necesario que se instale. En la línea de comandos ejecuta el siguiente comando como <strong>root</strong>.

<pre lang="bash" theme="slate">
apt-get install ant
</pre>

[php]section("Crear una máquina virtual para las pruebas");[/php]

El SDK de android incluye un emulador quen nos permite desarrollar aplicaciones incluso si no tenemos un dispositivo con sistema operativo Android, o simplemente para no hacer trabajar mucho a tu smartphone. Para utilizar el emulador primero debenos crear un dispositivo virtual. En la línea de comandos ejecuta el comando <code>android avd</code> y nos aparecerá la siguiente ventana.

[php]figure('android_sdk_02','Creación de un dispositivo virtual', '', 'png', 'ES');[/php]

Elegimos la opción "New" para crear un dispositivo virtual, en esa ventana proporcionamos el nombre para el dispositivo y utilizamos los valores que se muestran en la imagen.

[php]figure('android_sdk_03','Creación de un dispositivo virtual', '', 'png', 'ES');[/php]

Para ejecutar el emulador con la imagen recien creada utiliza el siguiente comando en una terminal.

<pre lang="bash" theme="slate">
emulator @Gingebread2
</pre>


[php]section("Configurar un dispositivo real");[/php]

Al final de cuentas lo que pretendemos es ejecutar nuestras aplicaciones en un dispositivo de verdad, para ello es necesario realizar algunas configuraciones para que el sistema operativo reconozca nuestro dispositivo. Como usuario root vamos a crear un archivo llamado <code>51-android.rules</code> dentro del directorio <code>/etc/udev/rules.d/</code> con el siguiente contenido.

<pre lang="bash" theme="slate">
SUBSYSTEM=="usb", ATTR{idVendor}=="0bb4", MODE="0666", GROUP="plugdev"
</pre>

El id <strong>0bb4</strong> corresponde a los dispositivos HTC. Vease la documentación oficial en <a href="https://developer.android.com/tools/device.html">https://developer.android.com/tools/device.html</a> para saber el id de otros dispositivos y más información sobre este tema.

[php]section("Verificación");[/php]

Solo resta verificar si todo esta correcto. Para ello vamos a crear un proyecto "¡Hola mundo!". Dentro de una terminal posicionate en tu directorio home y ejecuta los siguiente comandos.

<pre lang="bash" theme="slate">
mkdir HolaMundo
android create project --target android-10 -n HolaMundo -a HolaMundo -k com.inforscience.test -p ./HolaMundo
</pre>

El significado de los parametros del comando anterior es el siguiente:

<ul>
<li><code>--target</code> Para qué versión de Android será la aplicación, en nuestro caso es Android 2.3, <code>target-10</code> porque es la versión 10 de API.</li>
<li><code>-n</code> Nombre del proyecto.</li>
<li><code>-k</code> Nombre del paquete.</li>
<li><code>-a</code> Nombre de la actividad principal.</li>
<li><code>-p</code> Folder del proyecto.</li>
</ul>

Para compilar e instalar la aplicación de prueba ejecuta los siguientes comandos.

<pre lang="bash" theme="slate">
cd HolaMundo
ant debug
ant debug install
</pre>

El último comando buscará algún dispositivo Android conectado al sistema o una máquina virtual activa e instalará el programa ahí.

[php]figure('android_sdk_04','Aplicación HolaMundo corriendo en el emulador Android', '', 'png', 'ES');[/php]

Ahora estamos listos para empezar a desarrollar para Android. ¡Suerte!
