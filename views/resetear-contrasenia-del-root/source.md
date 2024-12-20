<!-- vim: set spelllang=es_MX: -->

---
tags:
    - sysadminuuulinux
    - post
created: 2016-02-18
updated: 2024-05-07
---
# Retear contrasenia del usuario root

## Problema
Hoy quiero hablarles de cómo **resetear** la contraseña del super usuario en GNU/Linux por si lo llegan a necesitar :-).

Es necesario remarcar que se trata de **resetear**, más no de revelar la contraseña existente, con lo cual no seremos capaces de conocer la contraseña del usuario root, si no más bien reemplazar la contraseña actual.

Situaciones en las que nos sea útil esta información sobran, una muy usual, no hicimos caso al que instalo el sistema operativo cuando nos decía que deberíamos de guardar bien la contraseña del usuario root tachándolo de exagerado y esas cosas...Días después cuando te bajas un programa para descargar música(...digamos frostwire) y no avanzado mucho el proceso de instalación se te pide la contraseña de Administrador del sistema y ...¿Contraseña? ¿Cuál contraseña? Mmmm...  y después de unos instantes pensando se ilumina el rostro del usuario y "Ah!, si claro, la que debería de ... Guardar bien". Pero el caso es que no sabes donde la guardaste o incluso, ni siquiera la guardaste!!!

Esta situación que podría parecer trivial resulta que no lo es, ya que una medida "atrevida" sería reinstalar el sistema, incluso.  En las siguientes líneas les explico como salir de estas situaciones. Este método lo he probado en las distribuciones Debian Lenny, en Slackware 13 y openSuse 11.1, sobre la cuales puedo asegurar que el método funciona, más sin embargo pienso que tiene que funcionar para la mayoría de las distribuciones que utilicen un núcleo de versión cercana. 

## Debian lenny y openSuse con GRUB

### Paso 1

Iniciamos la computadora y antes de cargar el sistema presionamos la tecla <kbd>e</kbd> para editar las opciones de arranque (en el caso de openSuse es necesario presionar la tecla <kbd>Esc</kbd> previamente para salir del modo gráfico), y nos aparecerán 3 líneas de comandos , la primera que empieza con `root(hdx,0)`, la segunda inicia con `kernel` y la tercera con `initrd`, la línea que nos interesa es la segunda, la que inicia con *kernel*, presionamos la letra `e` para editar las opciones. Haremos 2 modificaciones, lo primero será ubicar dentro de las opciones el texto `ro`,(read only) y lo sustituiremos por `rw`(read and write), para tener derechos de escritura sobre los archivos de contraseñas. La segunda modificación será añadir la siguiente instrucción al final de la línea de opciones:

```init=/bin/bash```

La línea tiene que quedar más o menos así: 

```kernel /boot/vmlinuz-2.6.18-5-486 root=/dev/hda2 rw vga=791 init=/bin/bash ```

Ahora solo presionar <kbd>Enter</kbd> y posteriormente presionar la tecla <kbd>b</kbd> para empezar con la carga del sistema...Si todo se hizo bien en unos instantes nos aparecerá el prompt del sistema en modo root, por lo general el indicador es el `#`, aunque en openSuse por ejemplo esto no es así, pero no hay de que preocuparse, si se esta como root.

### Paso 2

Ya en este punto del proceso solo resta ejecutar el comando `passwd` para hacer el cambio de la contraseña del root. Tecleamos la nueva contraseña y confirmamos.

Después de cambiar la contraseña simplemente tenemos que reiniciar  y Listo!. Ah por cierto, el comando `shutdown` no funciona en ese momento, es necesario usar el comando `halt`.

### Slackware con LILO

Con slackware el proceso cambia un poquito solo en el primer paso ya que el gestor de arranque es LILO(por defecto) en ves del GRUB y por ende las opciones de carga se configuran un poco diferente.

Iniciamos el ordenador y antes de que se cargue el sistema por presionamos la tecla <kbd>Tab</kbd> para editar las opciones de arranque, seleccionamos a `Linux` como sistema a cargar y después de eso agregamos `bin=/bin/bash` quedando como sigue:

``` boot: Linux init=/bin/bash ```

En seguida presionamos <kbd>Enter</kbd> para que cargue en sistema.

Ya una ves estando en el prompt como root tenemos que *remontar* el sistema de archivos para que sea de lectura y escritura(no lo pusimos en las opciones de arranque). Ejecutamos el siguiente comando: 

```mount -o remount,rw /```

Después de esto el siguiente paso es ejecutar  el comando `passwd`, y todo lo demás.

## Conclusión

Con estos sencillos pasos seremos capaces de resetear la contraseña del root sin tanta complicación. Ahora si a guardar bien el password para no estar con esto a cada rato. Espero les sea de utilidad. Hasta la próxima!
