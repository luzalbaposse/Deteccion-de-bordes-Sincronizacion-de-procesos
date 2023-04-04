# Procesos y Threads 🔄🔀

Este trabajo práctico se enfoca en la creación y manejo de procesos y threads en C, y su implementación en el filtro de detección de bordes sobre imágenes.

La creación de procesos se realiza mediante primitivas del sistema operativo, como fork(), que permite crear una copia del proceso original en un espacio de memoria diferente, mientras que los threads ejecutan en el mismo espacio de memoria que el proceso padre, pero en un contexto de ejecución diferente. En este trabajo práctico se utilizan threads para simplificar la operatoria y reducir los costos de crear nuevos procesos.

Para crear y esperar por la finalización de los threads, se utilizan los llamados a funciones pthread_create() y pthread_join(), respectivamente. Estos llamados forman parte de la librería pthread y permiten generar threads contra el sistema operativo.

En los ejercicios del trabajo práctico, se utiliza un arreglo en memoria compartida por múltiples threads, lo que requiere una sincronización adecuada entre los threads para obtener un resultado correcto.

### Ejercicio 1
En este ejercicio, se implementa la solución con dos threads de forma vertical, es decir, cada thread toma la mitad de las columnas y recorre la matriz por todas las filas. La solución se implementa en el archivo EdgeDetect_P2V.c.

### Ejercicio 2
En este ejercicio, se extrapolan las soluciones horizontal y vertical para dos threads y se implementa el algoritmo de detección de bordes utilizando 4 threads de forma horizontal y vertical. Se debe tener en cuenta que los procesos en los threads centrales tendrán dos caras lindantes, procesos a derecha e izquierda o arriba y abajo según corresponda. Esto implica que estos procesos recorrerán al menos una columna o fila de más. La solución se implementa en los archivos EdgeDetect_P4H.c y EdgeDetect_P4V.c, respectivamente.

### Ejercicio 3
En este ejercicio se realiza una tabla de tiempos para medir el tiempo que lleva cada implementación. Se miden los tiempos de EdgeDetect, EdgeDetect_P2H, EdgeDetect_P2V, EdgeDetect_P4H y EdgeDetect_P4V.

# Integrantes:
- Thomas Catz
- Tomás Ibarra
- Luz Alba Posse
