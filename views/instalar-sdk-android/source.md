<!-- vim: set spelllang=es_MX: -->

---
tags:
    - dev
    - android
    - post
created: 2016-02-18
updated: 2024-05-07
---
# Instalar SDK de Android

Como parte de un reporte de proyecto necesito un manual sobre como instalar y configurar el SDK de Java, si bien es cierto que en Internet hay gran cantidad de tutoriales, para mi reporte necesito una fuente confiable, algo de lo que este yo seguro de que funciona, y como dice el dicho, si quieres algo bien hecho hazlo tu mismo. En este tutorial vamos a ver como obtener y configurar el Android SDK en GNU/Linux Debian Wheezy.

## Descargar el Android SDK

Ve a la pagina principal para desarrolladores android y en la sección SDK ([https://developer.android.com/sdk/index.html](https://developer.android.com/sdk/index.html)) descarga la versión para Linux que corresponda a tu plataforma(32 o 64 bits). Hay dos formas de trabajar con android, con un plugin para Eclipse (ADT Bundle) o desde la línea de comandos (SDK Tools Only), nosotros vamos a emplear ésta última opción pues es ideal para familiarizarse con el SDK.
El archivo tiene un nombre parecido a `android-sdk_r22.x.x-linux.tgz` y pesa aproximadamente 100 MB.


## Instalación

El archivo que acabamos de descargar contiene los binarios del SDK, por lo que no habra que compilar nada, únicamente descomprimirlo en un directorio adecuado, en nuestro caso lo haremos en el directorio `/opt`. Como usuario **root** ejecuta los siguientes comandos.

```
mv /home/usuario/descargas/android-sdk_r22.x.x-linux.tgz /opt
cd /opt
tar xvf android-sdk_r22.x.x-linux.tgz
```

El último comando debio crear un direcotorio con el nombre `android-sdk-linux` dentro del directorio `/opt`.

## Registrar el SDK en la variable de entorno PATH

La variable de entorno PATH es es una variable especial ya que almacena los nombres de los directorios donde el sistema busca los programas instalados, nosotros vamos a registrar el SDK para que cuando ejecutamos algun programa del SDK, el sistema sepa donde encontrarlo. Abrimos el archivo `.bashrc` ubicado en el directorio home y agregamos la siguiente línea.

```
export PATH="${PATH}:/opt/android-sdk-linux/tools:/opt/android-sdk-linux/platform-tools"
```


## Descargar la API

Una API es una interfaz que proporciona facilidades a los desarrolladores para que puedan crear aplicaciones sin tanto problema puesto que abstrae la complejidad y el desarrollador se concentra más en el *qué* y no en el *cómo*. La API de Android es una colección de classes en Java que por defecto no se incluyen el archivo que descargamos y será necesario descargarlas de internet. En la línea de comandos ejecuta el comando `android`, les aparecerá la siguiente ventana.

![Administrador del Android SDK](/setup-android-sdk/android_sdk_01.png)

Nosotros vamos a desarrollar una aplicación para la versión 2.3 de Android (Versión 10 de la API) por lo que selecionaremos esa opción y procederemos a descargar.

## Ant

Ant es una herramienta para administrar la compilación de aplicaciones Java, esta no se incluye en el SDK de Android y es necesario que se instale. En la línea de comandos ejecuta el siguiente comando como **root**.

```
apt-get install ant
```

## Crear una máquina virtual para las pruebas

El SDK de android incluye un emulador quen nos permite desarrollar aplicaciones incluso si no tenemos un dispositivo con sistema operativo Android, o simplemente para no hacer trabajar mucho a tu smartphone. Para utilizar el emulador primero debenos crear un dispositivo virtual. En la línea de comandos ejecuta el comando `android avd` y nos aparecerá la siguiente ventana.

![Creación de un dispositivo virtual](/setup-android-sdk/android_sdk_02.png)

Elegimos la opción "New" para crear un dispositivo virtual, en esa ventana proporcionamos el nombre para el dispositivo y utilizamos los valores que se muestran en la imagen.

![Creación de un dispositivo virtual](/setup-android-sdk/android_sdk_03.png)

Para ejecutar el emulador con la imagen recien creada utiliza el siguiente comando en una terminal.

```
emulator @Gingebread2
```


## Configurar un dispositivo real

Al final de cuentas lo que pretendemos es ejecutar nuestras aplicaciones en un dispositivo de verdad, para ello es necesario realizar algunas configuraciones para que el sistema operativo reconozca nuestro dispositivo. Como usuario root vamos a crear un archivo llamado `51-android.rules` dentro del directorio `/etc/udev/rules.d/` con el siguiente contenido.

```
SUBSYSTEM=="usb", ATTR{idVendor}=="0bb4", MODE="0666", GROUP="plugdev"
```

El id **0bb4** corresponde a los dispositivos HTC. Vease la documentación oficial en [https://developer.android.com/tools/device.html](https://developer.android.com/tools/device.html) para saber el id de otros dispositivos y más información sobre este tema.

## Verificación

Solo resta verificar si todo esta correcto. Para ello vamos a crear un proyecto "¡Hola mundo!". Dentro de una terminal posicionate en tu directorio home y ejecuta los siguiente comandos.

```
mkdir HolaMundo
android create project --target android-10 -n HolaMundo -a HolaMundo -k com.inforscience.test -p ./HolaMundo
```

El significado de los parametros del comando anterior es el siguiente:

<ul>
<li>`--target` Para qué versión de Android será la aplicación, en nuestro caso es Android 2.3, `target-10` porque es la versión 10 de API.</li>
<li>`-n` Nombre del proyecto.</li>
<li>`-k` Nombre del paquete.</li>
<li>`-a` Nombre de la actividad principal.</li>
<li>`-p` Folder del proyecto.</li>
</ul>

Para compilar e instalar la aplicación de prueba ejecuta los siguientes comandos.

```
cd HolaMundo
ant debug
ant debug install
```

El último comando buscará algún dispositivo Android conectado al sistema o una máquina virtual activa e instalará el programa ahí.

![Aplicación HolaMundo corriendo en el emulador Android](/setup-android-sdk/android_sdk_04.png)

Ahora estamos listos para empezar a desarrollar para Android. ¡Suerte!
