// === DEFINICIÓN DE PINES ===
/*
Se toma el pin A1 para conectar el potenciometro, 
aunque también se puede usar A0, A2, A3, A4 o A5. 
El código es el mismo, solo cambia la constante pinLDR.
*/
const int pinLDR = A2;   // Cursor del potenciómetro — rango 0 a 5 V

// === VARIABLES GLOBALES ===
/*
para controlar la frecuencia de muestreo y evitar saturar el Serial Monitor.
el tiempoDisplay se actualiza cada vez que se muestra un nuevo valor, y el intervalo
se establece en 200 ms para una frecuencia de muestreo de 5 Hz (5 muestras por segundo).

*/
unsigned long tiempoDisplay = 0;
const unsigned long INTERVALO_DISPLAY = 200;   // Muestreo cada 200 ms (5 Hz)

// === CONFIGURACIÓN ===
void setup() {
  Serial.begin(9600);
  Serial.println("==========================================");
  Serial.println("  Lab 3 — Parte 4: Sensor de Temperatura LM35 — Lectura Directa");
  Serial.println("==========================================");
  Serial.println();
  Serial.println("Gire el potenciometro y observe el cambio");
  Serial.println("en los valores brutos y de voltaje.");
  Serial.println();
  // Encabezado tabular para Serial Monitor (columnas separadas por tabulación)
  Serial.println("t(ms)\traw(0-1023)\tvoltaje(V)");
  Serial.println("------------------------------------------");

}

// === BUCLE PRINCIPAL ===
/*
si INTERVALO_DISPLAY es 200 ms, el programa leerá el valor del ADC
 y actualizará el Serial Monitor cada 200 ms, lo que corresponde a 
 una frecuencia de muestreo de 5 Hz. Esto permite observar los cambios 
 en el valor del potenciómetro sin saturar la salida serial con demasiados datos. 
*/
void loop() {
  if ((millis() - tiempoDisplay) >= INTERVALO_DISPLAY) {
    tiempoDisplay = millis();

    // Lectura bruta del ADC: número entero 0–1023 proporcional al voltaje
    // 0 corresponde a 0 V (GND), 1023 corresponde a 5.00 V (VCC)
    int rawADC = analogRead(pinLDR);

    // Conversión a voltaje físico
    // Nota: se usa 1023.0 (no 1024.0) porque el ADC produce 1024 niveles
    // de 0 a 1023, y el nivel 1023 corresponde exactamente a V_ref = 5.00 V
    float voltaje = rawADC * (500.0 / 1023.0);

    Serial.print(millis());
    Serial.print("\t");
    Serial.print(rawADC);
    Serial.print("\t\t");
    Serial.println(voltaje, 3);   // 3 decimales: resolución visual ~1 mV
  }
}
