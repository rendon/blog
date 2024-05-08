<!-- vim: set spelllang=es_MX: -->
# Instalar servidor de DNS en Linux
2016-02-18 2024-05-07 #sysadmin #linux #post

## Introducción 

Las siglas DNS son la iniciales de _Domain Name System_, Sistema de Nombres de Dominio, es una base de datos distribuida y jerarquica, que almacena asignaciones de nombres de dominio a varios tipos de datos, como son direcciones IP. Un sistema de DNS permite emplear nombres faciles de recordar, tal como www.misitioweb.com, para localizar computadoras y otros recursos en una red TCP/IP.

## Configuración del cliente de DNS

La distribución que vamos a utilizar para esta práctica es Debian GNU/Linux, una de las distribuciones más estables y robustas.

Cuando nos conectamos a la Internet es indispensable que nuestro sistema conozca la dirección o direcciones de los servidores DNS para solicitar la traducción de nombres a IPs. En general, existen dos formas de establecer estas configuraciones, con la ayuda de una aplicación gráfica, o desde la línea de comandos. Veamos las dos formas.

En la figura  se muestra la forma de configurar una computadora para que utilice un servidor DNS en específico, en el ejemplo se utiliza una IP estática ya que de esta manera tenemos control total sobre las configuraciones, cuando utilizamos un cliente DHCP generalmente tambien se configura el servidor DNS automáticamente .

![Configuración de IP estática y servidor DNS con wicd](/dns-server-gnu-linux/dns_wicd_conf.png)

La figura  muestra como realizar la misma conexión utilizando el programa Network Manager, el asistente que podemos encontrar en sistemas con entorno de escritorio GNOME.

![Configuración de IP estática y servidor DNS con Network Manager](/dns-server-gnu-linux/dns_network_manager_conf.png)

El método para especificar el servidor(es) DNS desde la lína de comandos, es utilizando el archivo _/etc/resolv.conf_ para especificar a donde se deben solicitar los nombres. A continuación un ejemplo de como podría lucir este archivo.


```conf
# /etc/resolv.conf
search 192.168.1.65
nameserver 192.168.1.65

```

En este caso el servidor DNS se encuentra en la máquina con IP 192.168.1.65. Establecer la IP de nuestro equipo es el siguiente paso:


```sh
# ifconfig eth0 192.168.1.100 netmask 255.255.255.0

```

Y por último establecer la dirección IP del _Gateway_.


```sh
# route add default gw 192.168.1.254

```

## Instalación y configuración del servidor DNS

Ahora vamos a configurar nuestro sistema para que actue como servidor de DNS, ya no como cliente. El programa que vamos a utilizar para ello es Dnsmasq. El primer paso es instalarlo.


```sh
# apt-get install dnsmasq

```

La forma de configurar a Dnsmasq es utilizando el archivo _/etc/dnsmasq.conf_, la configuración más sencilla sería indicar las direcciones de los servidores de DNS externos, es decir, a los que hará la petición de nombres de dominio en caso que de Dnsmasq no tenga un nombre en su base de datos. 


```conf
server=8.8.8.8
server=8.8.4.4

```

El archivo _/etc/resolv.conf_ debe contener la siguiente información:


```conf
nameserver 127.0.0.1

```

Es decir, las peticiones de traducción de nombres se harán a si mismo, donde esta corriendo Dnsmasq.

## Caso práctico: Restringir sitios vía DNS

Existen varias formas de restringir el acceso a ciertos sitios o a cierto tipo de contenido en la Internet, entre las más comunes están el uso de _firewalls_, servidores _proxy_, y por supuesto, usando un servidor de DNS. En el caso de los firewalls y servidores proxy,  una de las técnicas utilizadas consiste en analizar la información que pasa a través de ellos, a nivel de paquetes y, en base a ello determinan que contenido es admitido y cual es rechazado. Sin embargo, hay casos donde ésta técnica no funciona, por ejemplo, con los sitios que manejan contenido encriptado, como `https://facebook.com`, `https://youtube.com`, `https://twitter.com`, etc.

Como se han mencionado, con un servidor de DNS también podemos limitar el acceso a ciertos sitios, el método es sencillo, para cada sitio que deseemos bloquear agregamos una entrada en la base de nombres del servidor DNS y hacemos que apunten a otra dirección IP, por ejemplo, a una página Web local que les notifique porque se les ha restringido el acceso.

Para cada sitio que deseemos bloquear agregar una línea como la siguiente al final del archivo _/etc/dnsmasq.conf_:


```conf
address=/www.facebook.com/192.168.1.65

```

Cada vez que alguien intente conectarse a facebook, en servidor de DNS le regresará al cliente la dirección del servidor DNS, en el cual tenemos también ejecutándose un servidor Web, el cual mostrará al cliente una nota informativa del porque se le ha denegado el servicio.

![Denegación de acceso a facebook usando DNS](/dns-server-gnu-linux/dns_deny_facebook.png)

Esto es todo por esta práctica. DNS es un tema extenso y complejo, en esta práctica solo hemos visto unos ejemplos sencillos, aunque creo que es un buen punto de partida para aprender sobre este tema.

## Referencias

- [Domain Name System](https://en.wikipedia.org/wiki/Domain_Name_System)
- [Domain Name System](http://technet.microsoft.com/en-US/network/bb629410.aspx)
- [Dnsmasq](https://wiki.archlinux.org/index.php/Dnsmasq)
