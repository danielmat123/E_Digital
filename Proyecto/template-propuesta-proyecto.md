# Propuesta de Proyecto Final — Electrónica Digital 2026-1

**Grupo #:** ___  
**Integrantes:**  
1. Daniel Mateo González Sánchez  
2. ___  
3. ___  
4. ___  

**Fecha de entrega:** ___

---

> ⚠️ **Regla de oro:** Cada integrante debe poder explicar y defender cada decisión de diseño y cada línea de código. En cada entregable y en la presentación final se hará una pregunta aleatoria a cualquier miembro del grupo.

---

## 1. Descripción del Proyecto

El proyecto consiste en un sistema de levitación magnética activa controlado con Arduino. El dispositivo consistirá en una base con bobinas electromagnéticas, sensores de posición y un microcontrolador que permitirá mantener suspendido un pequeño imán de neodimio sin contacto físico directo. Eeste sistema medirá constantemente la posición del imán y ajustará la corriente de las bobinas para estabilizarlo.

El dispositivo sirve como una plataforma experimental y didáctica para estudiar electromagnetismo, sensores, control automático y estabilidad dinámica. La necesidad que satisface es poder observar de manera concreta cómo un sistema físico inestable puede estabilizarse mediante medición, realimentación y actuación electrónica. En otras palabras, permite convertir conceptos abstractos como campo magnético, fuerza electromagnética, sensores Hall y control PID en un experimento visible e interactivo.

Este sistema podría ser usado por estudiantes y docentes de física, ingeniería, electrónica o áreas afines. En un laboratorio o clase, permitiría demostrar cómo un microcontrolador puede recibir información del entorno, procesarla y actuar sobre un sistema físico real. También serviría como prototipo para experimentar con algoritmos de control, calibración de sensores, respuesta ante perturbaciones y movimiento controlado en un eje.

El dispositivo recibirá varias entradas. La primera será la lectura de sensores: un sensor de distancia medirá la altura del imán y sensores Hall detectarán desviaciones laterales del campo magnético. También recibirá entradas del usuario, como encender el sistema, seleccionar una altura objetivo o modificar parámetros básicos del control. A partir de esas entradas, el Arduino calculará la corrección necesaria.

Las salidas principales serán señales PWM enviadas a los MOSFETs que controlan la corriente en las bobinas. Esas señales producirán campos magnéticos variables, los cuales generarán movimiento o estabilización del imán. Además, el sistema podrá mostrar datos en el monitor serial: altura medida, error respecto al punto objetivo, intensidad relativa de las bobinas y estado del sistema, por ejemplo “calibrando”, “levitando”, “corrigiendo” o “inestable”.

Una sesión típica de uso sería la siguiente. Primero, el usuario conecta la fuente de alimentación y enciende el Arduino. El sistema inicia una fase de calibración: mide los sensores sin el imán o con el imán en una posición inicial conocida, y establece valores de referencia.

Después, el usuario activa el modo de levitación. Las bobinas internas comienzan a generar un campo magnético controlado y el Arduino ajusta la corriente para llevar el imán hacia una altura objetivo. En el monitor serial o pantalla, el usuario observa la altura medida y el error respecto al setpoint. Cuando el imán alcanza una posición estable, el sistema mantiene la levitación haciendo pequeñas correcciones continuas.

Si el imán se desplaza un poco hacia un lado, los sensores Hall detectan el cambio y el Arduino activa las bobinas laterales necesarias para devolverlo al centro. Visualmente, el usuario verá el imán suspendido con pequeñas oscilaciones mientras el sistema lo corrige. También podría cambiar la altura objetivo para observar cómo el imán sube o baja suavemente. Al finalizar, el usuario desactiva la levitación, reduce la corriente de las bobinas y retira el imán de forma segura.

En síntesis, vamos a construir un prototipo interactivo de control electromagnético que permite levitar, estabilizar y desplazar de forma limitada un imán mediante sensores, bobinas y Arduino. Su propósito principal es demostrar cómo un sistema inestable puede controlarse en tiempo real usando realimentación electrónica.
---

## 2. Solución Propuesta — Diagrama de Bloques

**¿Cómo resuelven el problema con el toolkit del curso?**

Dibujen un diagrama de bloques del sistema completo. Cada bloque debe ser un subsistema identificable con su función específica.

La arquitectura depende del tipo de proyecto. Algunos ejemplos:

**Tipo A — Instrumento de medición / automatización:**
```
┌──────────┐    ┌──────────┐    ┌──────────┐
│ SENSORES │ →  │ ARDUINO  │ →  │ACTUADORES│
└──────────┘    └──────────┘    └──────────┘
                      │
               ┌──────┴──────┐
               │  DISPLAY /  │
               │  PC / LOG   │
               └─────────────┘
```

**Tipo B — Dispositivo interactivo (instrumento musical, juego, controlador):**
```
┌──────────┐    ┌──────────┐    ┌──────────┐
│ ENTRADAS │ →  │ ARDUINO  │ →  │  SALIDAS │
│(botones, │    │(FSM,     │    │(sonido,  │
│ potenció-│    │ lógica)  │    │ LEDs,    │
│ metros)  │    │          │    │ display) │
└──────────┘    └──────────┘    └──────────┘
```

*Elijan la arquitectura que corresponda a su proyecto o dibujen una propia. Identifiquen cada bloque con su función específica. Si su proyecto usa comunicación serial con Python (S4), agreguen el bloque PC/LOG.*

---

## 3. Matriz de Trazabilidad — Toolkit del Curso

**¿Qué habilidades de S1-S9 usa cada subsistema de su proyecto?**

Marquen con ✅ y describan cómo aplican cada habilidad. Si un subsistema no usa cierta habilidad, déjenlo en blanco.

## Subsistemas definidos

| Subsistema | Nombre | Descripción |
|---|---|---|
| Subsistema 1 | Sensado y entradas | Lectura del sensor de distancia, sensores Hall, botón de encendido/parada, setpoint y comandos del usuario. |
| Subsistema 2 | Control y procesamiento | Calibración, filtrado, cálculo de error, control PID vertical, corrección lateral, lógica de seguridad y máquina de estados. |
| Subsistema 3 | Actuación y visualización | Generación de PWM para MOSFETs y bobinas, visualización en OLED, monitor serial y apagado seguro. |

---

## Matriz de trazabilidad

| Habilidad del curso | Subsistema 1: Sensado y entradas | Subsistema 2: Control y procesamiento | Subsistema 3: Actuación y visualización |
|---|---|---|---|
| **S1 — E/S digital, protoboard** |  | ✅ Lógica condicional para cambiar entre estados como apagado, calibrando, levitando o inestable. | ✅ LED de diagnóstico o indicador de estado; montaje inicial de pruebas en protoboard. |
| **S2 — Timing preciso, interrupciones** | ✅ Lectura temporizada de sensores; posible interrupción para botón o evento crítico. | ✅ Lazo de control ejecutado con periodo fijo usando `millis()` o `micros()`, evitando `delay()`. | ✅ Actualización periódica de PWM, Pca9685 y Serial sin bloquear el control. |
| **S3 — Debouncing, ADC, sensores analógicos** | ✅ Lectura ADC del sensor de distancia y sensores Hall; debouncing del botón de usuario. | ✅ Conversión de lecturas crudas a altura, desviación lateral y valores calibrados. |  |
| **S4 — Comunicación UART + Python** | ✅ Entrada de comandos por Serial: iniciar, detener, calibrar o cambiar setpoint. | ✅ Parser serial no bloqueante para modificar parámetros sin detener el lazo de control. | ✅ Envío de telemetría: altura, error, PWM, estado del sistema y datos para registro en Python. |
| **S5 — PWM, H-Bridge, actuadores** |  | ✅ Cálculo de señales de mando a partir del error vertical y lateral. | ✅ Señales PWM enviadas a MOSFETs para regular la corriente en las bobinas internas y externas. |
| **S6 — Adquisición multicanal, OLED I2C** | ✅ Lectura multicanal: distancia, sensores Hall y entradas del usuario. | ✅ Organización de datos por canales, calibración y procesamiento por tiempos separados. |  |
| **S7 — Control PID** | ✅ Los sensores entregan las variables medidas: altura y desviación lateral. | ✅ PID para altura y PID para corrección lateral. | ✅ La salida del controlador se convierte en PWM para cada grupo de bobinas. |
| **S8 — Filtrado digital, oversampling, triggers** | ✅ Reducción de ruido en sensores de distancia y Hall mediante media móvil, IIR u oversampling. | ✅ Señales filtradas antes del PID para evitar correcciones debidas al ruido. | ✅ Triggers de seguridad: si el error supera un umbral, se apagan las bobinas. |
| **S9 — DAC MCP4725, FSM, generación de señales** | ✅ Setpoint variable como señal de referencia; comandos cambian el modo del sistema. | ✅ Máquina de estados finita: `OFF`, `CALIBRATING`, `READY`, `LEVITATING`, `UNSTABLE`, `FAULT`. | |



> Si el proyecto completo usa menos de 4 habilidades distintas del curso, probablemente es demasiado simple. Pero no inflen la matriz: solo marquen las habilidades que REALMENTE usan.

---

## 4. Diseño Técnico

### 4.1 Diagrama Esquemático

Dibujen el esquemático completo mostrando:
- Todos los pines de Arduino utilizados
- Conexiones de sensores, actuadores, display, DAC
- Resistencias, capacitores y componentes de protección
- Alimentación (5V, 12V, GND)

*Pueden dibujarlo a mano (foto) o usar Fritzing/Tinkercad.*

### 4.2 Tabla de Pines

| Pin Arduino | Conectado a | Función |
|---|---|---|
| D2 | Botón 1 (INPUT_PULLUP, LOW al presionar) | Cambio de modo |
| ... | ... | ... |

### 4.3 Arquitectura de Software

Describan la máquina de estados (FSM) de su sistema. La FSM es la implementación concreta de S9 que ya identificaron en la matriz de trazabilidad (Sección 3). Aquí la detallan con diagrama y pseudocódigo:

```
┌─────────┐   botón   ┌─────────┐
│ ESPERA  │ ────────→ │ MIDIENDO │
└─────────┘           └─────────┘
                           │
                     timeout │
                           ↓
                      ┌─────────┐
                      │ MUESTRA │
                      └─────────┘
```

Incluyan pseudocódigo de la FSM principal y las funciones clave:

```cpp
// Pseudocódigo — FSM principal
enum Estado {ESPERA, MIDIENDO, MUESTRA, CALIBRANDO};
Estado estado = ESPERA;

void loop() {
  switch(estado) {
    case ESPERA:
      // Esperar trigger del sensor
      // Transición → MIDIENDO
      break;
    case MIDIENDO:
      // Adquirir datos de sensores
      // Si completado → MUESTRA
      break;
    case MUESTRA:
      // Mostrar en OLED + enviar CSV
      // Si botón presionado → ESPERA
      break;
  }
}
```

> ⚠️ Este pseudocódigo es solo la estructura. En el código real deben usar `millis()` o interrupciones para el timing (S2). **Nada de `delay()` en una FSM.**

---

## 5. Lista de Materiales

| Componente | Cant. | Costo unit. | Costo total | Proveedor | Disponible? | Plan B si no se consigue |
|---|---|---|---|---|---|---|
| Arduino Uno | 1 | Ya tienen | $0 | Kit | ✅ | — |
| Pca9685 | 1 | 30.000 | 30.000 | Mercadolibre | ✅ | |
| Led | 4 | 200 | 800 | Tienda 30 |✅ | |
| Allegro A1324 | 5 | | 8.000 | Mercadolibre |✅| |
| MOSFET IRLZ44N | 8 | 6.000 | 48.000 | Mercadolibre |✅ | |
| Diodo 1N5408 | 10 | | 6.000 | Mercadolibre |✅ | |
| Alambre de cobre calibre 22 | 80 m | | 88.000 | Mercadolibre|✅| |
| Iman de neodimio, pequeño | 1 | | 1.000 | Ferreteria |✅ | |

**Costo total estimado:** $190.000

> ⚠️ **Crítico:** Si un componente es indispensable y no se consigue, el proyecto está en riesgo. Definan un Plan B para cada componente crítico.

---

## 6. Cronograma — Entregables

*7 semanas de ejecución. La Semana 1 empieza el mismo día en que se aprueba la propuesta. Tres entregables obligatorios. Cada uno debe ser una demo funcionando, no un documento.*

| Entregable | Semana | ¿Qué se demuestra? | Pre-requisitos | Definición de "terminado" |
|:---:|:---:|---|---|---|
| **Entregable 1** | Semana 2 | ___ | ___ | ___ |
| **Entregable 2** | Semana 5 | ___ | ___ | ___ |
| **Entregable 3 (Final)** | Semana 7 | Sistema completo funcionando + defensa | ___ | ___ |

**Para cada entregable, definan:**
- ¿Qué subsistemas estarán funcionando?
- ¿Qué evidencia van a mostrar? (demo en vivo, datos, gráficas)
- **Pre-requisitos:** ¿Qué debe estar listo ANTES de empezar este entregable?
- **Definición de "terminado":** ¿Cómo se sabe, sin ambigüedad, que este entregable está completo?
- ¿Qué riesgos podrían retrasar este entregable y cómo los mitigan?

> Si un entregable se retrasa, ¿afecta a los demás? Si el Entregable 1 depende de un componente que no llegó, ¿hay Plan B?

> 🔄 **Cambio de rumbo:** Si después del Entregable 1 descubren que el proyecto no es viable, pueden proponer un ajuste del alcance o un pivoteo justificado — pero DEBEN discutirlo con el profesor ANTES del Entregable 2. No se aceptan cambios de proyecto en la última semana.

---

## 7. Producto Mínimo Viable (MVP)

> 💀 **Si TODO sale mal** — no llega un componente, se enferma un integrante, se daña algo...

**¿Cuál es la demostración MÁS PEQUEÑA que prueba que aprendieron?**

*Ejemplo: "Aunque no funcione el control PID completo, al menos mostraremos el sensor midiendo temperatura con logging CSV y visualización en OLED."*

**Nuestro MVP es:**

___

**Prueba de aceptación del MVP:** ¿Qué evidencia concreta demostraría que el MVP está completo?

*Ejemplo: "El sensor LM35 muestra temperatura en el OLED con actualización cada 500 ms, y el script Python guarda un CSV con al menos 100 filas de datos correctos."*

___

---

## 8. Métrica de Éxito

**¿Cómo se sabe, sin ambigüedad, que el proyecto funciona?**

Definan al menos UNA métrica cuantitativa y falsable:

*Ejemplo malo:* ❌ "El sistema mide temperatura."  
*Ejemplo bueno:* ✅ "El sistema mide temperatura con error < ±1°C respecto a un termómetro de referencia, para temperaturas entre 20°C y 60°C."

**Nuestra métrica de éxito:**

___

---

## 9. Plan de Validación

**¿Cómo van a probar que su dispositivo funciona correctamente?**

- ¿Contra qué referencia validan? (valor teórico, otro instrumento, prueba con usuarios, comparación A/B)
- Si es un instrumento de medición: ¿cuántas mediciones van a tomar? (mínimo N ≥ 10)
- Si es un dispositivo interactivo: ¿cómo prueban que la experiencia funciona?
- ¿Qué análisis van a hacer? (promedio, desviación estándar, error relativo, tasa de aciertos, etc.)

---

## 10. Bitácora de Diseño

> 📓 **Obligatorio para presentar en cada entregable (no tiene nota, pero sin bitácora no hay presentación).**

La bitácora es un diario de ingeniería en Markdown que registra:

- Qué hicieron en cada sesión de trabajo
- Qué funcionó y qué falló
- Decisiones de diseño y su justificación
- Cambios respecto al plan original (y por qué)

**Formato sugerido:**

```markdown
# Bitácora — Proyecto [Nombre]

## Semana 1 — [Fecha]

**Qué hicimos:**
- Conectamos el LM35 al pin A0
- Probamos lectura básica con analogRead()

**Qué falló:**
- El sensor marcaba 10°C de más — descubrimos que era ruido de la fuente

**Qué decidimos:**
- Agregar filtro de media móvil (S8)
- Usar fuente externa en vez de USB para reducir ruido

**Plan próxima sesión:**
- Implementar filtro y verificar precisión con termómetro de referencia
```

---

## Checklist de Verificación (antes de entregar)

- [ ] ¿Cada integrante puede explicar el proyecto completo?
- [ ] ¿El diagrama de bloques muestra todos los subsistemas?
- [ ] ¿El proyecto usa al menos 4 habilidades distintas de S1-S9?
- [ ] ¿La lista de materiales incluye costo, proveedor, disponibilidad y Plan B?
- [ ] ¿El cronograma define los 3 entregables (semanas 2, 5, 7) con demos claras?
- [ ] ¿El MVP está definido? (si todo falla, ¿qué muestran?)
- [ ] ¿La métrica de éxito es cuantitativa y falsable?
- [ ] ¿El plan de validación especifica referencia y número de mediciones?
- [ ] ¿Iniciaron la bitácora de diseño?

---

> 🎯 **Recuerden:** El objetivo NO es hacer el proyecto más complejo posible, sino un proyecto **bien ejecutado, robusto y que demuestre lo que aprendieron.** Con 7 semanas, proyectos bien acotados y bien hechos brillan más que proyectos ambiciosos a medias. No importa si es un instrumento de medición, un dispositivo interactivo, o la automatización de un experimento — lo importante es que uses el toolkit S1-S9 y funcione.
