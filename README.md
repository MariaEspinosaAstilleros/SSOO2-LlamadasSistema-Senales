## Práctica 1 - Llamadas al sistema y señales 

### Objetivo
El programa consta de un proceso principal *manager* encargado de crear y coordinar al resto de procesos. Dichos procesos deben acceder al fichero *estudiantes.txt*, el cual consta de un conjunto de líneas donde se especifica la siguiente información en cada una de ellas:
* DNI del estudiante
* Modelo de examen que debe realizar
* Nota que obtuvo en el examen anterior

El proceso *manager* debe crear tres tipos de procesos **PA**, **PB** y **PC**, cada uno de ellos con una labor diferente. 
* En primer lugar el *manager* debe crear un proceso **PA** y esperar que finalice. El proceso **PA** debe realizar una lectura del fichero *estudiantes.txt* para crear un directorio por estudiante; el nombre del directorio debe ser el mismo que el DNI del estudiante.
* Después el proceso *manager* debe crear un proceso **PB** y otro **PC** que deben trabajar simultáneamente. El proceso **PB** debe hacer una lectura del fichero *estudiantes.txt* para extraer el modelo de examen que debe realizar cada estudiante. El proceso **PC** debe copiar en cada directorio de estudiante el modelo que le corresponda.
* Si el usuario pulsa *CTRL+C* el proceso *manager* debe crear un cuarto proceso **PD** que se encargue de eliminar todos los directorios y archivos asociados a los estudiantes. 

### Compilación y ejecución del código
Para compilar y ejecutar se escribe en el terminal 
```shell
make 
```
![Texto](/img/make.png)
