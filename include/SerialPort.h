/**
 * @file SerialPort.h
 * @brief Clase para comunicación serial multiplataforma
 * @author Tu Nombre
 * @date 2025
 */

#ifndef SERIALPORT_H
#define SERIALPORT_H

#ifdef _WIN32
    #include <windows.h>
#else
    #include <termios.h>
#endif

/**
 * @class SerialPort
 * @brief Maneja la comunicación serial con el Arduino
 * 
 * Proporciona una interfaz multiplataforma para abrir,
 * configurar y leer datos del puerto serial
 */
class SerialPort {
private:
#ifdef _WIN32
    HANDLE hSerial; ///< Handle del puerto serial en Windows
#else
    int fd;         ///< File descriptor del puerto serial en Linux
#endif
    bool conectado; ///< Estado de la conexión
    
public:
    /**
     * @brief Constructor: abre y configura el puerto serial
     * @param portName Nombre del puerto (ej: "COM3" o "/dev/ttyUSB0")
     * @param baudRate Velocidad de comunicación (default: 9600)
     */
    SerialPort(const char* portName, unsigned int baudRate = 9600);
    
    /**
     * @brief Destructor: cierra el puerto serial
     */
    ~SerialPort();
    
    /**
     * @brief Lee una línea del puerto serial
     * @param buffer Buffer donde se almacenará la línea leída
     * @param bufferSize Tamaño máximo del buffer
     * @return Cantidad de bytes leídos, -1 si hay error
     * @details Lee hasta encontrar '\n' o llenar el buffer
     */
    int leerLinea(char* buffer, int bufferSize);
    
    /**
     * @brief Verifica si el puerto está conectado
     * @return true si está conectado, false en caso contrario
     */
    bool estaConectado() const;
    
    /**
     * @brief Limpia los buffers de entrada y salida
     */
    void limpiarBuffer();
};

#endif // SERIALPORT_H
