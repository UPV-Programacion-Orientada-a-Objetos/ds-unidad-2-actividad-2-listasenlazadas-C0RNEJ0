/**
 * @file RotorDeMapeo.cpp
 * @brief Implementación de la clase RotorDeMapeo
 */

#include "RotorDeMapeo.h"
#include <iostream>

RotorDeMapeo::RotorDeMapeo() : cabeza(nullptr), tamano(26) {
    // Crear el alfabeto A-Z en forma circular
    NodoRotor* primero = nullptr;
    NodoRotor* anterior = nullptr;
    
    for (int i = 0; i < 26; i++) {
        NodoRotor* nuevo = new NodoRotor;
        nuevo->dato = 'A' + i;
        nuevo->siguiente = nullptr;
        nuevo->previo = anterior;
        
        if (i == 0) {
            primero = nuevo;
            cabeza = nuevo;
        } else {
            anterior->siguiente = nuevo;
        }
        
        anterior = nuevo;
    }
    
    // Cerrar el círculo
    if (anterior && primero) {
        anterior->siguiente = primero;
        primero->previo = anterior;
    }
}

RotorDeMapeo::~RotorDeMapeo() {
    if (!cabeza) return;
    
    // Romper el círculo
    NodoRotor* ultimo = cabeza->previo;
    ultimo->siguiente = nullptr;
    
    // Eliminar todos los nodos
    NodoRotor* actual = cabeza;
    while (actual) {
        NodoRotor* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

void RotorDeMapeo::rotar(int n) {
    if (!cabeza || tamano == 0) return;
    
    // Normalizar la rotación
    n = n % tamano;
    if (n < 0) n += tamano;
    
    // Mover la cabeza n posiciones hacia adelante
    for (int i = 0; i < n; i++) {
        cabeza = cabeza->siguiente;
    }
}

NodoRotor* RotorDeMapeo::encontrarNodo(char c) {
    if (!cabeza) return nullptr;
    
    NodoRotor* actual = cabeza;
    do {
        if (actual->dato == c) {
            return actual;
        }
        actual = actual->siguiente;
    } while (actual != cabeza);
    
    return nullptr;
}

int RotorDeMapeo::calcularDistancia(NodoRotor* desde, NodoRotor* hasta) {
    if (!desde || !hasta) return 0;
    
    int distancia = 0;
    NodoRotor* actual = desde;
    
    while (actual != hasta && distancia < tamano) {
        actual = actual->siguiente;
        distancia++;
    }
    
    return distancia;
}

char RotorDeMapeo::getMapeo(char in) {
    // Manejar espacios y caracteres especiales
    if (in == ' ' || in < 'A' || in > 'Z') {
        return in;
    }
    
    // Encontrar el nodo del carácter de entrada
    NodoRotor* nodoIn = encontrarNodo(in);
    if (!nodoIn) return in;
    
    // Calcular la distancia desde la cabeza hasta el carácter
    int distancia = calcularDistancia(cabeza, nodoIn);
    
    // Aplicar la misma distancia desde la posición 'A' original
    // para obtener el carácter mapeado
    NodoRotor* nodoA = encontrarNodo('A');
    if (!nodoA) return in;
    
    NodoRotor* resultado = nodoA;
    for (int i = 0; i < distancia; i++) {
        resultado = resultado->siguiente;
    }
    
    return resultado->dato;
}

void RotorDeMapeo::imprimir() {
    if (!cabeza) {
        std::cout << "Rotor vacío" << std::endl;
        return;
    }
    
    std::cout << "Estado del rotor (cabeza en '" << cabeza->dato << "'): ";
    NodoRotor* actual = cabeza;
    int contador = 0;
    
    do {
        std::cout << actual->dato;
        if (contador < tamano - 1) std::cout << " ";
        actual = actual->siguiente;
        contador++;
    } while (actual != cabeza && contador < tamano);
    
    std::cout << std::endl;
}
