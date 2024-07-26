#include <iostream>      // Para std::cout y std::cerr Para manejar la entrada y salida estándar
#include <fstream>       // Para std::ofstream Para manejar operaciones con archivos
#include <random>        // Para la generación de números aleatorios
#include <cstring>       // Para std::strcmp Para manejar operaciones con cadenas de caracteres

// Función que genera un archivo con números enteros aleatorios
void generateFile(const std::string& filePath, size_t sizeInBytes) {
    // Abre un archivo binario para escribir
    std::ofstream file(filePath, std::ios::binary);

    // Configura el generador de números aleatorios
    std::mt19937 randomGenerator(std::random_device{}());
    std::uniform_int_distribution<int> distribution;

    // Calcula el número de enteros que caben en el tamaño especificado
    size_t numberOfIntegers = sizeInBytes / sizeof(int);

    // Genera y escribe números enteros aleatorios en el archivo
    for (size_t i = 0; i < numberOfIntegers; ++i) {
        int randomNumber = distribution(randomGenerator);
        file.write(reinterpret_cast<char*>(&randomNumber), sizeof(int));
    }
}

// Función principal del programa
int main(int argc, char* argv[]) {
    // Verifica que el número de argumentos sea correcto
    if (argc != 5) {
        std::cerr << "Uso: generator --size <SIZE> --output <OUTPUT FILE PATH>\n";
        return 1;
    }

    // Obtiene los argumentos de tamaño y ruta de salida
    std::string sizeFlag = argv[1];
    std::string sizeArgument = argv[2];
    std::string outputFlag = argv[3];
    std::string outputFilePath = argv[4];
    size_t fileSizeInBytes;

    // Verifica que los flags sean correctos
    if (sizeFlag != "--size" || outputFlag != "--output") {
        std::cerr << "Uso: generator --size <SIZE> --output <OUTPUT FILE PATH>\n";
        return 1;
    }

    // Determina el tamaño del archivo en bytes según el argumento proporcionado
    if (sizeArgument == "SMALL") {
        fileSizeInBytes = 512 * 1024 * 1024; // 512 MB
    } else if (sizeArgument == "MEDIUM") {
        fileSizeInBytes = 1024 * 1024 * 1024; // 1 GB
    } else if (sizeArgument == "LARGE") {
        fileSizeInBytes = 2 * 1024 * 1024 * 1024; // 2 GB
    } else {
        std::cerr << "Tamaño inválido. Use SMALL, MEDIUM o LARGE.\n";
        return 1;
    }

    // Genera el archivo con números aleatorios
    generateFile(outputFilePath, fileSizeInBytes);
    return 0;
}
