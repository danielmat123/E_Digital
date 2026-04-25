/*
 * lab-03-parte1-debouncing.ino
 * Laboratorio 3 — Parte 1: Debouncing por Software
 *
 * Demuestra el problema de rebote (bouncing) en botones digitales
 * y su solución mediante debouncing por software con millis().
 *
 * El programa registra dos contadores en paralelo:
 *   - contadorBruto:   detecta TODOS los flancos, incluyendo rebotes
 *   - contadorDebounce: detecta solo pulsaciones reales (ventana 20 ms)
 *
 * La diferencia entre ambos contadores cuantifica el bouncing del botón.
 *
 * Circuito (Fase A — solo software, sin capacitor):
 *   D2  — Botón con resistencia pull-down 10kΩ (HIGH = presionado)
 *   D13 — LED indicador (resistencia 220Ω en serie)
 *
 * Nota: En la Fase B de este laboratorio se agrega un capacitor cerámico
 * 100nF en paralelo con la resistencia pull-down. Esa modificación de
 * hardware se evalúa usando el contador de interrupciones de la Sesión 2.
 *
 * Autor: Ricardo Amézquita Orozco
 * Curso: Electrónica Digital 2016684 — 2026-1
 */

// === DEFINICIÓN DE PINES ===
const int pinBoton = 2;     // Botón con pull-down 10kΩ — HIGH = presionado
const int pinLED   = 13;    // LED indicador de pulsación validada (220Ω en serie)

// === VARIABLES GLOBALES ===

// --- Lectura del botón ---
bool lecturaBruta    = LOW;  // Lectura directa del pin en cada iteración
bool lecturaAnterior = LOW;  // Lectura en la iteración inmediatamente anterior

// --- Debouncing por software ---
// Estado estable: valor aceptado después de que la señal permaneció
// estable durante al menos DEBOUNCE_MS milisegundos.
bool estadoEstable = LOW;

// Timestamp del último cambio detectado en la lectura bruta.
// Se reinicia cada vez que la señal oscila (rebote o cambio real).
unsigned long tiempoUltimoCambio = 0;

// Ventana de debounce: tiempo mínimo que la señal debe permanecer
// estable para considerarla un cambio de estado real.
// Los rebotes mecánicos duran típicamente 1–10 ms; 20 ms es seguro.
const unsigned long DEBOUNCE_MS = 20;

// --- Contadores comparativos ---
// contadorBruto registra cada flanco ascendente sin filtro.
// Con rebotes, una pulsación física puede generar 2–50 flancos.
int contadorBruto    = 0;

// contadorDebounce registra solo flancos ascendentes validados.
// Cada pulsación física real produce exactamente 1 incremento.
int contadorDebounce = 0;

// --- Reporte periódico por Serial ---
unsigned long tiempoDisplay = 0;
const unsigned long INTERVALO_DISPLAY = 500;   // Reporte cada 500 ms

// === CONFIGURACIÓN ===
void setup() {
  Serial.begin(9600);
  Serial.println("============================================");
  Serial.println("  Lab 3 — Parte 1: Debouncing por Software");
  Serial.println("============================================");
  Serial.println();
  Serial.println("Presione el boton varias veces y observe");
  Serial.println("la diferencia entre contadores.");
  Serial.println();
  Serial.println("t(ms)    Bruto    ConDebounce_SW");
  Serial.println("--------------------------------------------");

  // Pull-down externo — no usar INPUT_PULLUP (invierte la lógica)
  pinMode(pinBoton, INPUT);
  pinMode(pinLED, OUTPUT);
  digitalWrite(pinLED, LOW);
}

// === BUCLE PRINCIPAL ===
void loop() {
  lecturaBruta = digitalRead(pinBoton);

  // --- Contador bruto: flanco ascendente sin ningún filtro ---
  // Detecta cada transición LOW→HIGH, incluyendo rebotes.
  if (lecturaBruta == HIGH && lecturaAnterior == LOW) {
    contadorBruto++;
  }

  // --- Debouncing por software: algoritmo millis() + estado estable ---

  // Paso 1: Si la lectura cambia respecto a la anterior, reiniciar temporizador.
  // Esto ocurre tanto en rebotes reales como en el cambio de estado deseado.
  if (lecturaBruta != lecturaAnterior) {
    tiempoUltimoCambio = millis();
  }

  // Paso 2: Si la señal permaneció estable durante DEBOUNCE_MS,
  // comparar con el estado estable anterior para detectar transiciones reales.
  if ((millis() - tiempoUltimoCambio) >= DEBOUNCE_MS) {
    if (lecturaBruta != estadoEstable) {
      estadoEstable = lecturaBruta;

      if (estadoEstable == HIGH) {
        // Flanco ascendente validado: pulsación física real confirmada
        contadorDebounce++;
        digitalWrite(pinLED, HIGH);
      } else {
        // Flanco descendente validado: botón liberado
        digitalWrite(pinLED, LOW);
      }
    }
  }

  // Actualizar lectura anterior para la próxima iteración
  lecturaAnterior = lecturaBruta;

  // --- Reporte periódico por Serial Monitor ---
  if ((millis() - tiempoDisplay) >= INTERVALO_DISPLAY) {
    tiempoDisplay = millis();
    Serial.print(millis());
    Serial.print("\t ");
    Serial.print(contadorBruto);
    Serial.print("\t  ");
    Serial.println(contadorDebounce);
  }
}
