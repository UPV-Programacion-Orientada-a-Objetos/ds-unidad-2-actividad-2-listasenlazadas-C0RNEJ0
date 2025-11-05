/**

 */

#ifndef LISTADECARGA_H
#define LISTADECARGA_H

/**
 * @struct NodoCarga
 * @brief Nodo de la lista doblemente enlazada
 */
struct NodoCarga {
    char dato;           ///< Carácter decodificado
    NodoCarga* siguiente; ///< Puntero al siguiente nodo
    NodoCarga* previo;    ///< Puntero al nodo anterior
};

/**
 * @class ListaDeCarga
 * @brief Lista doblemente enlazada para almacenar la secuencia de datos decodificados
 * 
 * Mantiene el orden de llegada de los caracteres decodificados,
 * permitiendo reconstruir el mensaje original
 */
class ListaDeCarga {
private:
    NodoCarga* cabeza; ///< Primer nodo de la lista
    NodoCarga* cola;   ///< Último nodo de la lista
    int tamano;        ///< Cantidad de elementos en la lista
    
public:
    /**
     * @brief Constructor: inicializa lista vacía
     */
    ListaDeCarga();
    
    /**
     * @brief Destructor: libera toda la memoria de la lista
     */
    ~ListaDeCarga();
    
    /**
     * @brief Inserta un carácter al final de la lista
     * @param dato Carácter a insertar
     * @details Mantiene los punteros previo y siguiente actualizados
     */
    void insertarAlFinal(char dato);
    
    /**
     * @brief Imprime el mensaje completo almacenado
     * @details Recorre la lista e imprime cada carácter en secuencia
     */
    void imprimirMensaje();
    
    /**
     * @brief Obtiene el tamaño de la lista
     * @return Cantidad de caracteres almacenados
     */
    int getTamano() const;
    
    /**
     * @brief Verifica si la lista está vacía
     * @return true si está vacía, false en caso contrario
     */
    bool estaVacia() const;
};

#endif // LISTADECARGA_H
