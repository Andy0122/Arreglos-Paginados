//
// Created by andy on 27/07/24.
//

#ifndef PAGEDARRAY_H
#define PAGEDARRAY_H

#include "Page.h"
#include <fstream>
#include <string>

class PagedArray {
public:
    // Constructor que inicializa el objeto con la ruta al archivo binario
    PagedArray(const std::string& filePath);

    // Destructor que libera la memoria utilizada por las páginas cargadas
    ~PagedArray();

    // Sobrecarga del operador [] para proporcionar acceso a los elementos como si fuera un arreglo normal
    int& operator[](int index);

    // Métodos para obtener el número de page hits y page faults
    long getPageHits() const;
    long getPageFaults() const;

    int getSize() const;

    void setValue(int index, int value);

private:
    // Atributos que representan las cuatro páginas
    Page* page1;
    Page* page2;
    Page* page3;
    Page* page4;

    // Archivo de flujo utilizado para leer y escribir en el archivo binario
    std::fstream file;

    // Ruta del archivo binario que se está utilizando
    std::string filePath;

    // Contadores para page hits y page faults
    long pageHits;
    long pageFaults;

    // Método privado para cargar una página desde el disco
    void loadPage(int pageIndex);
    void savePage(Page* page);

    // Método privado para encontrar un slot vacío o reemplazable en el vector de páginas
    Page*& findEmptyOrReplaceableSlot();

    int size;

    friend void swap(PagedArray& arr, int i, int j);

};

void swap(PagedArray& arr, int i, int j);

#endif // PAGEDARRAY_H

