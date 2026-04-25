
// === DEFINICIÓN DE PINES ===

const int pinPotA3 = A3;   // Canal A3 Amplificado con LM324
const int pinA2    = A2;   // Canal A2 sin amplificar, rango 0–5 V

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
  Serial.println("  Lab 3 — Parte 4: ADC Multiples Entradas");
  Serial.println("==========================================");
  Serial.println();
  Serial.println("Lectura simultanea de A3 y A2.");
  Serial.println();

  // Encabezado
  /*
  se deja en V dado que se conoce que el sensor una ves realizada la conversion
  a voltaje, este tiene unidades de °C, pero se muestra como V para enfatizar que el valor mostrado es el resultado 
  de la conversión del ADC a voltaje. 
   Esto es útil para entender que el valor de temperatura se deriva de la 
   lectura del ADC y su correspondiente voltaje, aunque en este caso específico,
    el voltaje ya representa la temperatura debido a la configuración del 
    circuito con el LM324.
  */
  Serial.println("t(ms)\tA3_raw\tA3_V\t\tA2_raw\tA2_V");
  Serial.println("----------------------------------------------------------");
}

// === BUCLE PRINCIPAL ===
void loop() {
  if ((millis() - tiempoDisplay) >= INTERVALO_DISPLAY) {
    tiempoDisplay = millis();

    /*
    dado que la lectura del ADC es un número entero entre 0 y 1023, 
    se convierte a voltaje físico, el pin A2 tiene un voltaje máximo de 5 V, 
    mientras que el pin A3 tiene un voltaje máximo de 100 V debido al 
    amplificador LM324.
     Por lo tanto, para convertir la lectura bruta del ADC a voltaje, 
     se multiplica por el factor de escala correspondiente: 500.0/1023.0 para A2
      y 100.0/1023.0 para A3.
    */

    // === Lectura A3 ===
    int rawA3 = analogRead(pinPotA3);
    float voltajeA3 = rawA3 * (100.0 / 1023.0);

    // === Lectura A2 ===
    int rawA2 = analogRead(pinA2);
    float voltajeA2 = rawA2 * (500.0 / 1023.0);

    // === Salida Serial ===
    Serial.print(millis());
    Serial.print("\t");

    Serial.print(rawA3);
    Serial.print("\t");
    Serial.print(voltajeA3, 3);
    Serial.print("\t\t");

    Serial.print(rawA2);
    Serial.print("\t");
    Serial.println(voltajeA2, 3);
  }
}