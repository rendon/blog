<!-- vim: set spelllang=es_MX: -->

# Bash
2016-02-18 2024-05-07 #sysadmin #linux #post

**NOTA**: Este artículo fue publicado originalmente en [ATIX](http://revista.atixlibre.org/?p=271), revista de software libre.

![](/bash/hdud2_0.png)

<blockquote>
El Bourne Again Shell es el poderoso interprete de comandos por defecto en la mayoría de los sistemas UNIX y una herramienta indispensable de todo desarrollador.
</blockquote>

Alguna vez la única manera de interactuar con un ordenador fue mediante comandos, hasta que se inventaron las interfaces gráficas. Hoy día abundan las GUIs y se han desarrollado programas para casi cualquier propósito, sin embargo, diferente a lo que muchos podrían pensar, la línea de comandos no ha muerto, grandiosas aplicaciones aun se desarrollan en esta modalidad, `git`, `ffmpeg`, `vim`, `wicd`, `ncmpcpp`, `mplayer`, `alsamixer`, frameworks como Ruby on Rails, Play Web y DJango, además del gran número de comandos clásicos para la administración del sistema operativo. 

Como administradores y/o desarrolladores el interprete de comandos no es opcional, es y seguirá siendo nuestro pan de cada día. Bash es un interprete de comandos y un lenguaje de programación, el Bourne Again Shell es  la versión del Bourne Shell creada por el proyecto GNU.

Este artículo no es un tutorial sobre comandos UNIX ni un manual de referencia con descripciones exhaustivas sino más bien una guía rápida específicamente a cerca de Bash. Al final proporciono algunas referencias para profundizar sobre los temas si a así lo desean.

## Inicio de sesión

El primer paso a dar es invocar el comando bash, el cual obedece la sintaxis `bash [opciones] [archivo]`, los elementos entre corchetes son opcionales. Lo más probable es que Bash sea interprete de comandos por defecto y no tendrá que ejecutarlo ya que el emulador de terminal lo ejecuta por usted, aunque no esta demás saber algunas cosas.
Opciones:

```
-i
    Crea un shell interactivo.
--norc
    No leer el archivo ~/.bashrc.
--posix
    Habilita el modo POSIX. Limita el comportamiento de bash al estándar POSIX.
--rcfile archivo
    Indica a bash que lea la configuración de inicio desde archivo y no desde ~/.bashrc
-, --
    Termina el análisis de los parámetros.
```

**Listado 1.** Opciones del comando bash.

Si se indica el nombre de un archivo como argumento bash lo interpretará como un script(se verá más adelante) e intentará ejecutarlo. 

## Configuración de entorno

Bash admite personalización y lo hace mediante archivos de configuración:

<ul>
<li>`/etc/profile`. Se ejecuta automáticamente al iniciar sesión. </li>
<li>`~/.bash_profile`, `~/.bash_login` o `~/.profile`. El primer archivo que se encuentre, en este orden. Se ejecuta automáticamente al iniciar sesión. </li>
<li>`~/.bashrc`.  Se utiliza en en situaciones distintas al inicio de sesión. </li>
</ul>

A continuación muestro algunos ejemplos de configuración.

### Personalizar el prompt

El prompt es el indicador que le precede a todo lo que tecleamos en la terminal, por ejemplo, `rendon@intel:~$` o `root@intel:~#`. El contenido del prompt se almacena en la variable de entorno `PS1`,  veamos dos ejemplos:
El más común:

```
$ export PS1='\u@\h:\w$ '
usuario@host:directorio_actual$   #resultado
```

Con colores:

```
PS1='[\e[0;32m][\t][\e[1;34m]\u[\e[0;37m][\e[1;37m]@\h~$ [\e[1;37m]'
```

![Prompt con colores](/bash/hdud2_1.png)

En la definición del prompt se han utilizados algunos valores especiales para obtener información del sistema, tales como la hora, nombre de usuario,  host, directorio actual,  entre otras.

```
\u Nombre del usuario actual.
\h Nombre del host.
\t La hora del sistema.
\d Fecha.
\w Directorio actual.
```

**Listado 2**. Valores especiales.

En [2] encontrarán bastante información sobre el prompt y los colores.

### Variables de entorno

Las variables de entorno son datos que utiliza el sistema operativo o ciertas aplicaciones para ubicar recursos, por ejemplo, la variable `PATH` contiene un listado de directorios de donde el SO tiene que buscar programas, o `JAVA_HOME` que almacena la dirección del directorio de instalación de Java, `PS1` que ya se vio en la sección anterior. El comando export permite declarar variables de entorno.

```
export JAVA_HOME="/usr/local/jdk1.7.0_09"
export PATH="${PATH}:/usr/local/mis_programas"
```

### Alias

Los alias son a grandes rasgos atajos para comandos que nos ayudan a no teclear tanto o dar nombres más significativos a ciertas acciones, ejemplos:

```
alias apt-get="sudo apt-get"
alias grep="grep --color=always"
alias ls='ls $LS_OPTIONS'
```

Al intentar ejecutar `grep` lo que realmente se ejecuta es `grep --color=always` y así con los demás comandos.

### Modos de edición

Bash tiene dos modos de edición, emacs y vi, que permiten trabajar de manera más eficiente y cómoda con el interprete. El modo por defecto es emacs. Una de las ventajas de estos modos de edición es que permiten trabajar sin retirar las manos de su posición básica.

Para habilitar estos modos de edición emplea los siguientes comandos, ya sea en modo interactivo o en el archivo de configuración para hacer el cambio permanente.

```
set -o vi
set -o emacs
```

En [3] y [4] puede encontrar una lista detallada de comandos para los modos vi y emacs respectivamente.

## Redireccionamiento

El funcionamiento básico de todo programa es recibir una entrada, procesar los datos y producir una salida. En los sistemas UNIX existen dos tipos de salida, normal y de errores. Por defecto la entrada corresponde al teclado y la salida a la pantalla.

| Descriptor de archivo   |   Nombre            |  Abreviación  | Por defecto    |
|-------------------------|---------------------|---------------|----------------|
| 0                       | Entrada estándar    |   stdin       |  Teclado       |
| 1                       | Salida estándar     |   stdout      |  Pantalla      |
| 2                       | Error estándar      |   stderr      |  Pantalla      |

**Tabla 1**. Entradas y salidas en UNIX.

La redirección de datos permite modificar el comportamiento normal de los programas con respecto a la entrada y salida de datos, a continuación un resumen con ejemplos de algunos  tipos de redirección:

### comando > archivo

Redirecciona la salida de comando a archivo(el archivo se sobrescribe). Por ejemplo:

```
$ ls -1 > salida.txt
```

### comando < archivo

El comando toma la entrada desde archivo.
Ej.

```
$ bc < entrada.txt
```

### comando >> archivo

Redirecciona la salida de comando a archivo(el archivo no se sobrescribe, se agrega al final).
Ej.

```
$ ls imagenes/ > archivos.txt
$ ls videos/ >> archivos.txt
```

*archivos.txt* contiene el listado de archivos en imágenes y también los del directorio videos.

### comando << marca

Conocido como *here document*, todo texto que se tecleé después de marca hasta encontrar nuevamente a marca se tomará como la entrada del programa, marca no forma parte de la entrada.
Ej.


```
$cat > salida.txt <<EOF
> linea 1
> linea 2
>EOF
```

El texto entre `EOF` y `EOF` se almacena en el archivo `salida.txt`.

### comando <<< cadena

Conocido como *here string*, "cadena" es tomada como entrada de "comando", muy útil.
Ej. 

```
$ bc <<< "(2^10 + 6)/2"
```

### comando > archivo

Redirecciona la salida que normalmente iría al descriptor de archivo *n* a archivo. Por ejemplo:

```
$ gcc > error.txt
  gcc: fatal error: no input files
  compilation terminated.
$ cat error.txt
$
$ gcc 2> error.txt
$ cat error.txt
  gcc: fatal error: no input files
  compilation terminated.
```

El primer ejemplo de redirección no funciona y el archivo `error.txt` esta vació porque los mensajes de error de `gcc` van dirigidos al descriptor de errores(2) y no al descriptor de salida(1). El segundo ejemplo logra su objetivo.

### comando <& n

Toma la entrada para comando desde el descriptor de archivo n.
Ej.

```
$ echo "(3 * 4)/2" > entrada.txt
$ exec 5<entrada.txt 
$ bc &lt;&5
6
```

### comando &amp;&gt; archivo

Envía la salida estándar y errores a archivo.

### comando &gt; salida.txt 2&gt; errores.txt

Envía la salida a `salida.txt` y los errores a `errores.txt`.

### comando | tee salida.txt

Envía la salida de *comando* a `tee` para que lo muestre en pantalla y a la ves lo almacene en el archivo `salida.txt`.

Tenga cuidado con los espacios, no todas las redirecciones permiten espacios antes o después de `&lt;` y `&gt;`.

## Tuberías y substitución de procesos

### comando1 | comando2

_comando2_ toma como entrada la salida generada por _comando1_.
Ej.

```
$ ls -1 | grep ".*txt"
$ echo "1 9 7 1 2 9 2 1" | tr ' ' '\n' |  sort -n | uniq
```

### comando &lt;(comandos)

_comando_ toma como entrada la salida de _comandos_.
Ej. 

```
$ uniq <(echo "1 9 7 1 2 9 2 1" | tr ' ' '\n' |  sort -n)
```

## Bash como lenguaje de programación

En este apartado vamos a ver algunas de las características de Bash que le permiten funcionar como un lenguaje de programación. Cabe de decir que Bash no es un lenguaje de propósito general sino más bien orientado a la administración de sistemas y automatización de tareas.

### Variables

Una variable es un identificador que almacena cierto valor, veamos como definir una.

```
$ nombre="Rafael"
$ declare -i edad=20+3 #variables de tipo entero
$ idiomas=(español ingles latín hebreo chino) 
```

Las reglas para nombrar variables son las mismas que en la mayoría de los lenguajes: letras, guion bajo, números, el nombre no debe iniciar con número.
Para recuperar el valor de una variable anteponga un $ al nombre de la variable.

```
$ echo "Mi nombre es $nombre,  tengo $edad años y hablo ${idiomas[@]}."
Mi nombre es Rafael,  tengo 23 años y hablo español ingles latín hebreo chino.
```

#### Variables predefinidas

Bash define algunas variables por defecto, muy útiles cuando trabajamos con scripts.

```
$#    Número de argumentos pasados a un comando.
$?    Valor de salida del último comando.
$0    Nombre del comando que se esta ejecutando.
$n    Valores de los argumentos. $1 es el primer
      parámetro, $2 el segundo parámetro, etc.
"$*"  Todos los argumentos como una cadena 
      ("$1 $2 ...").
"$@"  Todos los argumentos entre comillas dobles
      de forma individual.
```

### Arreglos

Bash provee dos tipos de arreglos, basados en índices(los índices son números) y asociativos(los índices son cadenas).

```
$ idiomas=(español ingles latín hebreo chino)
$ echo ${idiomas[0]}
español
$ echo ${idiomas[1]}
ingles
$ declare -A P=( [mexico]=52 [bolivia]=591 [canada]=11 )
$ echo ${P[mexico]}
52
```

#### Operaciones sobre arreglos:

```
${arreglo[i]} Valor en el índice i
${arreglo[*]} Todos los elementos
${arreglo[@]} Todos los elementos
${#name[*]}   Número de elementos en el arreglo
${#name[@]}   Número de elementos en el   arreglo
```

### Expresiones aritméticas

Las operaciones aritméticas se puede realizar con `$((` *expresión* `))`.

```
$ echo $(( (2**10)/2 ))
512
$ a=3; b=10;
$ echo $(( a += b ))
$ echo $a
13
```

Los operadores en su mayoría son los mismos que en C/C++, salvo algunas excepciones, la exponenciación(**), por ejemplo.

### Estructuras de control

Las estructuras de control permiten guiar el flujo de ejecución de un programa. Bash provee `if`, `if ... else` y `if ... elif ... else`.

#### If

```
if COMANDOS-DE-PRUEBA
then
  BLOQUE-DE-COMANDOS
fi
```

Ej.

```
if [ $edad -lt 18 ]
then
  echo "Fuera de aquí. Solo para adultos.";
fi
```

#### If … else

```
if COMANDOS-DE-PRUEBA
then
  BLOQUE-DE-COMANDOS-1
else
  BLOQUE-DE-COMANDOS-2
fi
```

Ej. 

```
if [ $edad -ge 18 ]
then
  echo "Adelante.";
else
  echo "Fuera de aquí. Solo para adultos.";
fi
```

#### If … elif … else

```
if COMANDOS-DE-PRUEBA
then
  BLOQUE-DE-COMANDOS-1
elif COMANDOS-DE-PRUEBA
  BLOQUE-DE-COMANDOS-2
fi
```

Ej.

```
if [ $edad -ge 18 ]
then
  echo "Adelante.";
elif [ $influyente ]
  echo "Adelante por favor";
else
  echo "Fuera de aquí. Solo para adultos.";
fi
```

Para las comparaciones he utilizado algunos operadores diferentes a los convencionales, como son

```
-lt   Menor que.
-ge   Mayor o igual a.
```

Véase `man [` para más información sobre los operadores de comparación.

### Estructuras de repetición

Bash soporta las estructuras while y for para repetición de operaciones. Su sintaxis es la siguiente.

#### For

```
for argumento in [lista]
do
  comando(s)...
done
```

Ej. 

```
for i in {1..10}
do
  echo $(( i**2 ));
done
```

#### While

```
while [ condición ]
do
  comando(s)...
done
```

Ej. 

```
while read archivo
do
  rm "$archivo";
done < <(ls -1)
```

## Scripts

Un script no es más que una serie de comandos y operaciones guardados en un archivo, listos para ser ejecutados por Bash. La estructura de un script es la siguiente.

```
#!/bin/bash

VARIABLES_DE_CONFIGURACION

DEFINICION_DE_FUNCIONES

CODIGO_PRINCIPAL

EXIT_CODE
```

La primer línea especifica con que comando deben ser ejecutados los comandos en el archivo. El contenido de la primera línea es conocido como *shebang*.
Para finalizar les dejo un pequeño script donde se emplean algunos elementos ya vistos, es un script muy sencillo que empleo para configurar un directorio con plantillas de código en diferentes lenguajes para usarse durante un concurso de programación.

```
#!/bin/bash
PC="/home/data/cs/pc";

if [ $1 = "-f" ]
then
  if [ -z $2 ]
  then
    echo "Provide a file name!";
    exit;
  fi

  # file name
  fn=$(sed 's/\([^.]\+\).*$/\1/g' <<< $2);
  # file type
  ft=$(sed 's/[^.]\+.\(.\+\)$/\1/g' <<< $2);

  if [ $ft != "cpp" -a $ft != "java" -a $ft != "py" -a $ft != "rb" ]
  then
    echo "File type($ft) not supported :(!";
    exit;
  fi

  if [ $ft = "java" ]
  then
    sed "s/Main/$fn/g" < "$PC/TEMPLATE/Main.java" > "$fn.$ft";
  else
    cp "$PC/TEMPLATE/template.$ft" "$fn.$ft";
  fi

else
  if    [ $1 = "codeforces" ]; then list=({A..E});
  elif  [ $1 = "cookoff"    ]; then list=({A..E});
  elif  [ $1 = "challenge"  ]; then list=({A..J});
  elif  [ $1 = "hackercup"  ]; then list=({A..C});
  fi;

  for problem in ${list[@]}
  do
    mkdir $problem;
    cd $problem;
    cp "$PC/TEMPLATE/template.cpp" "$problem.cpp";
    cp "$PC/TEMPLATE/template.rb"  "$problem.rb";
    cp "$PC/TEMPLATE/template.py"  "$problem.py";
    sed "s/Main/$problem/g" < "$PC/TEMPLATE/Main.java" > "$problem.java";
    cd ..;
  done

fi

exit 0;
```

**Script 1**: setcontest.sh

Existen básicamente dos formas de ejecutar un script. Invocar bash pasando como argumento el archivo o dando permisos de ejecución al script y se ejecuta como cualquier otro comando.

```
$ bash mi_script.sh      # primera forma

$ chmod +x mi_script.sh  # segunda forma
$ ./mi_script.sh
```

## Conclusión

Bash es una herramienta poderosa y extensa, hablar a profundidad del tema involucraría cientos de páginas y ciertamente el autor de este artículo no cuenta con el conocimiento suficiente. En este documento solo hemos visto algunas de las características básicas pero que considero suficiente para iniciarse. Además recalcar que lo antes visto es unicamente referente a Bash, en futuras publicaciones escribiré sobre ciertos programas que agregan funcionalidad a la linea de comandos.

## Referencias

<table>
  <tr><td>[1]</td> <td>Bash Pocket reference, Arnold Robbins, O'Reily.</td></tr>
  <tr><td>[2]</td> <td>[Color Bash Prompt](https://wiki.archlinux.org/index.php/Color_Bash_Prompt), Archilinux.org</td></tr>
  <tr><td>[3]</td> <td>[Working Productively in Bash's Vi Command Line Editing Mode](http://www.catonmat.net/blog/bash-vi-editing-mode-cheat-sheet/), catonmat.net</td></tr>
  <tr><td>[4]</td> <td>[Bash Emacs Editing Mode Cheat Sheet](http://www.catonmat.net/blog/bash-emacs-editing-mode-cheat-sheet/), catonmat.net</td></tr>
</table>
