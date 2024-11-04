<!-- vim: set spelllang=es_MX: -->
<!-- slug: cifrar dispositivo con LUKS -->

---
tags:
    - sysadmin
    - seguridad
    - linux
created: 2024-04-26
---
# Cifrar dispositivos con LUKS

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
---
tags:
    - sysadmin
    - seguridad
    - linux
created: 2024-04-26
---
# Encuentra tu dispositivo
lsblk

---
tags:
    - sysadmin
    - seguridad
    - linux
created: 2024-04-26
---
# Formatea el dispositivo con formato LUKS
sudo cryptsetup luksFormat <dispositivo>

---
tags:
    - sysadmin
    - seguridad
    - linux
created: 2024-04-26
---
# Inspecciona el siguiente directorio
ls /dev/mapper/

---
tags:
    - sysadmin
    - seguridad
    - linux
created: 2024-04-26
---
# Abre dispositivo como <nombre>
sudo cryptsetup open <dispositivo> [<nombre>]

---
tags:
    - sysadmin
    - seguridad
    - linux
created: 2024-04-26
---
# Inspecciona el siguiente directorio nuevamente
ls /dev/mapper/<nombre>

---
tags:
    - sysadmin
    - seguridad
    - linux
created: 2024-04-26
---
# Crear un sistema de archivos
sudo mkfs.btrfs -L <etiqueta> /dev/mapper/<nombre>

---
tags:
    - sysadmin
    - seguridad
    - linux
created: 2024-04-26
---
# Cierra dispositivo
sudo cryptsetup close <dispositivo>
```


## Como usar tu dispositivo

```bash
---
tags:
    - sysadmin
    - seguridad
    - linux
created: 2024-04-26
---
# Encuentra tu dispositivo
lsblk

---
tags:
    - sysadmin
    - seguridad
    - linux
created: 2024-04-26
---
# Abre dispositivo como <nombre>
sudo cryptsetup open <dispositivo> [<nombre>]

---
tags:
    - sysadmin
    - seguridad
    - linux
created: 2024-04-26
---
# Monta el dispositivo
sudo mount /dev/mapper/<nombre> /mnt/

---
tags:
    - sysadmin
    - seguridad
    - linux
created: 2024-04-26
---
# Lee o escribe como normalmente lo haces

---
tags:
    - sysadmin
    - seguridad
    - linux
created: 2024-04-26
---
# Desmonta el dispositivo
sudo umount /mnt/

---
tags:
    - sysadmin
    - seguridad
    - linux
created: 2024-04-26
---
# Cierra dispositivo
sudo cryptsetup close <dispositivo>
```

## Interfaces gráficas
Debo mencionar que existen interfaces gráficas para hacer todo lo que les mostré en este articulo, pero eso lo dejamos para otra ocasión.

Pues bien, eso es todo. Recuerden guardar muy bien la contraseña. Hasta la próxima.
