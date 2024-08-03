# Sorter - Algoritmos de Ordenamiento de Archivos Binarios

## Descripción

Este proyecto implementa una aplicación en C++ para ordenar archivos binarios grandes que contienen números enteros aleatorios. Utiliza una clase `PagedArray` para manejar la paginación y soporta tres algoritmos de ordenamiento diferentes: Quick Sort, Insertion Sort y Bubble Sort.

## Características

- Ordenamiento de archivos binarios grandes.
- Implementación de la clase `PagedArray` para manejar la paginación.
- Soporte para Quick Sort, Insertion Sort y Bubble Sort.
- Generación de estadísticas sobre page hits y page faults.
- Conversión del archivo binario ordenado a un archivo de texto legible.

## Requisitos

- Compilador C++ (compatible con C++11 o superior)
- Sistema operativo: Linux, macOS o Windows
- Git (para clonar el repositorio)

## Instalación

### Paso 1: Clonar el repositorio

git clone https://github.com/Andy0122/Arreglos-Paginados.git
cd tu-repositorio

Paso 2: Compilar el proyecto
En Linux y macOS

g++ -o sorter main.cpp PagedArray.cpp SortingAlgorithms.cpp Page.cpp
g++ -o generator generator.cpp

En Windows
Usa MinGW o cualquier compilador C++ compatible. Asegúrate de que g++ esté en tu PATH.

g++ -o sorter main.cpp PagedArray.cpp SortingAlgorithms.cpp Page.cpp
g++ -o generator generator.cpp

Uso
Generar un archivo binario
El programa generator se ejecuta desde la línea de comandos con los siguientes argumentos:

./generator -size <SIZE> -output <OUTPUT FILE PATH>

    <SIZE>: Tamaño del archivo binario a generar. Puede ser uno de los siguientes valores: SMALL, MEDIUM, LARGE.
        SMALL: 512 MB
        MEDIUM: 1 GB
        LARGE: 2 GB
    <OUTPUT FILE PATH>: Ruta del archivo binario de salida.
    
    Ejemplo de Uso:

    ./generator -size MEDIUM -output input.bin


Ordenar un archivo binario

El programa sorter se ejecuta desde la línea de comandos con los siguientes argumentos:

./sorter -input <INPUT FILE PATH> -output <OUTPUT FILE PATH> -alg <ALGORITMO>

    <INPUT FILE PATH>: Ruta del archivo binario de entrada.
    <OUTPUT FILE PATH>: Ruta del archivo binario de salida.
    <ALGORITMO>: Algoritmo de ordenamiento a utilizar (QS para Quick Sort, IS para Insertion Sort, BS para Bubble Sort).

Ejemplo de Uso:

    ./sorter -input input.bin -output output.bin -alg QS

Este comando ordenará el archivo input.bin utilizando Quick Sort y guardará el resultado en output.bin. Además, generará un archivo de texto output.txt con los números ordenados.
Prueba del Programa

El programa fue probado en la siguiente configuración:

    Sistema Operativo: Ubuntu 20.04 LTS
    Compilador: g++ (GCC) 9.3.0
    Hardware: ryzen 5 5550h, 16GB RAM, HDD

Funciones Principales
main.cpp

    Argumentos de entrada: El programa acepta los argumentos requeridos (-input, -output, -alg).
    Copia del archivo de entrada al archivo de salida: Correctamente implementado.
    Instancia de PagedArray: Correctamente creada y utilizada.
    Algoritmo de ordenamiento: Se ejecuta el algoritmo seleccionado (Quick Sort, Insertion Sort, Bubble Sort) según el argumento -alg.
    Resumen impreso al finalizar: Imprime el algoritmo utilizado, el tiempo durado, y las estadísticas de page hits y page faults.
    Conversión a archivo de texto: Implementado, convierte el archivo binario ordenado a un archivo de texto con la misma base de nombre.

PagedArray.h y PagedArray.cpp

    Sobrecarga del operador []: Correctamente implementada para manejar el acceso a elementos con lógica de paginación.
    Page hits y page faults: Correctamente implementados y contados.
    Lógica de paginación: Carga y reemplazo de páginas implementados.

SortingAlgorithms.h y SortingAlgorithms.cpp

    Algoritmos de ordenamiento: Implementaciones de Quick Sort, Insertion Sort y Bubble Sort están correctas.

convertBinaryToText

    Conversión del archivo binario a texto: Implementado correctamente y llamado al final del proceso de ordenamiento.

Ejecución del Programa

Para ejecutar el programa, usa el siguiente comando:

    ./sorter -input <ruta_del_archivo_de_entrada> -output <ruta_del_archivo_de_salida> -alg <algoritmo>

Por ejemplo:

    ./sorter -input input.bin -output output.bin -alg QS

Esto ordenará el archivo binario input.bin utilizando el algoritmo Quick Sort y guardará el archivo ordenado en output.bin. Además, creará un archivo de texto output.txt con los números ordenados.
Notas Adicionales

    Algoritmos de Ordenamiento:
        QS - Quick Sort
        IS - Insertion Sort
        BS - Bubble Sort

    Estadísticas de Paginación:
        Page Hits: Número de veces que se accedió a una página que ya estaba cargada en memoria.
        Page Faults: Número de veces que se tuvo que cargar una página desde el disco porque no estaba en memoria.



