//
// Created by andy on 27/07/24.
//

#include "PagedArray.h"
#include <cstdlib>
#include <stdexcept> // Incluir el encabezado para std::runtime_error
#include <iostream>

// Constructor que inicializa el objeto con la ruta al archivo binario
PagedArray::PagedArray(const std::string& filePath)
    : filePath(filePath), pageHits(0), pageFaults(0), page1(nullptr), page2(nullptr), page3(nullptr), page4(nullptr) {
    // Calcular el número de páginas basado en el tamaño del archivo
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (file) {
        std::streamsize fileSize = file.tellg();
        numPages = fileSize / (128 * sizeof(int));
    } else {
        throw std::runtime_error("No se pudo abrir el archivo");
    }
}

// Destructor que libera la memoria utilizada por las páginas cargadas
PagedArray::~PagedArray() {
    delete page1;
    delete page2;
    delete page3;
    delete page4;
}

// Sobrecarga del operador [] para proporcionar acceso a los elementos como si fuera un arreglo normal
int& PagedArray::operator[](int index) {
    int pageIndex = index / 128; // Calcular el índice de la página
    int offset = index % 128; // Calcular el desplazamiento dentro de la página


    if (index < 0 || pageIndex >= numPages) {
        throw std::out_of_range("Índice fuera de los límites del array");
    }

    // Buscar si la página ya está cargada
    Page* pages[] = { page1, page2, page3, page4 };
    for (Page* page : pages) {
        if (page != nullptr && page->getPageNumber() == pageIndex) {
            ++pageHits; // Incrementar el contador de page hits
            return page->getValue(offset); // Devolver una referencia al valor en la página
        }
    }

    ++pageFaults; // Incrementar el contador de page faults
    loadPage(pageIndex); // Cargar la página desde el disco

    Page* newPages[] = { page1, page2, page3, page4 };

    // Volver a buscar después de cargar la página
    for (Page* page : newPages) {
        if (page != nullptr && page->getPageNumber() == pageIndex) {
            return page->getValue(offset); // Devolver una referencia al valor en la página
        }
    }
    throw std::runtime_error("Error al cargar la página"); // Lanzar una excepción si no se pudo cargar la página
}
void PagedArray::saveValue(int index, int value) {
    int pageIndex = index / 128;
    int offset = index % 128;

    Page* pages[] = { page1, page2, page3, page4 };
    for (Page* page : pages) {
        if (page != nullptr && page->getPageNumber() == pageIndex) {
            page->setValue(offset, value);
            break;
        }
    }
    file.open(filePath, std::ios::in | std::ios::out | std::ios::binary);
    if (!file) {
        throw std::runtime_error("No se pudo abrir el archivo");
    }
    file.seekp(pageIndex * 128 * sizeof(int) + offset * sizeof(int), std::ios::beg);
    file.write(reinterpret_cast<const char*>(&value), sizeof(int));
    file.close();
}
// Método privado para cargar una página desde el disco
void PagedArray::loadPage(int pageIndex) {
    std::cout << "Cargando página con índice: " << pageIndex << std::endl;
    Page*& slot = findEmptyOrReplaceableSlot(); // Encontrar un slot vacío o reemplazable

    if (slot != nullptr) {
        delete slot; // Liberar la memoria de la página existente
    }

    slot = new Page(pageIndex); // Crear una nueva página y asignarla al slot

    // Abrir el archivo en modo binario y leer los datos de la página
    file.open(filePath, std::ios::in | std::ios::binary);
    if (!file) {
        throw std::runtime_error("No se pudo abrir el archivo");
    }
    file.seekg(pageIndex * 128 * sizeof(int), std::ios::beg);
    file.read(reinterpret_cast<char*>(slot->getBuffer()), 128 * sizeof(int));
    if (!file) {
        throw std::runtime_error("Error al leer el archivo");
    }
    file.close();
}

Page*& PagedArray::findEmptyOrReplaceableSlot() {
    if (page1 == nullptr) return page1;
    if (page2 == nullptr) return page2;
    if (page3 == nullptr) return page3;
    if (page4 == nullptr) return page4;

    // Devolver una referencia a un slot aleatorio si no hay slots vacíos
    int slot = std::rand() % 4;
    switch (slot) {
        case 0: return page1;
        case 1: return page2;
        case 2: return page3;
        case 3: return page4;
        default: return page1; // Por si acaso, aunque no debería suceder
    }
}


// Métodos para obtener el número de page hits y page faults
int PagedArray::getPageHits() const {
    return pageHits; // Devolver el número de page hits
}

int PagedArray::getPageFaults() const {
    return pageFaults; // Devolver el número de page faults
}

int PagedArray::getSize() const {
    return numPages * 128;
}

void swap(PagedArray& arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr.saveValue(i, arr[j]);
    arr[j] = temp;
    arr.saveValue(j, temp);
}


