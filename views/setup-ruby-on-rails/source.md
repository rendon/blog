<!-- vim: set spelllang=es_mx: -->

# Set up Ruby on Rails
2016-02-18 2024-05-07 #dev #ruby #rails #post

Como parte de un reporte de proyecto necesito un manual sobre como instalar y configurar Ruby On Rails, si bien es cierto que en Internet hay gran cantidad de tutoriales, para mi reporte necesito una fuente confiable, algo de lo que este yo seguro de que funciona, y como dice el dicho, si quieres algo bien hecho, hazlo tu mismo. En este tutorial vamos a ver como obtener y configurar un Ruby On Rails en GNU/Linux Debian Wheezy.

## Instalación de Ruby

Lo primero va ser instalar Ruby, Debian Wheezy incluye la versión 1.9.3.

<pre lang="bash" theme="slate">
apt-get install ruby
</pre>

## RVM - Ruby Version Manager

Trabajar con Ruby puede llegar a ser problemático por que es muy común tener que instalar paquetes y para ello se requiere tener permisos administrativos, peor aun, en ocasiones necesitamos trabajar con más de una versión de ruby para diferentes proyectos, y es cuando empiezan los conflictos. RVM, permite crear entornos independientes de Ruby que permiten trabajar con diferentes versiones de Ruby, cada cual con sus paquetes y configuraciones, ver [rvm.io](https://rvm.io/) para más información.

Primero necesitamos `curl`.

<pre lang="bash" theme="slate">
sudo apt-get install curl
</pre>

Ahora instalamos RVM.

<pre lang="bash" theme="slate">
curl -L get.rvm.io | bash -s stable --auto
</pre>

El comando anterior instala RVM en el directorio home del usuario, por lo que no afecta las configuraciones de otros usuarios.

Vamos a necesitar de otros paquetes por lo que hay que instalarlos, como usuario **root** ejecuta el siguiente comando.

<pre lang="bash" theme="slate">
apt-get install build-essential openssl libreadline6 libreadline6-dev \
curl git-core zlib1g zlib1g-dev libssl-dev libyaml-dev libsqlite3-dev sqlite3 \
libxml2-dev libxslt-dev autoconf libc6-dev ncurses-dev automake libtool bison  \
subversion pkg-config
</pre>

## Ruby

Para nuestro proyecto vamos a utilizar la version 2.0 de Ruby, la cual instalamos con el siguiente comando, para esto **no** necesitamos estar como usuario root.

<pre lang="bash" theme="slate">
rvm install 2.0.0
</pre>

Esto tardará un poco. Ahora vamos a activar la versión 2.0 por defecto.

<pre lang="bash" theme="slate">
ruby -v
rvm --default use 2.0.0-p247
</pre>

## Rails

La versión más reciente del Ruby On Rails es la 4.0, ésta es la que vamos autilizar para nuestro proyecto.

<pre lang="bash" theme="slate">
gem install rails -v 4.0.0
</pre>
