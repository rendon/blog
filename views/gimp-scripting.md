"=========== Meta ============
"StrID : 98
"Title : Gimp scripting
"Slug  : gimp-scripting
"Cats  : Sin categoría
"Tags  : 
"=============================
"EditType   : post
"EditFormat : Markdown
"TextAttach : wpid1419-vimpress_5377c0ac_mkd.txt
"========== Content ==========
[php]initialize();[/php]

#Problemática
Hola! En estos días he estado trabajando en un proyecto web junto con algunos compañeros de clase y estoy contento porque he aprendido muchas cosas interesantes, hoy les voy a hablar de una de ellas.

Estamos desarrollando un sitio web para un centro comercial y empleamos muchas imágenes para los distintos productos que se ofertan. Cada uno de los integrantes se encargo de recolectar información de los productos de las distintas secciones y el problema empezó cuando cada quien recolecto fotos de distintos tamaños y era necesario redimensionar y decorar cada una de las imágenes a un tamaño adecuado(150x150). Tiempo atrás ya había oído hablar que se podían emplear scripts con gimp para automatizar la edición de imágenes así que me puse a investigar.

Gimp soporta scripts en <a href="http://www.gimp.org/docs/python/index.html" target="_blank">python</a> y en <a href="http://www.gimp.org/tutorials/Basic_Scheme/" target="_blank">scheme</a>, de los cuales he optado por python. A continuación el código que emplee para resolver mi problema. 

<pre lang="cpp" theme="slate" line="1">
import os, re
from gimpfu import *

for file in os.listdir(os.getcwd()):
    if not re.search('jpeg', file):
        continue

    image = pdb.gimp_file_load(file, '1') # Open file
    pdb.gimp_image_scale(image, 150, 150) # and scale

    # Apply round corners filter
    drawable = pdb.gimp_image_active_drawable(image)
    pdb.script_fu_round_corners(image, drawable, 9, 1, 8, 8, 9, 0, 0)
    image.merge_visible_layers(0)
    drawable = pdb.gimp_image_active_drawable(image)

    # Save file with PNG format
    temp = file.split('.')
    temp.pop()
    output_file = temp.pop() + ".png"
    pdb.gimp_file_save(image, drawable, output_file, 'Saved file')
</pre>

En este ejemplo mis imágenes están en formato JPEG pero ustedes pueden modificarlo para adaptarlo a sus necesidades. En la línea 2 importamos todo el contenido del modulo <code>gimpfu</code> el cual contiene todo lo necesario para trabajar con gimp, <code>os</code> y <code>re</code> son de utilería.

Desde una consola nos trasladamos al directorio donde están las imágenes y ejecutamos gimp. Vamos a Filters <code>-></code>Python-Fu<code>-></code>Console</code>, tenemos dos opciones, teclear el código ahí directamente o lo guardamos en un archivo y lo ejecutamos en el interprete con la función <code>execfile('script.py')</code>.

La documentación de las funciones que empleo en el script y muchas más la proporciona el mismo gimp y podemos acceder a ella con el botón <code>Browse...</code>. Hasta aquí con este post, espero que esta información les sea tan útil como a mi o más.

[php]figure('gimp_documentation', 'Documentación de GIMP', 'gimp_documentation', 'png', 'ES');[/php]

#Referencias

- [1] <a href="http://www.gimp.org/docs/python/index.html" target="_blank">GIMP Python Documentation</a>
- [2] <a href="http://www.gimp.org/tutorials/Basic_Scheme/" target="_blank">Basic Scheme</a</a>>

[php]finalize();[/php]
