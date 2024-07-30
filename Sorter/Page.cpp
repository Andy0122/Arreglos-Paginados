//
// Created by andy on 28/07/24.
//

#include "Page.h"

// Constructor que inicializa el número de página
Page::Page(int pageNumber) : pageNumber(pageNumber) {
    numbers.fill(0); // Inicializar todos los números a 0 (opcional)
}

// Obtener el número de página
int Page::getPageNumber() const {
    return pageNumber;
}

// Obtener el valor en una posición específica
int& Page::getValue(int index) {
    if (index >= 0 && index < 128) {
        return numbers[index];
    }
    // Manejar el error de índice fuera de rango
    throw std::out_of_range("Índice fuera de rango");
}

// Obtener un puntero al buffer interno
int* Page::getBuffer() {
    return numbers.data();
}

// Establecer el valor en una posición específica
void Page::setValue(int index, int value) {
    if (index >= 0 && index < 128) {
        numbers[index] = value;
    } else {
        // Manejar el error de índice fuera de rango
        throw std::out_of_range("Índice fuera de rango");
    }
}
