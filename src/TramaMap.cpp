/**
 * @file TramaMap.cpp
 * @brief Implementación de la clase TramaMap
 */

#include "TramaMap.h"
#include "RotorDeMapeo.h"
#include <iostream>

TramaMap::TramaMap(int n) : rotacion(n) {}

TramaMap::~TramaMap() {}

void TramaMap::procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) {
    // Rotar el rotor según la cantidad especificada
    rotor->rotar(rotacion);
    
    // Mostrar información de procesamiento
    std::cout << std::endl;
    std::cout << "Trama recibida: [M," << rotacion << "] -> Procesando... -> ";
    std::cout << "ROTANDO ROTOR ";
    if (rotacion > 0) {
        std::cout << "+" << rotacion;
    } else {
        std::cout << rotacion;
    }
    std::cout << std::endl << std::endl;
}

int TramaMap::getRotacion() const {
    return rotacion;
}
