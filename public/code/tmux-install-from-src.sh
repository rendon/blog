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
