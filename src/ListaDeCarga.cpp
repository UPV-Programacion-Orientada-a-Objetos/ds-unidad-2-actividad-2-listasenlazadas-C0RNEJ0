/**
 * @file ListaDeCarga.cpp
 * @brief Implementación de la clase ListaDeCarga
 */

#include "ListaDeCarga.h"
#include <iostream>

ListaDeCarga::ListaDeCarga() : cabeza(nullptr), cola(nullptr), tamano(0) {}

ListaDeCarga::~ListaDeCarga() {
    NodoCarga* actual = cabeza;
    while (actual) {
        NodoCarga* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

void ListaDeCarga::insertarAlFinal(char dato) {
    NodoCarga* nuevo = new NodoCarga;
    nuevo->dato = dato;
    nuevo->siguiente = nullptr;
    nuevo->previo = cola;
    
    if (cola) {
        cola->siguiente = nuevo;
    } else {
        // La lista está vacía
        cabeza = nuevo;
    }
    
    cola = nuevo;
    tamano++;
}

void ListaDeCarga::imprimirMensaje() {
    NodoCarga* actual = cabeza;
    std::cout << "[";
    while (actual) {
        std::cout << actual->dato;
        actual = actual->siguiente;
    }
    std::cout << "]";
}

int ListaDeCarga::getTamano() const {
    return tamano;
}

bool ListaDeCarga::estaVacia() const {
    return cabeza == nullptr;
}
