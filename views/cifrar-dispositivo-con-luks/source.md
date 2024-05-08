<!-- vim: set spelllang=es_MX: -->
<!-- slug: cifrar dispositivo con LUKS -->

# Cifrar dispositivos con LUKS
2024-04-26 15:33:19 #sysadmin #seguridad #linux

<div class='video'>
  <iframe width="560" height="315" src="https://www.youtube.com/embed/YIzfk069uYE?si=4e04fXz5mVrq9L2p" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>
</div>

Hola a todos, espero que se encuentren bien. Mi nombre es Rafael. En este vídeo les muestro como cifrar un dispositivo en Linux para que puedan guardar información de manera segura.

Debo mencionar, que el enfoque de este vídeo es datos personales, es decir, una cantidad relativamente pequeña que puede almacenarse en solo disco duro.

Probablemente no sea necesario explicar la importancia de respaldar nuestros datos. Sin embargo, quizá menos sabido es que una copia no es suficiente. El principio del 3-2-1:

- 3 copias
- 2 medios (por ejemplo, disco duro y USB)
- 1 de ellos debe ser externo (por ejemplo, una copia en S3)

Algo que yo quiero poder hacer es guardar una copia en la casa, o encargarla con alguien de confianza, pero esto no es posible si los datos no están cifrados ya que alguien podría robar el dispositivo. La buena noticia es que ahora puedo justo hacer eso si cifro el medio de almacenamiento.

## Configuración inicial:

```bash
# Encuentra tu dispositivo
lsblk

# Formatea el dispositivo con formato LUKS
sudo cryptsetup luksFormat <dispositivo>

# Inspecciona el siguiente directorio
ls /dev/mapper/

# Abre dispositivo como <nombre>
sudo cryptsetup open <dispositivo> [<nombre>]

# Inspecciona el siguiente directorio nuevamente
ls /dev/mapper/<nombre>

# Crear un sistema de archivos
sudo mkfs.btrfs -L <etiqueta> /dev/mapper/<nombre>

# Cierra dispositivo
sudo cryptsetup close <dispositivo>
```


## Como usar tu dispositivo

```bash
# Encuentra tu dispositivo
lsblk

# Abre dispositivo como <nombre>
sudo cryptsetup open <dispositivo> [<nombre>]

# Monta el dispositivo
sudo mount /dev/mapper/<nombre> /mnt/

# Lee o escribe como normalmente lo haces

# Desmonta el dispositivo
sudo umount /mnt/

# Cierra dispositivo
sudo cryptsetup close <dispositivo>
```

## Interfaces gráficas
Debo mencionar que existen interfaces gráficas para hacer todo lo que les mostré en este articulo, pero eso lo dejamos para otra ocasión.

Pues bien, eso es todo. Recuerden guardar muy bien la contraseña. Hasta la próxima.
