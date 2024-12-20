<!-- vim: set spelllang=es_MX: -->

---
tags:
    - dev
    - sysadmin
    - linux
    - post
created: 2016-02-18
updated: 2024-05-07
---
# Procesos

Como parte de mi proyecto final estoy estudiando sobre sistemas operativos con un enfoque especial en GNU/Linux, en lo posible voy a ir publicando algunas cosas que me parezcan interesantes y que ojala lo sean para otros más también.

## Proceso

Uno de los primeros temas que se abordan en los libros de sistemas operativos son los *procesos*, que en términos simples son programas en *ejecución*. Un programa por si mismo no es un proceso. Podríamos decir que un programa por si solo es una entidad **pasiva** mientras que un proceso es una entidad **activa**, un programa que se esta ejecutando en el sistema y tiene asociado a él más que código ejecutable.

Dentro de los datos que se asocian a un proceso podemos encontrar un identificador de proceso (PID), información sobre el creador del proceso actual (el padre), una lista de los procesos creados por el proceso actual (los hijos), recursos como archivos abiertos, un espacio de memoria para uso particular, entre otros. El sistema operativo necesita toda esta información para poder administrar los procesos de manera correcta.

## Procesos en Linux

En Linux (el kernel) toda la información relacionada a un proceso se almacena en la estructura `task_struct` la cual esta definida en el encabezado <code><linux/sched.h></code> y dentro de sus campos podemos encontrar los siguientes:


```c
struct task_struct {
    volatile long state;	/* -1 unrunnable, 0 runnable, >0 stopped */
    void *stack;
    atomic_t usage;
    unsigned int flags;	/* per process flags, defined below */
    unsigned int ptrace;

    ...

    pid_t pid;
    pid_t tgid;

    ...
    char comm[TASK_COMM_LEN]; /* executable name excluding path
                     - access with [gs]et_task_comm (which lock
                       it with task_lock())
                     - initialized normally by setup_new_exec */

    ...

    /*
     * children/sibling forms the list of my natural children
     */
    struct list_head children;	/* list of my children */
    struct list_head sibling;	/* linkage in my parent's children list */
    ...
}

```

Como podrán apreciar en la última línea, un proceso también mantiene una lista de sus procesos hermanos, aquellos que comparten el mismo padre.

El kernel mantiene la lista de procesos en una lista doublemente enlazada donde cada elemento contiene una estructura `task_struct`. La figura  muestra como luce dicha lista.

![Lista doblemente enlazada de procesos](/procesos/doubly_linked_list.png)

Puesto que un proceso es un programa en ejecución y normalmente la cantidad de procesos es mayor que la cantidad de procesadores (en muchas ocasiones solo uno), éstos tienen que compartir el tiempo de la CPU y es el sistema operativo quien se encarga de coordinar esta actividad. Debido a lo anterior un proceso tiene asociado un *estado*, que como su nombre lo indica, nos permite determinar que esta haciendo el proceso dentro del sistema operativo, básicamente esta en ejecución o esperando, a continuación una lista de todos los estados posibles en en SO Linux.

<ul>
	<li>TASK_RUNNING: El proceso esta en ejecución.</li>
	<li>TASK_INTERRUPTIBLE: El proceso esta durmiendo (bloqueado), esperando que se cumpla alguna condición, por ejemplo, cuando se espera a que el usuario realice una acción.</li>
	<li>TASK_UNINTERRUPTIBLE: Similar al TASK_INTERRUPTIBLE con la diferencia que en este estado el proceso no responde a las señales, por ejemplo, cuando queremos que un procesos espere cierta cantidad de tiempo.</li>
	<li>__TASK_TRACED: El proceso esta siendo rastreado por otro proceso, por ejemplo, por un depurador.</li>
	<li>__TASK_STOPPED: El proceso a termina su ejecución</li>
</ul>

La figura  ilustra las relaciones entre los distintos estados.

![Diagrama de flujo de los estados de un proceso](/procesos/process_states.svg)

En Linux el primer proceso que se ejecuta es `init` con PID igual a 1 y es éste el que se encarga de crear al resto de los procesos  necesarios para el funcionamiento del sistema. A su vez, cada nuevo proceso es capaz de crear otros más. No es difícil darse cuenta que este mecanismo forma un árbol de procesos, donde la raíz es el proceso `init`, los nodos intermedios son aquello diferentes de `init` y que tienen al menos un proceso hijo, mientras que las hojas son aquellos que no crean nuevos procesos.

## Consultar información de procesos

A continuación veremos como obtener información a cerca de los procesos desde el punto de vista del administrador del sistema como desde el punto de vista del desarrollador.

### Utilizando el comando ps

El comando `ps` obtiene y reporta información de los procesos en el sistema en un determinado instante (snapshot). `ps` soporta varias opciones que nos permiten filtrar justo la información que necesitamos, veamos algunos ejemplos.

Listar todos los procesos en el sistema: `ps -e`


```txt
  PID TTY          TIME CMD
    1 ?        00:00:01 init
    2 ?        00:00:00 kthreadd
    3 ?        00:00:02 ksoftirqd/0
    6 ?        00:00:00 migration/0
    7 ?        00:00:00 watchdog/0
    8 ?        00:00:00 migration/1
   10 ?        00:00:02 ksoftirqd/1
   12 ?        00:00:00 watchdog/1
    .
    .
    .
28260 ?        00:00:00 apache2
28383 ?        00:00:00 gvfsd-metadata
28414 ?        00:02:31 inkscape
29918 pts/3    00:00:00 bash
30032 ?        00:00:00 kworker/0:1
30759 ?        00:00:00 kworker/1:2

```

Mostrar los procesos en forma de arbol: `ps -ejH`

```txt
  PID  PGID   SID TTY          TIME CMD
    2     0     0 ?        00:00:00 kthreadd
    3     0     0 ?        00:00:02   ksoftirqd/0
    6     0     0 ?        00:00:00   migration/0
    7     0     0 ?        00:00:00   watchdog/0
    8     0     0 ?        00:00:00   migration/1
    .
    .
    .
    1     1     1 ?        00:00:01 init
  329   329   329 ?        00:00:00   udevd
  439   329   329 ?        00:00:00     udevd
 2507   329   329 ?        00:00:00     udevd
 1822  1822  1822 ?        00:00:00   rpcbind
 2144  2081  2070 ?        00:00:00   rsyslogd
 2173  2173  2173 ?        00:00:00   vmware-usbarbit
 2202  2202  2202 ?        00:00:00   acpid
 2232  2232  2232 ?        00:00:00   dbus-daemon
 2310  2310  2310 ?        00:00:00   atd
 2335  2334  2334 ?        00:00:00   gdm3
 2470  2334  2334 ?        00:00:00     gdm-simple-slav
 2509  2509  2509 tty7     00:35:46       Xorg
 3180  2334  2334 ?        00:00:00       gdm-session-wor
 3464  3464  3464 ?        00:00:09         openbox
 3517  3517  3517 ?        00:00:00           ssh-agent
 2391  2390  2390 ?        00:00:00   avahi-daemon
 2392  2390  2390 ?        00:00:00     avahi-daemon
    .
    .
    .

```

Mostrar los procesos creados por el usuario *root*:


```txt
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
root         1  0.0  0.0   2280   732 ?        Ss   08:43   0:01 init [2]  
root         2  0.0  0.0      0     0 ?        S    08:43   0:00 [kthreadd]
root         3  0.0  0.0      0     0 ?        S    08:43   0:02 [ksoftirqd/0]
root         6  0.0  0.0      0     0 ?        S    08:43   0:00 [migration/0]
root         7  0.0  0.0      0     0 ?        S    08:43   0:00 [watchdog/0]
root         8  0.0  0.0      0     0 ?        S    08:43   0:00 [migration/1]
root        10  0.0  0.0      0     0 ?        S    08:43   0:02 [ksoftirqd/1]
root        12  0.0  0.0      0     0 ?        S    08:43   0:00 [watchdog/1]
  .
  .
  .
root      3230  0.0  0.0   3780   864 tty4     Ss+  08:44   0:00 /sbin/getty 38400 tty4
root      3231  0.0  0.0   3780   856 tty5     Ss+  08:44   0:00 /sbin/getty 38400 tty5
root      3232  0.0  0.0   3780   856 tty6     Ss+  08:44   0:00 /sbin/getty 38400 tty6
root      3448  0.0  0.0      0     0 ?        S    08:51   0:00 [kauditd]
root      3611  0.0  0.0  24052  3584 ?        Sl   08:52   0:01 /usr/lib/udisks/udisks-daemon
root      3614  0.0  0.0   6352   728 ?        S    08:52   0:00 udisks-daemon: not polling any devices
root     23607  0.0  0.0      0     0 ?        S    13:54   0:06 [kworker/1:1]
root     24530  0.0  0.0      0     0 ?        S    14:08   0:04 [kworker/0:0]
root     27516  0.0  0.0   4664  1628 ?        S    14:52   0:00 /bin/sh /usr/bin/mysqld_safe
root     27845  0.0  0.0   3352   620 ?        S    14:52   0:00 logger -t mysqld -p daemon.error
root     28055  0.0  0.1  36792  7596 ?        Ss   14:52   0:00 /usr/sbin/apache2 -k start
root     30032  0.0  0.0      0     0 ?        S    15:19   0:00 [kworker/0:1]
root     30759  0.0  0.0      0     0 ?        S    15:30   0:00 [kworker/1:2]

```

Es posible especificar que campos debe contener el reporte, por ejemplo: `ps -eo pid,class,rtprio,pri,psr,pcpu,stat,comm`


```txt
  PID CLS RTPRIO PRI PSR %CPU STAT COMMAND
    1 TS       -  19   1  0.0 Ss   init
    2 TS       -  19   0  0.0 S    kthreadd
    3 TS       -  19   0  0.0 S    ksoftirqd/0
    6 FF      99 139   0  0.0 S    migration/0
    7 FF      99 139   0  0.0 S    watchdog/0
    8 FF      99 139   1  0.0 S    migration/1
   10 TS       -  19   1  0.0 S    ksoftirqd/1
   12 FF      99 139   1  0.0 S    watchdog/1
   13 TS       -  39   0  0.0 S<   cpuset
   14 TS       -  39   1  0.0 S<   khelper
   15 TS       -  19   1  0.0 S    kdevtmpfs
   16 TS       -  39   1  0.0 S<   netns
   17 TS       -  19   0  0.0 S    sync_supers
    .
    .
    .
28064 TS       -  19   1  0.0 S    apache2
28121 TS       -  19   0  0.0 Ss   bash
28197 TS       -  19   1  0.1 Sl+  vi
28207 TS       -  19   0  0.0 S    apache2
28210 TS       -  19   1  0.0 S    apache2
28257 TS       -  19   1  0.0 S    apache2
28259 TS       -  19   0  0.0 S    apache2
28260 TS       -  19   0  0.0 S    apache2
28383 TS       -  19   0  0.0 S    gvfsd-metadata
28414 TS       -  19   1  1.4 S    inkscape
29918 TS       -  19   1  0.0 Ss   bash

```

El significado de las opciones es el siguiente:

<ul>
  <li>*pid*: El identificador de proceso.</li>
  <li>*class*: Clase de planificación del proceso, e.g:</li>
  <ul>
    <li>`-` no ha sido reportado
    <li>`FF` proviene de SCHED_FIFO, una cola de espera normal, el primero en llegar es el primero en salir.
    <li>`RR`  proviene de SCHED_RR, utiliza un algoritmo [Round robin](https://en.wikipedia.org/wiki/Round-robin).
    <li>`IDL` proviene  SCHED_IDLE, para procesos con prioridad muy baja.
    <li>`?` el valor no se conoce.
  </ul>
  <li>*rtprio*: Prioridad en tiempo real.</li>
  <li>*pri*: Prioridad del proceso, valores más pequeños significan prioridad más alta.</li>
  <li>*psr*: A que procesador se encuentra asignado el proceso.</li>
  <li>*pcpu*: Porcentaje de uso de la CPU.</li>
  <li>*stat*: Estado del proceso:</li>
  <ul>
    <li>`D`   Esperando. No interrumpible.</li>
    <li>`R`   En ejecución o en la cola de ejecución.</li>
    <li>`S`   Esperando. Interrumpible.</li>
    <li>`T`   Parado.</li>
    <li>`X`   Muerto (nunca debería de ser visto).</li>
    <li>`Z`   Difunto (zombie), el proceso ha terminado pero no ha sido reclamado por quien lo creo, su padre.</li>
  </ul>
  <li> *comm*: Nombre del comando.</li>
</ul>


Para más información véase la documentación (`man ps`). Otro comando que puede ser útil es `top`, cuya funcionalidad es similar a `ps` en cuanto a la información que despliega, la diferencia es que `top` se mantiene actualizando la información constantemente.

### Desde C

Para obtener información sobre el proceso actual utilizaremos la macro `current`, cuya implementación varia entre plataformas. El siguiente listado muestra como moverse desde el proceso actual hasta la raíz:


```c
struct task_struct *parent = current;
while (parent->pid != 1)
    parent = parent->parent;

```

Para un determinado proceso podemos obtener la lista de sus procesos hijo de la siguiente manera:


```c
struct list_head *list;
struct task_struct *task;

list_for_each(list, &s->children)
    task = list_entry(list, struct task_struct, sibling);

```


#### Visualizar el árbol de procesos

Con las premisas que hemos visto podemos extraer algo de información significativa de nuestro sistema operativo, lo primero que se me ocurrió es simular lo que hace el comando `pstree`. El siguiente código realiza un recorrido primero en profundidad ([DFS](https://en.wikipedia.org/wiki/Depth-first_search)) para obtener el árbol de procesos de nuestro sistema:


```c
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/string.h>

void pstree(struct task_struct *s, int sum)
{
    struct list_head *list;
    struct task_struct *task;

    int i;
    for (i = 0; i < sum; i++)
        printk(" ");
    printk("|-->%s\n", s->comm);
    sum = sum + strlen(s->comm);
    list_for_each(list, &s->children) {
        task = list_entry(list, struct task_struct, sibling);
        pstree(task, sum);
    }
}


int simple_init(void)
{
    struct task_struct *parent = current;
    while (parent->pid != 1)
        parent = parent->parent;
    
    pstree(parent, 0);

    return 0;
}

void simple_exit(void)
{
    printk("Bye!\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPLv3");
MODULE_DESCRIPTION("Playing with processes.");
MODULE_AUTHOR("Rafael Rendón Pablo");

```

Este código corresponde a un módulo cargable del nucleo ([LKM](http://en.wikipedia.org/wiki/Loadable_kernel_module)) y se compila con el siguiente archivo Makefile:


```
obj-m += pstree.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

```

No se si esta sea la mejor manera de experimentar con el kernel pero funciona, y por ahora eso es más importante. Veamos como funciona.

Insertar el módulo:


```sh
sudo insmod pstree.ko

```

Visualizar los resultados:


```sh
sudo dmesg

```

Aquí el resultado en mi máquina:


```txt
[10134.361134] |-->init
[10134.361138]     |-->udevd
[10134.361142]          |-->udevd
[10134.361150]          |-->udevd
[10134.361157]     |-->rpcbind
[10134.361162]     |-->rsyslogd
[10134.361167]     |-->acpid
[10134.361172]     |-->vmware-usbarbit
[10134.361177]     |-->dbus-daemon
[10134.361182]     |-->atd
[10134.361187]     |-->gdm3
[10134.361192]         |-->gdm-simple-slav
[10134.361199]                        |-->Xorg
[10134.361214]                        |-->gdm-session-wor
[10134.361229]                                       |-->openbox
[10134.361252]                                              |-->ssh-agent
[10134.361278]                                              |-->firefox
[10134.361308]     |-->avahi-daemon
[10134.361313]                 |-->avahi-daemon
[10134.361325]     |-->cron
[10134.361329]     |-->ntpd
[10134.361334]     |-->colord
[10134.361339]     |-->exim4
[10134.361344]     |-->colord-sane
[10134.361349]     |-->cupsd
[10134.361353]     |-->sshd
[10134.361358]     |-->minissdpd
[10134.361363]     |-->getty
[10134.361367]     |-->getty
[10134.361372]     |-->getty
[10134.361377]     |-->getty
[10134.361381]     |-->getty
[10134.361386]     |-->getty
[10134.361391]     |-->polkitd
[10134.361395]     |-->accounts-daemon
[10134.361400]     |-->console-kit-dae
[10134.361405]     |-->upowerd
[10134.361410]     |-->rtkit-daemon
[10134.361415]     |-->dbus-daemon
[10134.361420]     |-->dbus-launch
[10134.361425]     |-->fbpanel
[10134.361430]     |-->sh
[10134.361434]       |-->conky
[10134.361440]     |-->compton
[10134.361445]     |-->nm-applet
[10134.361450]     |-->hp-systray
[10134.361454]               |-->hp-systray
[10134.361465]                         |-->hp-systray
[10134.361480]     |-->notification-da
[10134.361485]     |-->gvfsd
[10134.361490]     |-->pulseaudio
[10134.361495]     |-->gconfd-2
[10134.361500]     |-->kded4
[10134.361504]     |-->kdeinit4
[10134.361509]             |-->klauncher
[10134.361518]             |-->okular
[10134.361527]             |-->okular
[10134.361536]     |-->kglobalaccel
[10134.361541]     |-->yakuake
[10134.361546]            |-->tmux
[10134.361555]     |-->tmux
[10134.361559]         |-->bash
[10134.361566]             |-->vim
[10134.361575]         |-->bash
[10134.361582]             |-->sudo
[10134.361591]                 |-->su
[10134.361601]                   |-->bash
[10134.361613]                       |-->insmod
[10134.361628]         |-->bash
[10134.361635]             |-->vi
[10134.361644]     |-->udisks-daemon
[10134.361649]                  |-->udisks-daemon
[10134.361661]     |-->knotify4
[10134.361666]     |-->mpd
[10134.361670]     |-->dolphin
[10134.361675]     |-->at-spi-bus-laun
[10134.361680]     |-->apache2
[10134.361685]            |-->apache2
[10134.361693]            |-->apache2
[10134.361702]            |-->apache2
[10134.361710]            |-->apache2
[10134.361718]            |-->apache2
[10134.361727]            |-->apache2
[10134.361735]            |-->apache2
[10134.361744]            |-->apache2
[10134.361752]            |-->apache2
[10134.361761]            |-->apache2
[10134.361769]     |-->mysqld_safe
[10134.361774]                |-->mysqld
[10134.361785]                |-->logger
[10134.361795]     |-->kuiserver
[10134.361800]     |-->xclip

```

Para descargar el módulo del kernel ejecuta el siguiente comando:


```sh
sudo rmmod pstree

```

#### Visualizar el árbol de procesos de forma gráfica
Una vez que logre extraer el árbol se me ocurrió generarlo en un formato adecuado para que pudiese visualizarlo de forma gráfica apoyándome de una herramienta que desarrolle para visualizar grafos ([Graph Illustrator](https://github.com/rendon/graph_illustrator/)). He aquí la nueva versión:


```c
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/string.h>

void pstree_coord(struct task_struct *s, int x, int y)
{
    struct list_head *list;
    struct task_struct *task;
    int i = 0, size = 0, offset = 15;
    printk("%s\\n[%d]:%d,%d,C\n", s->comm, s->pid, x, y);
    list_for_each(list, &s->children)
        size += offset;

    i = -size / 2;
    list_for_each(list, &s->children) {
        task = list_entry(list, struct task_struct, sibling);
        pstree_coord(task, x + i, y - 15);
        i += offset;
    }
}

void pstree(struct task_struct *s)
{
    struct list_head *list;
    struct task_struct *task;
    printk("%s\\n[%d],%s\\n[%d]\n",
           s->parent->comm, s->parent->pid, s->comm, s->pid);

    list_for_each(list, &s->children) {
        task = list_entry(list, struct task_struct, sibling);
        pstree(task);
    }
}


int simple_init(void)
{
    struct task_struct *parent = current;
    while (parent->pid != 1)
        parent = parent->parent;
    
    printk("[EDGES]\n");
    pstree(parent);
    printk("[VERTICES]\n");
    pstree_coord(parent, 0, 0);

    return 0;
}

void simple_exit(void)
{
    printk("======================= END =========================\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPLv3");
MODULE_DESCRIPTION("Playing with processes.");
MODULE_AUTHOR("Rafael Rendón Pablo");


```

Manualmente hay que editar un poco la salida para que que sirva como entrada para el visualizador. He aquí el archivo resultante: [pstree.gi](/procesos/pstree.gi).

La figura  muestra el resultado.

![Árbol de procesos](/procesos/pstree.svg)

## Creación de procesos

En sistemas UNIX la creación de nuevos procesos se realiza en dos pasos. Primero se bifurca el proceso actual utilizando la función `fork()`, la cual crea una copia del proceso actual, la única diferencia entre estos dos procesos es el PID, el cual es único. El segundo paso consiste en reemplazar el espacio de memoria del nuevo proceso con el código ejecutable del programa que se quiere ejecutar e inmediatamente iniciar la ejecución, esto se logra con la función `exec()`.


```c
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "La bifurcación fallo :(");
        return 1;
    } else if (pid == 0) {
        execlp("/bin/ls", "ls", NULL);
    } else {
        wait(NULL);
        printf("El proceso hijo ya termino.");
    }

    return 0;
}

```


Notarán que he utilizado `execlp()` en vez de `exec()`, esto es porque en realidad `exec()` es un familia de funciones, la cuales son *front ends* para la función `execve()`.

El código funciona de la siguiente manera:

<ul>
  <li>Cuando se realiza la bifurcación se crea una copia del proceso actual y ambos procesos continúan su ejecución en la siguiente instrucción.</li>
  <li>Debido a que el hijo es una copia del padre debe existir un mecanismos para diferenciarlos y este es que el valor de `pid` en el hijo es igual al cero (el cero no es un PID válido puesto que a `init` le corresponde el 1 y todos los demás PIDs deben ser mayores a él) y en el proceso padre el valor de `pid` es igual al verdadero PID del nuevo proceso.</li>
  <li>Una vez que sabemos como diferenciar a los dos procesos podemos reemplazar al proceso hijo con el programa que pretendemos ejecutar.</li>
  <li>El proceso padre puede continuar con su ejecución o bien esperar que que el hijo termine, lo cual dependerá de la tarea que se este realizando, para esperar a que el hijo termine utilizamos la función `wait()`.</li>
</ul>

Por último veamos un ejemplo un poco más elaborado, un mini emulador de terminal:


```c
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
    char line[100];
    char command[20];
    char args[60];
    int exit = 0, ch, cmd_len, args_len, bg, i, len;
    pid_t pid;
    while (1) {
        printf("osh> ");
        len = 0;
        while ((ch = getchar()) != '\n')
            line[len++] = ch;
        line[len] = '\0';

        cmd_len = 0;
        i = 0;
        while (i < len && line[i] != ' ')
            command[cmd_len++] = line[i++];
        command[cmd_len] = '\0';

        args_len = 0;
        while (i < len && line[i] == ' ') i++;
        while (i < len)
            args[args_len++] = line[i++];
        args[args_len] = '\0';

        if (strcmp(command, "exit") == 0)
            break;

        if (cmd_len > 0) {
            bg = 0;
            for (i = args_len - 1; i >= 0; i--) {
                if (args[i] == '&') {
                    bg = 1;
                    args[i] = ' ';
                    break;
                }
            }

            pid = fork();
            if (pid == 0) {
                if (args_len > 0) 
                    execlp(command, command, args, NULL);
                else
                    execlp(command, command, NULL);

            } else {
                if (bg == 0)
                    wait(NULL);
            }
        }
    }
    return 0;
}

```

En este ejemplo básicamente leemos la línea de texto que el usuario introduce y se paramos el nombre del comando de los parámetros y además verificamos si el comando debe ejecutarse en *background* (el comando finaliza con un ampersand), después de esto creamos un nuevo proceso y utilizamos la función `execlp()` para ejecutar al comando en cuestión, el cual debe existir en el sistema.

Este programa esta bien limitado y tiene varías fallas, el único propósito es dar una mejor idea de como se crean procesos y no de crear una copia de Bash :).

## Referencias
1. Robert Love, Linux Kernel Development, 3rd Ed.
2. Silberschatz et al., Operating System Concepts, 9th Ed.
