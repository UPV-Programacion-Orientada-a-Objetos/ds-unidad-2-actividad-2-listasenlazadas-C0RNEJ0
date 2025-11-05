/**
 * @file TramaMap.h
 * @brief Clase para tramas de tipo MAP (M,N)
 * @author Tu Nombre
 * @date 2025
 */

#ifndef TRAMAMAP_H
#define TRAMAMAP_H

#include "TramaBase.h"

/**
 * @class TramaMap
 * @brief Representa una trama de mapeo que modifica la rotación del rotor
 * 
 * Las tramas MAP contienen un valor de rotación que altera
 * el estado del rotor de mapeo, cambiando cómo se decodifican
 * los caracteres subsecuentes
 */
class TramaMap : public TramaBase {
private:
    int rotacion; ///< Cantidad de posiciones a rotar (puede ser negativa)
    
public:
    /**
     * @brief Constructor de la trama MAP
     * @param n Número de posiciones a rotar el rotor
     */
    TramaMap(int n);
    
    /**
     * @brief Destructor
     */
    ~TramaMap();
    
    /**
     * @brief Procesa la trama MAP
     * @param carga Lista de carga (no utilizada en MAP)
     * @param rotor Rotor que será rotado
     * @details Aplica la rotación especificada al rotor de mapeo
     */
    void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override;
    
    /**
     * @brief Obtiene el valor de rotación
     * @return Cantidad de posiciones a rotar
     */
    int getRotacion() const;
};

#endif // TRAMAMAP_H
