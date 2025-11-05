/**
 */

#ifndef TRAMABASE_H
#define TRAMABASE_H

// Forward declarations
class ListaDeCarga;
class RotorDeMapeo;

/**
 * @class TramaBase
 * @brief Clase base abstracta que define la interfaz para todas las tramas
 * 
 * Esta clase utiliza polimorfismo para permitir el procesamiento
 * uniforme de diferentes tipos de tramas (LOAD y MAP)
 */
class TramaBase {
public:
    /**
     * @brief Destructor virtual
     * @details Necesario para la correcta liberación de memoria
     * al eliminar objetos derivados a través de punteros base
     */
    virtual ~TramaBase() {}
    
    /**
     * @brief Método virtual puro para procesar la trama
     * @param carga Puntero a la lista de carga donde se almacenan datos decodificados
     * @param rotor Puntero al rotor de mapeo que realiza las transformaciones
     * @details Cada clase derivada implementa su propia lógica de procesamiento
     */
    virtual void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) = 0;
};

#endif // TRAMABASE_H
