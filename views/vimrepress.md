"=========== Meta ============
"StrID : 102
"Title : Publica en wordpress usando [g]Vim
"Slug  : vimrepress
"Cats  : 
"Tags  :
"=============================
"EditType   : post
"EditFormat : markdown
"TextAttach : vimpress_5377c2f8_mkd.txt
"========== Content ==========
[php]initialize();[/php]

Para aquellos que hallan tenido la oportunidad de trabajar con Wordpress estarán de acuerdo que el editor que éste proporciona no es muy cómodo que digamos puesto que carece de todas las características de un editor HTML, si trabajan en modo HTML claro esta.

Cuando publico por lo general lo hago en modo HTML usando mi editor de texto favorito([g]Vim por supuesto). Anteriormente el procedimiento era teclear el código en el editor y posteriormente copiarlo al editor de Wordpress, si había algo que modificar lo hacia en mi editor y nuevamente copiar todo el contenido al editor de Wordpress reemplazando el contenido anterior. Afortunadamente encontré la manera de enlazar a mi editor con Wordpress para que la creación y actualización de contenido se realice directamente desde mi editor: VimRepress.

#Instalación y configuración

El primer paso es ir a la <a href="http://www.vim.org/scripts/script.php?script_id=3510" target="__blank">página oficial del plugin</a> y descargamos la versión estable(al momento de escribir este artículo es la 2.1.5). Una vez descargado el plugin desde una terminal realizamos lo siguiente:

<pre lang="bash" theme="slate">
$ cd ~/.vim
$ unzip /path/to/plugin/vimpress-stable_2.1.5_r81_13e8413bc8e7.zip
</pre>

Con esto el plugin ya esta instalado y solo falta configurar la conexión con Wordpress. Abrimos el archivo <code>.vimrc</code> y agregamos lo siguiente, reemplazando los datos de ejemplo con los suyos.

<pre lang="vim">
let VIMPRESS = [{'username':'user',
                \'password':'pass',
                \'blog_url':'http://your-first-blog.com/'
                \},
                \{'username':'user',
                \'blog_url':'http://your-second-blog.com/'
                \}]
</pre>

A partir de la versión <code>3.x</code> el plugin tiene su propio archivo de configuración y con distinto formato. Sin embargo aquí he usado la versión <code>2.x</code> ya que es más estable.


#Como trabaja Vimrepress

Para empezar a trabar con el plugin simplemente abren [g]Vim y tienen a sus disposición los siguientes comandos a sus disposición:
 
<pre lang="vim">
:BlogList             -  Lista los 30 artículos más recientes
:BlogList page        -  Lista las 30 páginas más recientes
:BlogList post 100    -  Lista las 100 páginas más recientes

:BlogNew post         -  Escribir un artículo nuevo
:BlogNew page         -  Escribir una página nueva

:BlogSave             -  Guargar(por default se publica)
:BlogSave draft       -  Guardar como borrador

:BlogPreview local    -  Vista previa localmente in tu navegador
:BlogPreview publish  -  Igual que ':BlogSave publish' con navegador abierto

:BlogOpen 679         - Abir publicación con id 679
:BlogOpen http://your-first-blog.com/archives/679
:BlogOpen http://your-second-blog.com/?p=679
:BlogOpen http://your-third-blog.com/with-your-custom-permalink
</pre>

Y con esto terminamos este post. Espero que les sea de utilidad. Hasta la próxima!

#Referencias
<table border="0">
  <tr>
    <td>[1]</td> <td><a href="http://www.vim.org/scripts/script.php?script_id=3510" target="__blank">Sitio oficial de Vimrepress</a></td>
  </tr>
</table>

[php]finalize();[/php]
