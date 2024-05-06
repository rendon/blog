
<p>Para aquellos que hallan tenido la oportunidad de trabajar con Wordpress estarán de acuerdo que el editor que éste proporciona no es muy cómodo que digamos puesto que carece de todas las características de un editor HTML, si trabajan en modo HTML claro esta.</p>

<p>Cuando publico por lo general lo hago en modo HTML usando mi editor de texto favorito([g]Vim por supuesto). Anteriormente el procedimiento era teclear el código en el editor y posteriormente copiarlo al editor de Wordpress, si había algo que modificar lo hacia en mi editor y nuevamente copiar todo el contenido al editor de Wordpress reemplazando el contenido anterior. Afortunadamente encontré la manera de enlazar a mi editor con Wordpress para que la creación y actualización de contenido se realice directamente desde mi editor: VimRepress.</p>

## Instalación y configuración

<p>El primer paso es ir a la <a href="http://www.vim.org/scripts/script.php?script_id=3510" target="__blank">página oficial del plugin</a> y descargamos la versión estable(al momento de escribir este artículo es la 2.1.5). Una vez descargado el plugin desde una terminal realizamos lo siguiente:</p>

<pre lang="bash" theme="slate">
$ cd ~/.vim
$ unzip /path/to/plugin/vimpress-stable_2.1.5_r81_13e8413bc8e7.zip
</pre>

<p>Con esto el plugin ya esta instalado y solo falta configurar la conexión con Wordpress. Abrimos el archivo `.vimrc` y agregamos lo siguiente, reemplazando los datos de ejemplo con los suyos.</p>

Embed: `config.vim`

<p>A partir de la versión `3.x` el plugin tiene su propio archivo de configuración y con distinto formato. Sin embargo aquí he usado la versión `2.x` ya que es más estable.</p>


## Como trabaja Vimrepress

<p>Para empezar a trabar con el plugin simplemente abren [g]Vim y tienen a sus disposición los siguientes comandos a sus disposición:</p>
 
Embed: `commands.txt`

<p>Y con esto terminamos este post. Espero que les sea de utilidad. Hasta la próxima!</p>

## Referencias
<table border="0">
  <tr>
    <td>[1]</td> <td><a href="http://www.vim.org/scripts/script.php?script_id=3510" target="__blank">Sitio oficial de Vimrepress</a></td>
  </tr>
</table>

