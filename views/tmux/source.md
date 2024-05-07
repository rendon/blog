<!-- vim: set spelllang=es_mx: -->

# Tmux
2016-02-18 2024-05-07 #sysadmin #tools #post

**NOTA**: Este artículo fue publicado originalmente en [ATIX](http://revista.atixlibre.org/?p=259), revista de software libre.

<blockquote>
Tmux es un multiplexor de terminal: posibilita que una o más de terminales, cada una ejecutando un programa por separado,  puedan crearse, accederse y controlarse desde una sola pantalla.
</blockquote>

Hace seis años aproximadamente empece a usar el sistema operativo GNU/Linux, casi el mismo tiempo en el que me inicie en la programación, cuando aun cursaba el bachillerato. Hoy soy estudiante de ingeniería, próximo a graduarme, puedo decir que GNU/Linux es el mejor entorno de desarrollo que he conocido.

A lo largo de estos años he aprendido a utilizar el SO y algunas herramientas que me han ayudado a realizar mi trabajo de manera más fácil y eficiente, y que considero, debería ser el kit básico de todo desarrollador.

En este tiempo también he conocido a algunos programadores, la mayoría de ellos usuarios de Windows, dependientes de las GUIs y de los IDEs, demorando demasiado en tareas que bien se podrían automatizar empleando las herramientas adecuadas. En la edición 2012 del CONACUP, un concursante que terminó por sentarse a lado mio, no pudo siquiera intentar resolver los problemas propios del evento debido a que paso la mayor parte del tiempo cambiándose de máquina en máquina porque eclipse se le bloqueaba. Verídico.

Tiempo atrás leí una pregunta muy popular en StackOverflow, *C++ IDE for Linux?*, muchas respuestas y comentarios, de entre ellos destacó uno: *UNIX is an IDE. All of it.*, lo cual me hizo recordar cual fue el propósito inicial de UNIX, un sistema para programadores.


Estamos iniciando el año y he decidido comenzar una serie de artículos que titulo *"Herramientas de un desarrollador"* como son:

<ul>
  <li>Multiplexor de terminal: tmux</li>
  <li>Línea de comandos: Bash</li>
  <li>Editor de texto: Vim y/o emacs </li>
  <li>Utilerías: grep, find, sed, etc.</li>
  <li>Sistema de control de versiones: git</li>
</ul>

Lo único que se necesita para seguir estos artículos es un emulador de terminal(xterm, gnome-terminal, konsole, etc.) y ganas de aprender. Puesto que vamos a dedicar mucho tiempo trabajando en línea de comandos es vital una herramienta que nos permita administrar terminales en forma eficiente, esta herramienta se llama tmux y es el tema de esta primer entrega.

## ¿Qué es tmux?

En electrónica un multiplexor es un dispositivo que permite trasmitir varios mensajes o señales de manera simultanea sobre un canal de comunicación. Tmux es un multiplexor de terminal, esto es, posibilita que una o más de terminales(o ventanas), cada una ejecutando un programa por separado, puedan accederse y controlarse desde una sola pantalla. 

En mis actividades diarias empleo muy a menudo una o más terminales, cuando programo utilizo como mínimo dos, en una tengo abierto vim y en la otra realizo las pruebas. Antes yo solía tener dos terminales abiertas en dos ventanas, usando Ctrl + Tab para moverme entre ellas, pero con el tiempo esto se volvió tedioso y mi vista se cansaba fácilmente debido a los constantes destellos del cambio de ventanas. Investigando un poco conocí GNU Screen, no me gusto. Descubrí tmux y fue exactamente lo que andaba buscando.

![Antes](/tmux/hdud1_0.png)

![Después](/tmux/hdud1_1.png)

## Instalación

Para los usuarios de distribuciones Debian, Ubuntu, CentOS, Fedora, etc. es muy probable que puedan instalar tmux directamente con el gestor de paquetes o bien pueden compilarlo desde código fuente, nada complicado.

### Con el gestor de paquetes


```sh
# Debian y Ubuntu
$ sudo apt-get install tmux

```

## Desde código fuente

Ve al sitio oficial de tmux([https://tmux.github.io/](https://tmux.github.io/)) y descarga el código fuente, yo estoy empleando la versión 1.6. Por cierto, tmux depende de `libevent` y `ncurses`.


```sh
$ # Instalar dependencias
$ sudo apt-get install libevent-dev libncurses5-dev
$
$ cd ~/Downloads/
$ tar xvf tmux-1.6.tar.gz
$ cd tmux-1.6/
$ ./configure
$ make
$ sudo make install
$
$ # Prueba la instalacion
$ tmux -V

```

## Lo básico

Para empezar a usar tmux abre una terminal y ejecuta tmux, teclea el comando exit para salir. Tmux al igual que vim es modal, el modo por defecto es el que nos permite interactuar con la terminal. Los otros modos son:

<ul>
<li>**output mode**: Entramos a este modo cuando un comando que produce una salida, tal como list-keys, es ejecutado con una combinación de teclas.</li>
<li>**copy mode**: Este modo permite copiar texto de las ventanas, del historial o de la salida producida por otros programas.</li>
</ul>

### El prefijo de comandos

<p>El prefijo de comandos es una combinación de teclas que avisa a tmux que estamos a punto de indicarle una acción que debe realizar, por defecto esta combinación es <kbd>Ctrl</kbd> + <kbd>b</kbd>, <kbd>PREFIX</kbd> de aquí en adelante. La instrucción <kbd>PREFIX</kbd> + <kbd>c</kbd> se traduce en presionar las teclas <kbd>Ctrl</kbd> y <kbd>b</kbd> simultáneamente, soltar las teclas y después presionar la letra <kbd>c</kbd>. </p>
Tmux tiene un comando para cada acción y una serie de keybindings para ejecutar algunos de ellos con una combinación de teclas, de esto hablaremos más adelante. Para entrar en modo de comandos presiona <kbd>PREFIX</kbd> + <kbd>:</kbd> y teclea el comando.

### Copy mode

<p>Como ya se menciono, en este modo podemos navegar por el contenido que se ha generado en la terminal y copiar texto si así lo queremos. Presiona <kbd>PREFIX</kbd> + <kbd>[</kbd> para entrar en este modo.</p>

### Paneles

Tmux permite dividir el área de trabajo en varias partes, llamadas paneles, estas pueden ser horizontales o verticales.


```txt
# Creación de panel horizontal
# Combinación     Comando
PREFIX + "      (split-window)

# Creación de panel vertical
PREFIX + %      (split-window -h)

# Moverse al siguiente panel
PREFIX + o      (select-pane -t :.+)

#Moverse al al panel superior, inferior, izquierdo y derecho

PREFIX + UP     (select-pane -U)
PREFIX + DOWN   (select-pane -D)
PREFIX + LEFT   (select-pane -L)
PREFIX + RIGHT  (select-pane -R)

```

![Splits](/tmux/hdud1_2.png)

<p>Una combinación muy util para moverse entre paneles es <kbd>PREFIX</kbd> + <kbd>q</kbd>, que enumera cada uno de los paneles por un momento, presiona el numero del panel al cual te quieres trasladar y listo.</p>

![Paneles enumerados](/tmux/hdud1_3.png)

Si necesitas reducir o aumentar el área de un panel lo puedes hacer con las siguientes combinaciones.

### Aumentar o reducir el panel verticalmente.


```txt
PREFIX + C-UP     (resize-pane -U)
PREFIX + C-DOWN   (resize-pane -D)

```

### Aumentar o reducir el panel horizontalmente.


```txt
PREFIX + C-LEFT   (resize-pane -L)
PREFIX + C-RIGHT  (resize-pane -R)

```

<p>Para cerrar un panel tenemos dos opciones, terminar la sesión en la terminal con el comando exit o presionando <kbd>PREFIX</kbd> + <kbd>x</kbd>, que cierra el panel con previa confirmación.</p>

### Organizando paneles

Tmux proporciona cinco plantillas que nos permiten organizar nuestros paneles.

<ul>
<li>**even-horizontal**: Alinea todos los paneles horizontalmente, de izquierda a derecha. </li>
<li>**even-vertical**: Alinea todos los paneles verticalmente, de arriba a abajo. </li>
<li>**main-horizontal**: Crea un panel en la parte superior que ocupa casi todo el espacio de la pantalla y alinea el resto de los paneles en la parte inferior. </li>
<li>**main-vertical**: Crea un panel en el lado izquierdo que ocupa casi todo el espacio de la pantalla y alinea el resto de los paneles a la derecha.</li>
<li>**tiled**: Alinea todos los paneles en la pantalla con igual cantidad de espacio.</li>
</ul>

<p>Presiona <kbd>PREFIX</kbd> + <kbd>Espacio</kbd> para probar cada plantilla.</p>

### Ventanas

Cuando los paneles no son suficientes o deseamos agrupar las terminales segun su actividad contamos con las ventanas.

<h6>Crear una ventana.</h6>

```txt
PREFIX + c

```

Las ventanas tienen nombre y lo podemos modificar con:


```txt
PREFIX + ,

```

<h6>Moverse entre ventanas.</h6>

```txt
PREFIX + n # Siguiente
PREFIX + p # Anterior

```

![Ventanas](/tmux/hdud1_4.png)

<p>El listado de ventanas activas se muestra en la parte inferior de la pantalla, cada ventana tiene un número que la identifica. Una forma fácil de cambiar de ventana es presionando <kbd>PREFIX</kbd> + numero_de_ventana. Si tienes demasiadas ventanas también es posible buscarlas por su nombre con <kbd>PREFIX</kbd> + <kbd>f</kbd> o bien presionar <kbd>PREFIX</kbd> + <kbd>w</kbd> para mostrar el listado de ventanas.</p>

### Sesiones

Una sesión es una colección de pseudo terminales(ver man 7 pty) que son administradas por tmux. Cada sesión tiene una o más ventanas asociadas a ella. Las sesiones son persistentes y mantendrán su estado en caso de una desconexión. Aquí va un punto importante, si un programa se esta ejecutando cuando la sesión se interrumpe éste continuara su ejecución cuando la sesión sea reanudada.

En otras palabras las sesiones sirven para crear entornos de trabajo personalizados, por ejemplo, si están trabajando en un proyecto y tienes abiertos varios archivos, un terminal interactivo de Ruby o Python, varias ventanas, etc. Si por alguna razón tienes que interrumpir tus actividades, resultaría un poco molesto tener que cerrar archivos, programas, paneles y ventanas, y una hora más tarde cuando regresas a trabajar, restablecer el entorno. La solución es crear una sesión y le asignamos un nombre acorde, si trabajas en más de un proyecto o tarea simplemente crea otra sesión y mantendrás tus áreas de trabajo organizadas.
Aunque no lo indiquemos explícitamente tmux crea una sesión de forma automática cada vez que lo ejecutamos.


```txt
#Crear una sesión:
$ tmux new -s nombre_de_sesion

#Cerrar sesión:
PREFIX + d

#o bién:
$ tmux kill-session -t nombre_de_sesion

#Listar sesiones existentes:
$ tmux list-sessions

#Abrir sesión cuando solo existe una:
$ tmux attach

#Abrir una sesión en especifico:
$ tmux attach -t nombre_de_sesion

```

## Configuración y personalización

Hasta ahora hemos cubierto lo esencial, usando las configuraciones por defecto, sin embargo éstas no siempre son las más cómodas para todos, es por eso que tmux nos admite ser personalizado usando el archivo `~/.tmux.conf`. A continuación muestro algunas de las opciones disponibles:


```txt
# Soporte para 256 colores.
set -g default-terminal "screen-256color"

# Cambiar PREFIX a Ctrl + a, más cómodo.
set-option -g prefix C-a
unbind-key C-b
bind-key C-a send-prefix

#Como dividir la pantalla de forma más intuitiva
# | en vez de %
bind | split-window -h
# - en vez de "
bind - split-window -v

#Cambiando el el atajo para entrar al modo copy.
bind-key e copy-mode

```

Tmux soporta los modos vi y emacs para moverse dentro de la aplicación, por defecto el modo emacs es activado. Activar modo vi y algunos atajos.


```txt
setw -g mode-keys vi
bind-key -t vi-copy 'v' begin-selection
bind-key -t vi-copy 'y' copy-selection

```

<p>Con estas opciones activadas, haz lo siguiente para copiar contenido dentro de tmux, **1)** entra en modo copy, **2)** presiona la tecla v para iniciar la selección y muevete con las teclas <kbd>hjkl</kbd>, como en vim, **3)** presiona la tecla y para copiar la selección.</p>

### Moverse entre los paneles de manera similar a vim con los splits.


```txt
# Presiona PREFIX + [jkhl]
# para cambiar de panel
unbind-key j
bind-key j select-pane -D
unbind-key k
bind-key k select-pane -U
unbind-key h
bind-key h select-pane -L
unbind-key l
bind-key l select-pane -R

```

### Cambia el modo de redimencionar paneles.


```txt
# Presiona Ctrl + a + [jkhl]
# para redimensionar panel
bind-key C-a-j resize-pane -D 2
bind-key C-a-k resize-pane -U 2
bind-key C-a-h resize-pane -L 4
bind-key C-a-l resize-pane -R 4

```

### Configurar la barra de estado.


```txt
# Color de fondo y de letra
set -g status-bg black
set -g status-fg white

# Leyendas que se deben mostrar
# A la izquierda el nombre del host
# y a la derecha la fecha
set -g status-left '#[fg=green]#H'
set -g status-right '#[fg=yellow]#(date)'

# Color de la ventana activa
set-window-option -g window-status-current-bg blue

# Color del panel activo
set-option -g pane-active-border-fg colour027

```

Longitud del historial.


```txt
set -g history-limit 10000

```

<p>Recargar configuración con <kbd>PREFIX</kbd> + <kbd>r</kbd>.</p>


```txt
unbind r
bind r source-file ~/.tmux.conf

```

Existen muchas más opciones de configuración pero creo que con esto es suficiente para comenzar.

## Algunos hacks

### Iniciar tmux automáticamente al abrir una terminal

Hemos visto que para utilizar tmux abrimos una terminal y entonces lo ejecutamos, para hacer que tmux se ejecute automáticamente cuando abrimos una terminal agrega las siguientes líneas al archivo `~/.bashrc`.


```sh
[[ $- != *i* ]] && return
[[ $TERM != screen* ]] && exec tmux -2

```

Si estamos ejecutando el interprete de comandos en modo interactivo y tenemos soporte para 256 colores entonces ejecutamos tmux.

### Copiar texto al portapapeles del sistema

Estando en el modo copy es posible copiar texto para ser usado en otros paneles o ventanas dentro de tmux, pero no en otras aplicaciones, es decir, el texto copiado en tmux no se puede pegar en firefox, por citar un ejemplo. La siguiente línea soluciona el problema. Es necesario tener instalado el programa `xclip`.


```txt
bind C-c run "tmux save-buffer - | xclip -i -selection clipboard"

```

<p>Funciona de esta manera, entra en modo copy y copia el texto en cuestión tal como ya se ha visto. Sal del modo copy y presiona <kbd>PREFIX</kbd>, suelta y después <kbd>Ctrl</kbd>+<kbd>c</kbd> para colocar el contenido en el portapapeles del sistema.</p>

Una desventaja que he notado con este truco es que una vez que lo usas vim ya no puede trabajar con el portapapeles del sistema(`"*`), aun no he encontrado una solución.

### Agregar una tecla control adicional

<p>Cuando reasigne <kbd>PREFIX</kbd> a <kbd>Ctrl</kbd> + <kbd>a</kbd> mencione que ésta combinación era más cómoda, y lo es en comparación a <kbd>Ctrl</kbd> + <kbd>b</kbd>, pero en realidad para mi es más accesible porque he reasignado la tecla de la ventana para que actúe como una tecla control adicional, esta asignación trabaja a nivel de sistema y no tiene relación directa con tmux pero a mi me resulta muy útil, en especial con vim.</p>

Para realizar la re asignación emplea el comando `xmodmap` y agrega lo siguiente en el archivo `~/.Xmodmap`.


```txt
remove Control = Control_L Control_R
remove mod4 = Super_L Super_R
add Control = Control_L Super_L

```

Algunos entornos de escritorio ejecutan este archivo al iniciar, si no es tu caso, agrega el comando `xmodmap ~/.Xmodmap` al archivo de inicio de tu entorno de escritorio, para openbox el archivo es `~/.config/openbox/autostart.sh`.

## Conclusión

Tmux al igual que las otras herramientas que vamos a tratar no son el tipo de programas que se aprenden a usar en 5 minutos, requieren cierta cantidad de tiempo, yo lo llamo una inversión porque el tiempo que dediquen para aprender a utilizarlas lo verán remunerado en poco tiempo en forma de eficiencia y productividad.

## Referencias

<table>
<tr><td>[1]</td>  <td><a href="https://tmux.github.io/"  target="_blank">https://tmux.github.io</a>                                      </td></tr>
<tr><td>[2]</td>  <td>[tmux Productive Mouse-Free Development, Brian P. Hogan](http://pragprog.com/book/bhtmux/tmux)   </td></tr>
<tr><td>[3]</td>  <td>[C IDE for Linux?](http://stackoverflow.com/questions/24109/c-ide-for-linux)                     </td></tr>
<tr><td>[4]</td>  <td>[Getting tmux to copy a buffer to the clipboard](http://unix.stackexchange.com/questions/15715/getting-tmux-to-copy-a-buffer-to-the-clipboard)  </td></tr>
</table>
