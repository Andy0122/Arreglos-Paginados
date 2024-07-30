//
// Created by andy on 28/07/24.
//

#ifndef PAGE_H
#define PAGE_H

#include <array>
#include <stdexcept> // Incluir el encabezado para std::out_of_range

class Page {
public:
    // Constructor
    Page(int pageNumber);

    // Obtener el número de página
    int getPageNumber() const;

    // Obtener el valor en una posición específica (devuelve una referencia)
    int& getValue(int index);

    // Establecer el valor en una posición específica
    void setValue(int index, int value);

    // Obtener un puntero al buffer interno
    int* getBuffer();

private:
    int pageNumber;                   // Número de página
    std::array<int, 128> numbers;     // Arreglo de 128 números enteros
};

#endif // PAGE_H
