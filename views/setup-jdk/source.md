<!-- vim: set spelllang=es_mx: -->

# Installar SDK de java
2016-02-18 2024-05-07 #dev #java #post

Como parte de un reporte de proyecto necesito un manual sobre como instalar y configurar el SDK de Java, si bien es cierto que en Internet hay gran cantidad de tutoriales, para mi reporte necesito una fuente confiable, algo de lo que este yo seguro de que funciona, y como dice el dicho, si quieres algo bien hecho hazlo tu mismo. En éste artículo vamos a indicar como obtener y configurar el JDK en el sistema operativo GNU/Linux Debian Wheezy.

**NOTA:** Vamos a partir del supuesto de que no existe una instalación previa del JDK, si es así, asegúrate de desinstalarla porque puede ocasionar problemas, puedes apoyarte de *synaptic*.

## Descargar el JDK

Ve al sitio oficial de Java, [http://www.oracle.com/technetwork/java/javase/downloads/](http://www.oracle.com/technetwork/java/javase/downloads/) y descarga la versión más reciente, en la fecha en que se escribe este documento es la versión 7. El archivo a descargar tiene un nombre parecido a  *jdk-7uxx-linux-xxxx.tar.gz* y pesa alrededor de 90 MB.

## Instalación

El archivo que acabamos de descargar contiene los archivo binarios del JDK por lo que no hay que compilar nada, únicamente descomprimirlo en un lugar adecuado, nosotros vamos a usar el directorio `/opt`, como usuario **root** ejecuta los siguientes comandos.

<pre lang="bash" theme="slate">
mv /home/nombre_de_usuario/descargas/jdk-7uxx-linux-xxxx.tar.gz /opt/
cd /opt
tar xvf jdk-7uxx-linux-xxxx.tar.gz
</pre>

El último comando debió crear una carpeta con un nombre parecido `jdk1.7xxx` dentro del directorio `/opt`. Ten cuidado de no teclear los comandos literalmente, tienes que emplear los valores que correspondan en tu caso.

## Configurar la variable de entorno JAVA_HOME

Una variable de entorno almacena valores que el sistema y algunas aplicaciones utilizan para ubicar recursos, en este caso la ubicación de los compiladores y la máquina virtual de Java. Es muy importante que no se omita este paso.

Con tu editor de texto favorito(vim, nano, gedit, etc) abre el archivo `.bashrc` ubicado en el directorio home y agrega la siguiente línea. Asegúrate de remplazar las "xxx" por lo valores reales.

<pre lang="bash" theme="slate">
export JAVA_HOME=/opt/jdk1.7xxx
</pre>

Para verificar que todo esta correcto, abre otra terminal y ejecuta el siguiente comando.

<pre lang="bash" theme="slate">
echo $JAVA_HOME
/opt/jdk1.7xxx
</pre>

Si el comando anterior no imprime nada es que algo salio mal y habrá que repetir el procedimiento con más cuidado.
