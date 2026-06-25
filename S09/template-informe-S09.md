# Informe de Laboratorio — Sesión 9: Generación de Señales y Sistema Integrado

---

**Universidad Nacional de Colombia**
**Electrónica Digital — 2016684 — 2026-1**
**Prof. Ricardo Amézquita Orozco**

---

| Campo | |
|-------|--|
| **Integrantes** | 1. Andres Felipe Polanco Olaya |
| | 2. Juan Felipe Sanchez Poveda |
| | 3. Daniel Mateo Gonzales Sánchez |
| | 4. Juan Sebastian Baquero Pinzon |
| | 5. |
| **Grupo** | 4 |
| **Fecha de la práctica** | Miércoles 22 de Abril, 2026 |
| **Fecha de entrega** | Viernes 25 de Abril, 2026 |

---

## 1. Resultados

### 1.1 Reto 1 — Generador de Señales con MCP4725

#### Captura 1: Forma de onda periódica

Se adjunta una captura del osciloscopio con una forma de onda periódica tipo diente de sierra generada con el DAC.

![Captura — Forma de onda periódica](imagenes/reto-1-onda-periodica.png)

#### Capturas 2–4: Tres formas de onda

Se adjuntan las capturas disponibles en `Inputs`: diente de sierra y triangular. No se encontró una captura separada de la señal senoidal en los archivos suministrados.

![Diente de sierra](imagenes/reto-1-diente-sierra.png)

![Triangular](imagenes/reto-1-triangular.png)

![Senoidal con LUT](imagenes/reto-1-senoidal.png)

#### Captura 5: Control de frecuencia

No se encontraron en `Inputs` capturas separadas de frecuencia mínima y máxima; esta evidencia queda pendiente.

![Frecuencia mínima](imagenes/reto-1-freq-min.png)

![Frecuencia máxima](imagenes/reto-1-freq-max.png)

---

### 1.2 Reto 2 — Caracterización I-V de LEDs con FSM

#### Tabla 1 — Datos I-V de muestra

Incluya las primeras 10 filas y las últimas 10 filas de uno de sus archivos CSV.
Las últimas 10 filas deben incluir la fila con el valor máximo de V_DAC (5.00 V).

**Primeras 10 filas:**

| V_DAC (V) | V_A1 (V) | V_LED (V) | I (mA) |
|:---------:|:--------:|:---------:|:------:|
| | | | |
| | | | |
| | | | |
| | | | |
| | | | |
| | | | |
| | | | |
| | | | |
| | | | |
| | | | |

**Últimas 10 filas:**

| V_DAC (V) | V_A1 (V) | V_LED (V) | I (mA) |
|:---------:|:--------:|:---------:|:------:|
| | | | |
| | | | |
| | | | |
| | | | |
| | | | |
| | | | |
| | | | |
| | | | |
| | | | |
| | | | |

#### Captura: Estados de la FSM en el OLED

Se adjunta la evidencia disponible del OLED durante la operación del Reto 2. En la foto se observa el estado `SUBIDA` y el avance del barrido.

![OLED — Estados de la FSM](imagenes/reto-2-oled-fsm.png)

---

## 2. Visualización

### Gráfica 1 — Curva I-V del LED rojo

Graficar todos los datos del barrido completo del LED rojo (≥ 50 filas del CSV).

**Eje X:** V_LED (V)
**Eje Y:** I (mA)

![Curva I-V LED rojo](imagenes/grafica-1-iv-rojo.png)

**Interpretación:**

> Pendiente: en `Inputs` no se encontró el CSV completo del barrido I-V del LED rojo ni la gráfica correspondiente. Cuando se agregue el archivo, se debe identificar el punto donde la corriente empieza a crecer rápidamente y estimar el voltaje umbral.

---

### Gráfica 2 — Comparación I-V: LED rojo vs LED verde

Superponer las curvas I-V del LED rojo y del LED verde en un mismo gráfico.

**Eje X:** V_LED (V)
**Eje Y:** I (mA)

![Comparación I-V rojo vs verde](imagenes/grafica-2-iv-comparacion.png)

**Interpretación:**

> Pendiente: falta el CSV o la gráfica comparativa del LED rojo y verde. Con esos datos se deben estimar los umbrales de cada color y explicar que el LED verde requiere mayor voltaje por su mayor energía de fotón y bandgap.

---

## 3. Análisis

**Pregunta 1 (Reto 1):** Deduzca la fórmula que relaciona la frecuencia de la señal
senoidal con el número de puntos N de la LUT y el tiempo entre puntos controlado
por el potenciómetro. Con N = 64, ¿cuál es el tiempo entre puntos necesario para
obtener 1 Hz? ¿Y para 15 Hz?

> Para una LUT de N puntos, una vuelta completa de la señal tarda `T = N * Δt`, donde `Δt` es el tiempo entre puntos. Por tanto, `f = 1 / (N * Δt)` y `Δt = 1 / (N*f)`. Con N=64, para 1 Hz se necesita `Δt = 1/(64*1) = 0.015625 s = 15.625 ms`. Para 15 Hz se necesita `Δt = 1/(64*15) = 0.0010417 s = 1.04 ms`.

---

**Pregunta 2 (Reto 2):** ¿Por qué la corriente no crece linealmente con el voltaje
en el LED? Relacione la forma de la curva I-V con el modelo físico de una unión p-n.

> La corriente del LED no crece linealmente porque una unión p-n sigue una relación exponencial entre corriente y voltaje. Por debajo del voltaje umbral, la corriente es muy pequeña; al superar la barrera de potencial, pequeños aumentos de voltaje producen incrementos grandes de corriente. Por eso la curva I-V del LED tiene una región casi plana y luego una subida pronunciada.

---

**Pregunta 3:** Compare los dos métodos de generación de ondas periódicas que usó
en el Reto 1: barrido lineal (diente de sierra y triangular) versus Lookup Table
precalculada (senoidal). ¿En qué situaciones es preferible una LUT sobre un cálculo
en tiempo real, y viceversa? Fundamente con base en la precisión temporal, el uso
de memoria y la flexibilidad de cambiar parámetros.

> El barrido lineal es simple para diente de sierra y triangular porque basta incrementar o decrementar el valor del DAC en pasos regulares. La LUT es preferible para señales como la senoidal, donde calcular `sin()` en tiempo real puede ser costoso y producir jitter temporal. La LUT usa más memoria, pero mejora la regularidad del tiempo entre puntos. El cálculo en tiempo real es más flexible si se quieren cambiar forma, amplitud o parámetros sin almacenar tablas.

---

**Pregunta 4:** En el Reto 2, la transición SUBIDA → FIN es automática (DAC == 4095),
mientras que ESPERA → SUBIDA y FIN → ESPERA dependen del botón. ¿Qué propiedad de
la FSM demuestra esta diferencia en los tipos de transición? ¿Cómo se modificaría
el diseño si todas las transiciones dependieran del botón — qué funcionalidad se perdería?

> La FSM demuestra que pueden coexistir transiciones por evento externo y transiciones automáticas por condición interna. `ESPERA -> SUBIDA` depende del botón, pero `SUBIDA -> FIN` ocurre cuando el barrido llega a `DAC == 4095`. Si todas las transiciones dependieran del botón, se perdería la automatización del barrido y el usuario tendría que detener manualmente la medición, aumentando errores y haciendo menos reproducible la curva I-V.

---

## 4. Código Documentado

Incluya SOLO el código que usted modificó o escribió. No incluya el código base
original ni el I2C Scanner. Comente cada bloque funcional.

### Reto 1 — Generador de Señales (lab-09-generacion-senales.ino)

```cpp
// Pendiente: no se encontro en Inputs el sketch final del generador.
// Debe agregarse aqui el codigo de Reto 1 con:
// - implementacion de diente de sierra, triangular y senoidal por LUT,
// - seleccion de modo por FSM,
// - lectura del potenciometro para controlar la frecuencia.
```

### Reto 2 — Caracterización I-V con FSM (lab-09-iv-led.ino)

```cpp
// Pendiente: no se encontro en Inputs el sketch final del Reto 2.
// Debe agregarse aqui el codigo de la FSM con estados ESPERA, SUBIDA y COMPLETADO,
// el calculo de V_DAC, V_A1, V_LED e I, y la salida CSV del barrido.
```

---

## 5. Dificultades Encontradas y Soluciones Aplicadas

### Dificultad 1

- **Síntoma observado:** No se cuenta aún con todos los archivos de evidencia del Reto 1.
- **Causa identificada:** En `Inputs` solo aparecen capturas de diente de sierra y triangular, pero no la senoidal ni las frecuencias extremas.
- **Solución aplicada:** Se añadieron las capturas disponibles y se dejó indicado qué evidencia falta.
- **Lección aprendida:** Conviene nombrar las capturas por reto y condición experimental al momento de tomarlas.

### Dificultad 2

- **Síntoma observado:** No fue posible construir las curvas I-V.
- **Causa identificada:** No se encontró el CSV del barrido de LEDs rojo/verde.
- **Solución aplicada:** Se dejó pendiente explícito en las secciones de tabla y visualización.
- **Lección aprendida:** Para análisis de curvas, el CSV crudo es tan importante como la foto del montaje.

---

## 6. Pregunta Abierta

**Pregunta:** Proponga una extensión del sistema integrado (Reto 1 + Reto 2) que
utilice simultáneamente las capacidades de generación de señales y de caracterización
I-V. Por ejemplo: usar el generador para excitar un LED con una señal triangular y
medir la respuesta I-V resultante sin necesidad de un barrido por software paso a
paso. Describa qué modificaciones requerirían el hardware y el código, y qué ventaja
ofrecería este enfoque frente a la implementación actual.

> Una extensión sería usar una señal triangular del DAC como excitación continua para el LED y medir simultáneamente el voltaje en la resistencia de sensado con el ADC. En hardware se mantendría una resistencia en serie para calcular corriente y se conectaría el nodo del LED a una entrada analógica. En código, el generador actualizaría el DAC y, en cada punto, registraría `V_DAC`, `V_A1`, `V_LED` e `I`. La ventaja es obtener una curva I-V más rápida y continua, sin depender de un barrido paso a paso controlado por estados largos.
