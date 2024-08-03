#include <iostream>
#include <fstream>
#include <cstring>
#include "PagedArray.h"
#include "SortingAlgorithms.h"
#include <chrono>
#include <vector>

void copyFile(const std::string& src, const std::string& dest) {
    std::ifstream srcFile(src, std::ios::binary);
    if (!srcFile) {
        throw std::runtime_error("No se pudo abrir el archivo de origen.");
    }

    std::ofstream destFile(dest, std::ios::binary);
    if (!destFile) {
        throw std::runtime_error("No se pudo abrir el archivo de destino.");
    }

    destFile << srcFile.rdbuf();
}


// Función para convertir un archivo binario a un archivo de texto
void convertBinaryToText(const std::string& binaryFilename, const std::string& textFilename) {
    try {
        // Abrir el archivo binario en modo lectura
        std::ifstream binaryFile(binaryFilename, std::ios::binary);
        if (!binaryFile) {
            throw std::runtime_error("No se pudo abrir el archivo binario: " + binaryFilename);
        }

        // Crear un archivo de texto en modo escritura
        std::ofstream textFile(textFilename);
        if (!textFile) {
            throw std::runtime_error("No se pudo crear el archivo de texto: " + textFilename);
        }

        // Leer y escribir los números enteros del archivo binario al archivo de texto
        int number;
        bool first = true; // Para manejar la coma antes del primer número
        while (binaryFile.read(reinterpret_cast<char*>(&number), sizeof(int))) {
            if (!first) {
                textFile << ", ";
            }
            textFile << number;
            first = false;
        }

        // Mensaje de éxito
        std::cout << "Conversión completada. Los números han sido escritos en " << textFilename << std::endl;

        // Cerrar los archivos
        binaryFile.close();
        textFile.close();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main(int argc, char* argv[]) {
    auto startInsertion = std::chrono::high_resolution_clock::now();

    if (argc != 7) {
        std::cerr << "Uso: sorter -input <INPUT FILE PATH> -output <OUTPUT FILE PATH> -alg <ALGORITMO>" << std::endl;
        return 1;
    }

    std::string inputFile;
    std::string outputFile;
    std::string algorithm;

    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "-input") == 0) {
            inputFile = argv[++i];
        } else if (std::strcmp(argv[i], "-output") == 0) {
            outputFile = argv[++i];
        } else if (std::strcmp(argv[i], "-alg") == 0) {
            algorithm = argv[++i];
        }
    }

    try {
        // Copiar el archivo de entrada al archivo de salida
        copyFile(inputFile, outputFile);

        // Crear una instancia de PagedArray con el archivo binario copiado
        PagedArray pagedArray(outputFile);

        // Determinar el tamaño del PagedArray
        int size = pagedArray.getSize();

        // Ejecutar el algoritmo de ordenamiento seleccionado
        if (algorithm == "QS") {
            quickSort(pagedArray, 0, size - 1);
        } else if (algorithm == "IS") {
            insertionSort(pagedArray, size);
        } else if (algorithm == "BS") {
            bubbleSort(pagedArray, size);
        } else {
            std::cerr << "Algoritmo no reconocido: " << algorithm << std::endl;
            return 1;
        }

        // Generar el nombre del archivo de texto
        std::string textFilename = outputFile.substr(0, outputFile.find_last_of('.')) + ".txt";

        // Llamar a convertBinaryToText para crear el archivo de texto
        convertBinaryToText(outputFile, textFilename);

        auto endInsertion = std::chrono::high_resolution_clock::now();

        // Imprimir resumen
        std::cout << "Algoritmo utilizado: " << algorithm << std::endl;
        std::chrono::duration<double> durationInsertion = endInsertion - startInsertion;
        std::cout << "Tiempo de ordenamiento: " << durationInsertion.count() << " segundos" << std::endl;
        std::cout << "Page Hits: " << pagedArray.getPageHits() << std::endl;
        std::cout << "Page Faults: " << pagedArray.getPageFaults() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
