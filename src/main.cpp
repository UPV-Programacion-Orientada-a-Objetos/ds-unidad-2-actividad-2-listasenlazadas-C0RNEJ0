/**
 * 
 * Este programa lee tramas del protocolo PRT-7 desde un puerto serial
 * y decodifica el mensaje oculto utilizando estructuras de datos
 * implementadas manualmente (listas doblemente enlazadas y circulares)
 */

#include <iostream>
#include <cstring>
#include <cstdlib>
#include "SerialPort.h"
#include "TramaBase.h"
#include "TramaLoad.h"
#include "TramaMap.h"
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"

/**
 * @brief Parsea una línea del puerto serial y crea la trama correspondiente
 * @param linea Cadena recibida del puerto serial (ej: "L,A" o "M,5")
 * @return Puntero a TramaBase (TramaLoad o TramaMap) o nullptr si hay error
 */
TramaBase* parsearTrama(const char* linea) {
    if (!linea || linea[0] == '\0') return nullptr;
    
    // Crear una copia de la línea para procesarla
    char buffer[256];
    int i = 0;
    while (linea[i] != '\0' && i < 255) {
        buffer[i] = linea[i];
        i++;
    }
    buffer[i] = '\0';
    
    // Buscar la coma
    char* coma = nullptr;
    for (int j = 0; buffer[j] != '\0'; j++) {
        if (buffer[j] == ',') {
            coma = &buffer[j];
            break;
        }
    }
    
    if (!coma) return nullptr;
    
    // Separar tipo y dato
    *coma = '\0';
    char tipo = buffer[0];
    char* dato = coma + 1;
    
    if (tipo == 'L') {
        // Trama LOAD
        return new TramaLoad(dato[0]);
    } else if (tipo == 'M') {
        // Trama MAP - convertir string a int
        int rotacion = atoi(dato);
        return new TramaMap(rotacion);
    }
    
    return nullptr;
}

/**
 * @brief Función principal
 */
int main() {
    std::cout << "============================================" << std::endl;
    std::cout << "   Decodificador de Protocolo PRT-7" << std::endl;
    std::cout << "============================================" << std::endl;
    std::cout << std::endl;
    
    // Configuración del puerto serial
    const char* puerto;
    
#ifdef _WIN32
    puerto = "COM3";  // Cambiar segun el sistemas
    std::cout << "Sistema: Windows" << std::endl;
#else
    puerto = "/dev/ttyUSB0";  // o /dev/ttyACM0 para Arduino
    std::cout << "Sistema: Linux/Unix" << std::endl;
#endif
    
    std::cout << "Intentando conectar al puerto: " << puerto << std::endl;
    std::cout << std::endl;
    
    // Crear puerto serial
    SerialPort serial(puerto, 9600);
    
    if (!serial.estaConectado()) {
        std::cerr << "ERROR: No se pudo establecer la conexión." << std::endl;
        std::cerr << "Verifica que:" << std::endl;
        std::cerr << "  1. El Arduino esté conectado" << std::endl;
        std::cerr << "  2. El puerto sea el correcto" << std::endl;
        std::cerr << "  3. No haya otro programa usando el puerto" << std::endl;
        return 1;
    }
    
    // Inicializar estructuras de datos
    ListaDeCarga miListaDeCarga;
    RotorDeMapeo miRotorDeMapeo;
    
    std::cout << "Esperando tramas del protocolo PRT-7..." << std::endl;
    std::cout << "============================================" << std::endl;
    std::cout << std::endl;
    
    // Buffer para leer líneas
    char buffer[256];
    bool procesamientoIniciado = false;
    bool procesamientoTerminado = false;
    
    // Bucle principal de lectura
    while (!procesamientoTerminado) {
        int bytesLeidos = serial.leerLinea(buffer, sizeof(buffer));
        
        if (bytesLeidos > 0) {
            // Verificar señales de control
            if (strcmp(buffer, "INICIO") == 0) {
                procesamientoIniciado = true;
                std::cout << ">>> Señal de INICIO recibida <<<" << std::endl;
                std::cout << std::endl;
                continue;
            }
            
            if (strcmp(buffer, "FIN") == 0) {
                procesamientoTerminado = true;
                std::cout << std::endl;
                std::cout << ">>> Señal de FIN recibida <<<" << std::endl;
                continue;
            }
            
            if (!procesamientoIniciado) continue;
            
            // Parsear y procesar la trama
            TramaBase* trama = parsearTrama(buffer);
            
            if (trama) {
                // Procesar la trama (polimorfismo en acción)
                trama->procesar(&miListaDeCarga, &miRotorDeMapeo);
                
                // Liberar memoria de la trama
                delete trama;
            } else {
                std::cout << "Advertencia: Trama mal formada ignorada: [" << buffer << "]" << std::endl;
            }
        }
    }
    
    // Mostrar resultado final
    std::cout << std::endl;
    std::cout << "============================================" << std::endl;
    std::cout << "   DECODIFICACIÓN COMPLETADA" << std::endl;
    std::cout << "============================================" << std::endl;
    std::cout << std::endl;
    std::cout << "Mensaje oculto ensamblado: ";
    miListaDeCarga.imprimirMensaje();
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Total de caracteres: " << miListaDeCarga.getTamano() << std::endl;
    std::cout << std::endl;
    std::cout << "Liberando memoria... Sistema apagado." << std::endl;
    
    return 0;
}
