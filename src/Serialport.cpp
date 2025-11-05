/**
 * @file SerialPort.cpp
 * @brief Implementación de la clase SerialPort
 */

#include "SerialPort.h"
#include <iostream>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <fcntl.h>
    #include <unistd.h>
    #include <termios.h>
    #include <cstring>
#endif

SerialPort::SerialPort(const char* portName, unsigned int baudRate) : conectado(false) {
#ifdef _WIN32
    // Windows implementation
    hSerial = CreateFileA(portName,
                          GENERIC_READ | GENERIC_WRITE,
                          0,
                          NULL,
                          OPEN_EXISTING,
                          FILE_ATTRIBUTE_NORMAL,
                          NULL);
    
    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: No se pudo abrir el puerto " << portName << std::endl;
        return;
    }
    
    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error: No se pudo obtener el estado del puerto" << std::endl;
        CloseHandle(hSerial);
        return;
    }
    
    dcbSerialParams.BaudRate = baudRate;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error: No se pudo configurar el puerto" << std::endl;
        CloseHandle(hSerial);
        return;
    }
    
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    
    if (!SetCommTimeouts(hSerial, &timeouts)) {
        std::cerr << "Error: No se pudo configurar los timeouts" << std::endl;
        CloseHandle(hSerial);
        return;
    }
    
    conectado = true;
    std::cout << "Conexión establecida en " << portName << std::endl;
    
#else
    // Linux implementation
    fd = open(portName, O_RDWR | O_NOCTTY | O_NDELAY);
    
    if (fd == -1) {
        std::cerr << "Error: No se pudo abrir el puerto " << portName << std::endl;
        return;
    }
    
    struct termios options;
    tcgetattr(fd, &options);
    
    // Set baud rate
    speed_t baud;
    switch(baudRate) {
        case 9600: baud = B9600; break;
        case 115200: baud = B115200; break;
        default: baud = B9600; break;
    }
    
    cfsetispeed(&options, baud);
    cfsetospeed(&options, baud);
    
    // 8N1
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    
    // No flow control
    options.c_cflag &= ~CRTSCTS;
    
    // Turn on READ & ignore ctrl lines
    options.c_cflag |= CREAD | CLOCAL;
    
    // Turn off software flow ctrl
    options.c_iflag &= ~(IXON | IXOFF | IXANY);
    
    // Make raw
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_oflag &= ~OPOST;
    
    // Set timeouts
    options.c_cc[VMIN] = 0;
    options.c_cc[VTIME] = 10;
    
    tcsetattr(fd, TCSANOW, &options);
    
    conectado = true;
    std::cout << "Conexión establecida en " << portName << std::endl;
#endif
}

SerialPort::~SerialPort() {
#ifdef _WIN32
    if (conectado) {
        CloseHandle(hSerial);
    }
#else
    if (conectado) {
        close(fd);
    }
#endif
}

int SerialPort::leerLinea(char* buffer, int bufferSize) {
    if (!conectado) return -1;
    
    int pos = 0;
    char c;
    
#ifdef _WIN32
    DWORD bytesRead;
    
    while (pos < bufferSize - 1) {
        if (ReadFile(hSerial, &c, 1, &bytesRead, NULL)) {
            if (bytesRead > 0) {
                if (c == '\n' || c == '\r') {
                    if (pos > 0) break;
                    continue;
                }
                buffer[pos++] = c;
            }
        } else {
            return -1;
        }
    }
#else
    while (pos < bufferSize - 1) {
        int n = read(fd, &c, 1);
        if (n > 0) {
            if (c == '\n' || c == '\r') {
                if (pos > 0) break;
                continue;
            }
            buffer[pos++] = c;
        } else if (n < 0) {
            return -1;
        }
    }
#endif
    
    buffer[pos] = '\0';
    return pos;
}

bool SerialPort::estaConectado() const {
    return conectado;
}

void SerialPort::limpiarBuffer() {
#ifdef _WIN32
    if (conectado) {
        PurgeComm(hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR);
    }
#else
    if (conectado) {
        tcflush(fd, TCIOFLUSH);
    }
#endif
}
