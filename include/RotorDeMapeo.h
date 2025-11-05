/**

 */

#ifndef ROTORDEMAPEO_H
#define ROTORDEMAPEO_H

/**
 * @struct NodoRotor
 * @brief Nodo de la lista circular doblemente enlazada
 */
struct NodoRotor {
    char dato;           ///< Carácter almacenado
    NodoRotor* siguiente; ///< Puntero al siguiente nodo
    NodoRotor* previo;    ///< Puntero al nodo anterior
};

/**
 * @class RotorDeMapeo
 * @brief Lista circular doblemente enlazada que actúa como disco de cifrado
 * 
 * Implementa un mecanismo similar a la Rueda de César donde la rotación
 * del rotor cambia el mapeo de caracteres. El alfabeto A-Z está dispuesto
 * en forma circular.
 */
class RotorDeMapeo {
private:
    NodoRotor* cabeza; ///< Puntero que marca la posición 'cero' actual
    int tamano;        ///< Cantidad de caracteres en el rotor
    
    /**
     * @brief Encuentra un nodo por su carácter
     * @param c Carácter a buscar
     * @return Puntero al nodo encontrado o nullptr
     */
    NodoRotor* encontrarNodo(char c);
    
    /**
     * @brief Calcula la distancia entre dos nodos
     * @param desde Nodo origen
     * @param hasta Nodo destino
     * @return Cantidad de pasos desde el origen al destino
     */
    int calcularDistancia(NodoRotor* desde, NodoRotor* hasta);
    
public:
    /**
     * @brief Constructor: inicializa el rotor con el alfabeto A-Z
     */
    RotorDeMapeo();
    
    /**
     * @brief Destructor: libera toda la memoria del rotor
     */
    ~RotorDeMapeo();
    
    /**
     * @brief Rota el rotor N posiciones
     * @param n Cantidad de posiciones (positivo: horario, negativo: antihorario)
     * @details Mueve el puntero cabeza circularmente
     */
    void rotar(int n);
    
    /**
     * @brief Mapea un carácter según la rotación actual
     * @param in Carácter de entrada
     * @return Carácter mapeado según el estado del rotor
     * @details Encuentra la posición relativa del carácter y devuelve
     * el carácter que está en esa posición desde la cabeza actual
     */
    char getMapeo(char in);
    
    /**
     * @brief Imprime el estado actual del rotor (para debug)
     */
    void imprimir();
};

#endif // ROTORDEMAPEO_H
