/*
en este ejercicio de hiteresis, se utilizo el sensor de luminosidad si segun su intensidad
encender o apagar un led, para esto se definieron dos umbrales, uno para encender el led y otro para apagarlo, 
de esta manera se evita que el led parpadee constantemente cuando la intensidad de luz se encuentra cerca del umbral. 
El programa lee el valor del sensor de luminosidad, lo convierte a voltaje y luego aplica la lógica de histéresis para controlar el estado del LED. 
Además, se muestra la información en el monitor serial para facilitar la visualización de los datos.
*/

// === DEFINICIÓN DE PINES ===
const int pinPot = A1;     // Entrada analógica señal del sensor de luminosidad
const int pinLED = 13;     // LED

/*
estos umbrales se pueden ajustar según las necesidades específicas del proyecto o las características del sensor utilizado.
tener en cuenta que son los valores de ADC (0-1023) que corresponden a los niveles de luz que se desean para encender o apagar el LED.
*/
// === UMBRALES DE HISTÉRESIS ===
const int UMBRAL_ALTO = 600;  // Encender LED
const int UMBRAL_BAJO = 500;  // Apagar LED

/*
dejando un tiempo de muestra de 200ms para evitar saturar el monitor serial con demasiada información, y para que el cambio de estado del LED sea perceptible.
*/
// === VARIABLES GLOBALES ===
unsigned long tiempoDisplay = 0;
const unsigned long INTERVALO_DISPLAY = 200;

// Estado del LED (memoria de histéresis)
bool estadoLED = false;

// === CONFIGURACIÓN ===
void setup() {
  Serial.begin(9600);
  pinMode(pinLED, OUTPUT);

  Serial.println("==========================================");
  Serial.println(" ADC con Histeresis (Control LED)");
  Serial.println("==========================================");
  Serial.println("t(ms)\traw\tvoltaje\tLED");
  Serial.println("------------------------------------------");
}

// === BUCLE PRINCIPAL ===
void loop() {
  if ((millis() - tiempoDisplay) >= INTERVALO_DISPLAY) {
    tiempoDisplay = millis();

    int rawADC = analogRead(pinPot);
    float voltaje = rawADC * (5.0 / 1023.0);

    /*
    si el LED está apagado y el valor del ADC es mayor o igual al umbral alto, se enciende el LED.
    si el LED está encendido y el valor del ADC es menor o igual al umbral bajo, se apaga el LED.
    */
    // === LÓGICA DE HISTÉRESIS ===
    if (!estadoLED && rawADC >= UMBRAL_ALTO) {
      estadoLED = true;   // Encender
    } 
    else if (estadoLED && rawADC <= UMBRAL_BAJO) {
      estadoLED = false;  // Apagar
    }

    digitalWrite(pinLED, estadoLED);

    // === SALIDA SERIAL ===
    Serial.print(millis());
    Serial.print("\t");
    Serial.print(rawADC);
    Serial.print("\t");
    Serial.print(voltaje, 3);
    Serial.print("\t");

    Serial.println(estadoLED ? "ON" : "OFF");
  }
}
