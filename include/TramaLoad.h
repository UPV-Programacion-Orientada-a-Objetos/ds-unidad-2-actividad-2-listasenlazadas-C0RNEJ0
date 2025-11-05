/**

 */

#ifndef TRAMALOAD_H
#define TRAMALOAD_H

#include "TramaBase.h"

/**
 * @class TramaLoad
 * @brief Representa una trama de carga que contiene un carácter a decodificar
 * 
 * Las tramas LOAD contienen un fragmento de datos que debe ser
 * mapeado según el estado actual del rotor y almacenado en la lista de carga
 */
class TramaLoad : public TramaBase {
private:
    char dato; ///< Carácter recibido en la trama
    
public:
    /**
     * @brief Constructor de la trama LOAD
     * @param c Carácter a almacenar en la trama
     */
    TramaLoad(char c);
    
    /**
     * @brief Destructor
     */
    ~TramaLoad();
    
    /**
     * @brief Procesa la trama LOAD
     * @param carga Lista donde se almacenará el carácter decodificado
     * @param rotor Rotor que realizará el mapeo del carácter
     * @details Obtiene el carácter mapeado del rotor y lo inserta en la lista de carga
     */
    void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override;
    
    /**
     * @brief Obtiene el dato almacenado
     * @return Carácter de la trama
     */
    char getDato() const;
};

#endif // TRAMALOAD_H
