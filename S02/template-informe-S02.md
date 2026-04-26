# Informe de Laboratorio — Sesión 2: Tiempo y Eventos — Mediciones Precisas con Arduino

---

**Universidad Nacional de Colombia**
**Electrónica Digital — 2016684 — 2026-1**
**Prof. Ricardo Amézquita Orozco**

---

| Campo | |
|-------|--|
| **Integrantes** | 1. Andres Felipe Polanco Olaya |
| | 2. Juan Felipe Sanchez Poveda|
| | 3. Daniel Mateo Gonzales Sánchez|
| | 4. Juan Sebastian Baquero Pinzon|
| **Grupo** | 4 |
| **Fecha de la práctica** | Miércoles 11 de Febrero, 2026 |
| **Fecha de entrega** | Miércoles 11 de Marzo, 2026 (Informe Bloque 1) |

---

## 1. Resultados

<!-- CRITERIO DE RÚBRICA: Resultados
     Nivel 2: Resultados completos y organizados
     Nivel 3: Con análisis estadístico o comparativo cuando aplique
     (Sesión de medición: tablas con N≥10, promedio, desv. estándar) -->

### Parte 1: Tiempo de Reacción (Polling)

| Medición | Tiempo millis() [ms] | Tiempo micros() [μs] | Diferencia [μs] |
|----------|----------------------|----------------------|------------------|
| 1 | 194 | 194728 | -728 |
| 2 | 316 | 315668 | 332 |
| 3 | 226 | 225844 | 156 |
| 4 | 182 | 181932 | 68 |
| 5 | 247 | 247312 | -312 |
| 6 | 174 | 174404 | -404 |
| 7 | 179 | 179524 | -524 |
| 8 | 179 | 179748 | -748 |
| 9 | 387 | 387632 | -632 |
| 10 | 202 | 201632 | 368 |
| **Promedio** | 228.6 | 228842.4 | -242.4 |
| **Desv. Est.** | 70.75183547 | 70721.54023 | 459.43 |

### Parte 2: Tiempo de Reacción (Interrupciones) + Bouncing

| Medición | Tiempo de reacción [μs] | contadorISR | Bouncing (sí/no) |
|----------|-------------------------|-------------|-------------------|
| 1 | 270488 | 1 | No |
| 2 | 152500 | 1 | No |
| 3 | 181976 | 1 | No |
| 4 | 165588 | 2 | Sí |
| 5 | 177316 | 2 | Sí |
| 6 | 185736 | 1 | No |
| 7 | 361892 | 1 | No |
| 8 | 186724 | 1 | No |
| 9 | 43820 | 2 | Sí |
| 10 | 279932 | 2 | Sí |
| **Promedio** | 200597.2 | — | — |

### Parte 2: Experimento del Delay

| Valor del delay [ms] | Tiempo de reacción medido [μs] | Observaciones |
|-----------------------|-------------------------------|---------------|
| 10 (original) | 302928 | Tiempo base de referencia |
| 100 | 374272 | Aumento significativo del tiempo |
| 200 | 393792 | Incremento leve respecto a 100 ms |
| 500 | 350088 | Disminución inesperada (no lineal) |

Los resultados indican que, presuponiendo que el valor del delay se incrementa, el tiempo de reacción se hace mayor ante un incremento del delay, supuestamente desde un delay de 10 ms a uno de valor de 100 ms, pero de forma no del todo consistente, ya que entre el valor de 100 ms y 200 ms se aumenta, pero en menor medida desde el de valor de 200 ms hasta el de 500 ms hasta llegar a una reducción cuando se mide con un delay de 500 ms (con valores de tiempo de reacción de 290 ms a una test de 92 ms). Esta observación puede sugerir que el sistema no presenta una relación lineal clara entre el delay y el tiempo de reacción, ya que otros factores deban influir (en el sentido positivo, o que sean responsables de la falta de linealidad; salvo, en su aspecto negativo, el ruido, interferencias/deformaciones por interrupciones, el efecto de rebote que sufre la medición, etc.). En consecuencia, los resultados sugieren que el delay es un parámetro que puede influir, pero no el único con capacidad de afectar el tiempo de reacción y la precisión de la medición. 

### Parte 3: Período del Péndulo (Sensor IR)

**Longitud de cuerda L = 0.4 m**

| Medición | T medido [μs] | T medido [s] |
|----------|---------------|--------------|
| 1 | 126096 | 126 |
| 2 | 122744 | 123 |
| 3 | 127744 | 128 |
| 4 | 125024 | 125 |
| 5 | 128816 | 129 |
| **Promedio** |126084.8 | 126.2|
| **Desv. Est.** | 2121.2|2.13 |

$T_{teórico} = 2\pi\sqrt{L/g}$ = 1.268 s

Error porcentual: 0.62 %

---

## 2. Visualización

<!-- CRITERIO DE RÚBRICA: Visualización
     Nivel 2: Figuras claras, rotuladas y referenciadas en el texto
     Nivel 3: Con interpretación cuantitativa o comparación con teoría -->

### Gráfica 1: Efecto del Delay sobre el Tiempo de Reacción (Interrupciones)

**Eje X:** Valor del delay en `loop()` (ms)
**Eje Y:** Tiempo de reacción medido (μs)

Diagrama de barras o puntos con los datos de la Tabla 3 (delay de 10, 100, 200 y 500 ms). Si el tiempo de reacción no cambia con el delay, eso demuestra que la ISR captura el evento independientemente de lo que haga el programa principal.

![Gráfica 1 — Tiempo de reacción vs delay](imagenes/grafica-1.png)

**Interpretación:** ¿El tiempo de reacción depende del valor del delay? ¿Qué demuestra esto sobre cómo funcionan las interrupciones?

> [Respuesta del estudiante aquí]

### Gráfica 2: T experimental vs T teórico (Péndulo)

Representar el valor medido de T (promedio ± desviación estándar) junto con el valor teórico $T = 2\pi\sqrt{L/g}$ para la longitud utilizada. Puede ser un diagrama de barras o un punto con barra de error y una línea horizontal para el valor teórico.

![Gráfica 2 — T experimental vs teórico](imagenes/grafica-2.png)

### Gráfica 3 (solo si se realizó el Reto 3): T² vs L

*Aplica únicamente si se midió el péndulo con ≥5 longitudes diferentes.*

**Eje X:** Longitud L (m)
**Eje Y:** Período al cuadrado T² (s²)

![Gráfica 3 — T² vs L](imagenes/grafica-3.png)

**Ecuación de ajuste lineal:** T² = _______ · L + _______

**Pendiente experimental:** _______ s²/m

**Pendiente teórica ($4\pi^2/g$):** _______ s²/m

**Valor de $g$ obtenido:** _______ m/s²

---

## 3. Análisis

<!-- CRITERIO DE RÚBRICA: Análisis (preguntas obligatorias)
     Nivel 2: Respuesta correcta respaldada por resultados propios
     Nivel 3: Con insight adicional o comparación cuantitativa -->

**Pregunta 1:** ¿Cuál es la diferencia promedio entre las mediciones de `millis()` y `micros()` en la Tabla 1? ¿Es consistente con la resolución de 1 ms de `millis()`?

> [Respuesta del estudiante aquí]

**Pregunta 2:** ¿Qué porcentaje de las pulsaciones en la Tabla 2 presentaron bouncing (`contadorISR > 1`)? ¿Cuál fue el valor máximo de `contadorISR` observado?

> [Respuesta del estudiante aquí]

**Pregunta 3:** Analiza los resultados de la Tabla 3: ¿el delay afectó el tiempo de reacción reportado? Explica por qué o por qué no, en términos del mecanismo de la ISR.

> [Respuesta del estudiante aquí]

---

## 4. Código Documentado

<!-- CRITERIO DE RÚBRICA: Código documentado
     Nivel 2: Código con comentarios básicos
     Nivel 3: Código limpio, bien comentado, explica la lógica -->

*Pegar el código completo de la Parte 3 con los 3 TODOs resueltos. Comentar cada bloque explicando la lógica implementada.*

### lab-02-parte3-pendulo.ino (TODOs completados)

```cpp
esta esta un tris mejor
eso si tiene problemas cuando un objeto pasa muy lento, pero para el pendulo esta bien
// ============================================================================
// Lab 02 - Parte 3: Medición de Período de Péndulo con Sensor IR
// Curso: Electrónica Digital 2026-1 | Universidad Nacional de Colombia
// Sesión 2: Tiempo y Eventos — Mediciones Precisas con Arduino
// ============================================================================
//
// DESCRIPCIÓN:
// Medición del período de oscilación de un péndulo usando un módulo sensor IR
// de proximidad. Cada vez que el péndulo pasa frente al sensor, se genera
// una interrupción. Con 2 detecciones consecutivas y el sensor centrado
// en la posición de equilibrio, se obtiene medio período: T = 2 × (t₂ - t₁).
//
// CIRCUITO: Diferente a Partes 1-2 — retirar LEDs, conectar sensor IR
// - Pin 2:  Sensor IR OUT (INPUT) — pin INT0
// - 5V:     Sensor IR VCC
// - GND:    Sensor IR GND
//
// NOTA: El módulo sensor IR tiene un comparador con histéresis integrado.
// Su salida es digital limpia — no presenta bouncing como un botón mecánico.
//
// SCAFFOLDING: Solo estructura base — el estudiante escribe la lógica
// ============================================================================

// === DEFINICIÓN DE PINES ===
const int pinSensorIR = 2;    // Salida digital del módulo IR — pin INT0

// === VARIABLES GLOBALES ===
// Todas las variables modificadas dentro de una ISR deben ser 'volatile'.
// 2 detecciones consecutivas = medio período (con sensor centrado en equilibrio).
volatile unsigned int  contadorDetecciones     = 0;      // Cuenta pasos del péndulo
volatile unsigned long tiempoPrimeraDeteccion  = 0;      // Timestamp (micros) de la 1ra detección
volatile unsigned long tiempoSegundaDeteccion  = 0;      // Timestamp (micros) de la 2da detección
volatile bool          medicionLista           = false;   // true cuando se tienen 2 detecciones

// Variables de medición (no-volatile, solo usadas en loop)
int numMedicion = 0;

// === CONFIGURACIÓN ===
void setup() {
  // ---------------------------------------------------------------
  // TODO 1: Configurar pin, Serial, e interrupción
  //
  // Necesitas:
  //   1. Configurar pinSensorIR como INPUT
  //   2. Iniciar Serial a 9600
  //   3. Imprimir encabezado del programa
  //   4. Configurar interrupción en pinSensorIR
  //      - Usar FALLING: el sensor IR pone OUT en LOW cuando detecta objeto
  //      - La función ISR se llama isrSensorIR (definida más abajo)
  //   5. Imprimir encabezado de tabla de datos
  //
  // Escribe el código aquí:
  pinMode(pinSensorIR, INPUT);

  Serial.begin(9600);
  Serial.println("============================================");
  Serial.println("  Lab 02 - Parte 3: Periodo Pendulo");
  Serial.println("  Mismo juego, pero con attachInterrupt()");
  Serial.println("============================================");
  Serial.println();
  attachInterrupt(digitalPinToInterrupt(pinSensorIR), isrSensorIR, FALLING);
  Serial.println("#   T(us)        T(ms)      T(s)");
  Serial.println("--------------------------------------");
  // ---------------------------------------------------------------
}

// === BUCLE PRINCIPAL ===
void loop() {
  // ---------------------------------------------------------------
  // TODO 2: Lógica principal de medición
  //
  // Pseudocódigo:
  //   Si medicionLista es true:
  //     1. Calcular medio período en microsegundos:
  //        medio_T = tiempoSegundaDeteccion - tiempoPrimeraDeteccion
  //     2. Calcular período completo: T = 2 * medio_T
  //        (válido porque el sensor está centrado en el equilibrio)
  //     3. Convertir a segundos: T_seg = T / 1000000.0
  //     4. Incrementar numMedicion
  //     5. Imprimir por Serial: numMedicion, T en us, T en ms, T en s
  //     6. Reiniciar para siguiente medición:
  //        contadorDetecciones = 0
  //        medicionLista = false
  //
  // Formato sugerido de salida:
  //   #  T(us)      T(ms)    T(s)
  //   1  1023456    1023.5   1.024
  //
  // Escribe el código aquí:
  if (medicionLista==true) {

     // aqui la idea es que el sensor unicamente mide el tiempo desde que el pendulo pasa por primera ves y se devuelve, por lo que solo se tiene el tiempo de la mitad del recorrido, por eso T es igual a el tiempo medido por 2, ya despues es unicamente es unicamente imprimir las mediciones
    float medio_T = tiempoSegundaDeteccion - tiempoPrimeraDeteccion;
    float T = 2 * medio_T;
    float T_seg= T/1000000.0;
    float T_ms = T/1000.0;
    numMedicion++;
    // Número de medición
    Serial.print(numMedicion);
    Serial.print("   ");

    // T en microsegundos
    Serial.print(T);
    Serial.print("        ");

    // T en milisegundos (3 decimales)
    Serial.print(T_ms, 3);
    Serial.print("      ");

    // T en segundos (6 decimales)
    Serial.print(T_seg, 6);

    Serial.println();

     // se reincia el contadorDetecciones para el siguiente intervalo
    contadorDetecciones = 0;
    medicionLista = false;
  }

  // ---------------------------------------------------------------
}

// === ISR: Detección del paso del péndulo ===
void isrSensorIR() {
  // ---------------------------------------------------------------
  // TODO 3: Implementar lógica de la ISR (2 detecciones)
  //
  // Pseudocódigo:
  //   contadorDetecciones++
  //   si contadorDetecciones == 1:
  //     guardar micros() en tiempoPrimeraDeteccion
  //   si contadorDetecciones == 2:
  //     guardar micros() en tiempoSegundaDeteccion
  //     medicionLista = true
  //
  // Escribe el código aquí:
  static unsigned long ultimoTiempo = 0;
  unsigned long ahora = micros();

  // Ignorar detecciones muy cercanas, esto con el fin de evitar el bouncing del sensor (por ejemplo < 100 ms)
  // sin embargo esto tiene un problema y es que si un objeto pasa muy lento o es muy grande el programa lo toma como que el intervalo en que el paso por el sensor es el mismo que el tiempo que se demoro en ir y volver, esto se corrige cambiando el valor del siguiente if, pero para un pendulo normal que no va tan lento el programa funciona bien 
  if (ahora - ultimoTiempo < 200000) {
    return;
  }

  ultimoTiempo = ahora;
  // si pasa el filtro unicamente cuenta cuando paso una ves el pendulo y mide el intervalo de tiempo entre la primera y la segunda medicion
  contadorDetecciones++;
  if (contadorDetecciones ==1) {
    tiempoPrimeraDeteccion = ahora;
  }
  if (contadorDetecciones ==2) {
    tiempoSegundaDeteccion = ahora;
    medicionLista = true;
  }
  // ---------------------------------------------------------------
}
```

---

## 5. Dificultades Encontradas y Soluciones Aplicadas

<!-- CRITERIO DE RÚBRICA: Dificultades y soluciones
     Nivel 2: Describe problemas y cómo los resolvieron
     Nivel 3: Análisis de causa raíz + lección aprendida -->

### Dificultad 1: [Descripción breve]

- **Síntoma observado:**
- **Causa identificada:**
- **Solución aplicada:**
- **Lección aprendida:**

### Dificultad 2: [Descripción breve]

- **Síntoma observado:**
- **Causa identificada:**
- **Solución aplicada:**
- **Lección aprendida:**

---

## 6. Pregunta Abierta

<!-- CRITERIO DE RÚBRICA: Pregunta abierta
     Nivel 2: Propuesta viable y justificada
     Nivel 3: Propuesta creativa con análisis cuantitativo -->

**Pregunta:** Propón un experimento de física que podrías automatizar usando interrupciones y un sensor (IR, ultrasonido, u otro). Describe: qué mediría, qué sensor usaría, qué tipo de interrupción (RISING/FALLING/CHANGE), y qué ventaja tendría sobre una medición manual.

> [Respuesta del estudiante aquí]
