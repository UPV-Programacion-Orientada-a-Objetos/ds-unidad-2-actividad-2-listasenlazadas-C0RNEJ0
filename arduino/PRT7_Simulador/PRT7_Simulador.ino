/**
 * @file PRT7_Simulator.ino
 * @brief Simulador del Protocolo PRT-7 para Arduino
 * @details Envía tramas LOAD y MAP por el puerto serial
 * para ser decodificadas por el sistema C++
 */

void setup() {
  // Inicializar comunicación serial a 9600 baudios
  Serial.begin(9600);
  delay(2000); // Esperar a que se establezca la conexión
  
  Serial.println("INICIO"); // Señal de inicio
}

void loop() {
  // Secuencia de tramas para formar "HELLO WORLD"
  
  // H O L (sin rotación)
  Serial.println("L,H");
  delay(1000);
  
  Serial.println("L,O");
  delay(1000);
  
  Serial.println("L,L");
  delay(1000);
  
  // Rotar +2 posiciones
  Serial.println("M,2");
  delay(1000);
  
  // L -> N (con rotación +2)
  // O -> Q (con rotación +2)
  Serial.println("L,J"); // J + 2 = L
  delay(1000);
  
  Serial.println("L,M"); // M + 2 = O
  delay(1000);
  
  // Espacio
  Serial.println("L, ");
  delay(1000);
  
  // Rotar -2 posiciones (volver a normal)
  Serial.println("M,-2");
  delay(1000);
  
  // W O R L D
  Serial.println("L,W");
  delay(1000);
  
  Serial.println("L,O");
  delay(1000);
  
  Serial.println("L,R");
  delay(1000);
  
  Serial.println("L,L");
  delay(1000);
  
  Serial.println("L,D");
  delay(1000);
  
  Serial.println("FIN"); // Señal de fin
  
  // Detener envío
  while(true) {
    delay(10000);
  }
}
