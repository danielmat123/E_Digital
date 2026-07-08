# Reporte de Progreso — Entregable Escrito
## Sistema de Levitación Magnética Activa

**Grupo:** ___
**Integrantes:**
- Daniel Mateo González Sánchez
- Andres Felipe Polanco Olaya
- Juan Sebastian Baquero Pinzón
- Juan Felipe Sánchez Poveda

**Fecha:** ___

---

> ⚠️ **Nota para el equipo antes de entregar:** este documento sigue exactamente el orden que pidió el profesor (estado de subsistemas → cambios → problemas/soluciones → plan → MVP), y agrega dos secciones que la rúbrica exige explícitamente: una sección de **honestidad sobre lo que no funciona** y una sección de **Plan B** dedicada. Reemplacen cada `[FOTO REAL: ...]` por una foto propia tomada en el laboratorio — no usen imágenes de internet, el profesor lo pidió textualmente. Reemplacen cada `[DATO: ...]` con la medición real antes de subir el PDF.

---

## 1. Estado actual de cada subsistema

### 1.1 Subsistema mecánico
**Estado: funcionando.**

Está construido el soporte para dos bobinas axiales enfrentadas, alineadas sobre el mismo eje. El diseño deja espacio físico para agregar bobinas laterales más adelante, pero por ahora esa expansión **no está implementada** (ver Sección 6).

`[FOTO REAL: soporte mecánico completo, tomada en el laboratorio]`

### 1.2 Subsistema de actuación
**Estado: funcionando en modo manual, no automático.**

La arquitectura final usa dos bobinas de núcleo de aire (500–600 espiras), alimentadas por MOSFETs controlados por Arduino vía PWM. Con esta configuración se logra suspender el imán sin soporte mecánico, pero **el valor de PWM lo fija una persona a mano, moviendo un potenciómetro/variable en el código** — no hay lazo de control cerrado todavía.

`[FOTO REAL: bobinas axiales instaladas]`

`[DATO: rango de PWM (0–255) donde se logra la suspensión, y cuánto dura la suspensión antes de que el imán se caiga o se pegue]`

### 1.3 Subsistema de sensado
**Estado: parcialmente funcionando.**

Los 5 sensores Hall del diseño original fueron descartados (Sección 2). El sensor de altura que los reemplaza ya entrega lecturas razonables en pruebas de banco, pero **todavía no está leído dentro del lazo de control** — hoy es solo una lectura de diagnóstico en el monitor serial, no se usa para corregir nada.

`[FOTO REAL: sensor de altura instalado sobre el sistema]`

`[DATO: error de medición del sensor de altura frente a una regla/calibre, en mm]`

### 1.4 Subsistema de control
**Estado: NO implementado. Este es el punto más atrasado del proyecto y lo decimos sin rodeos.**

No existe controlador PID ni ningún lazo de control automático corriendo en el Arduino. Lo único que existe es control manual: una persona ajusta el PWM de las dos bobinas hasta encontrar el punto de equilibrio del imán. Esto es intencional en esta etapa (necesitábamos primero validar que la arquitectura electromagnética era físicamente viable antes de invertir tiempo en el PID), pero implica que el requisito original de Entregable 1 — *"Control PID de las bobinas interiores en serie"* — **no se cumple todavía en su forma literal**, porque la arquitectura de 8 bobinas para la cual se definió ese requisito ya no existe (ver Sección 2 y Sección 6).

### 1.5 Subsistema electrónico
**Estado: funcionando, con un rediseño reciente.**

Arduino Uno + MOSFETs de potencia + dos bobinas + sensor de altura. Se detectó un problema de acoplamiento al alimentar ambas bobinas desde una sola fuente (Sección 3, Problema 4); la solución (una fuente independiente por bobina) **está definida pero aún no instalada físicamente**.

`[FOTO REAL: circuito electrónico actual, incluyendo la fuente compartida que todavía está en uso]`

---

## 2. Cambios respecto al diseño original, justificados

El diseño que se aprobó en la propuesta (8 bobinas con núcleo de hierro + 5 sensores Hall + control lateral y vertical) fue abandonado por completo. Esto es un cambio de alcance grande, no un ajuste menor, y lo explicamos con la evidencia experimental que lo forzó.

**Diseño 1 — 8 bobinas con núcleo de hierro (diseño original aprobado).**
Al construir las 8 bobinas y probarlas, el núcleo de hierro atraía el imán con más fuerza de la que las bobinas podían repeler. El imán se pegaba al núcleo en vez de levitar. Fue un fallo físico, no de tuning: no había forma de ajustar PWM o control que arreglara esto, había que cambiar de núcleo.

**Diseño 2 — 8 bobinas núcleo de aire, atracción a favor de la gravedad.**
Se cambió la estrategia (atraer hacia arriba en vez de repeler) para evitar el problema del núcleo. El campo generado por las 8 bobinas resultó insuficiente para sostener el peso del imán. Diagnóstico: demasiadas bobinas pequeñas repartiendo corriente en vez de pocas bobinas concentrando campo.

**Diseño 3 — 1 bobina + sensor Hall con compensación por regresión lineal.**
Se calibró una regresión para restar del sensor Hall el campo generado por la propia bobina y quedarse solo con la componente del imán. Funcionó, pero se descubrió que buena parte de la estabilidad observada venía de piezas ferromagnéticas dentro del encapsulado del sensor Hall, no del control. Al quitarlas, la levitación dejó de ser estable. Es decir, el resultado "bueno" de este diseño era en parte un artefacto de medición, no un logro de control real — lo reportamos así de honesto porque nos habría sido fácil quedarnos con ese resultado.

**Diseño 4 — 2 bobinas axiales núcleo de aire (diseño actual).**
Bobina superior atrae, bobina inferior repele; entre ambas se forma una zona de equilibrio. Con ajuste manual de PWM se logra levitación sostenida sin soporte mecánico. Es el primer diseño donde la levitación es explicable por física de campos y no por un efecto secundario no controlado.

**Por qué esto importa para la entrega:** el requisito de Entregable 1 en la propuesta original ("PID de 4 bobinas interiores en serie") fue escrito para el Diseño 1/2, que ya no existe. Vamos a plantearle formalmente este pivote al profesor antes del Entregable 2, como exige la regla de "Cambio de rumbo" de la propuesta — este documento es parte de esa notificación.

---

## 3. Problemas encontrados y soluciones intentadas (incluyendo lo que no funcionó)

| # | Problema | Diagnóstico | Solución intentada | ¿Resuelto? |
|---|---|---|---|---|
| 1 | Núcleo de hierro atrae el imán más de lo que repele | Fuerza de atracción del núcleo domina sobre la fuerza de control | Migrar a núcleo de aire | ✅ Sí |
| 2 | 8 bobinas a favor de gravedad no sostienen el imán | Campo total insuficiente, dispersado en muchas bobinas pequeñas | Concentrar en 2 bobinas axiales | ✅ Sí |
| 3 | "Estabilidad" del sensor Hall era parcialmente un artefacto | Material ferromagnético en el encapsulado del sensor | Reemplazar sensor Hall por sensor de altura | ✅ Sí, pero obligó a rediseñar todo el subsistema de sensado |
| 4 | Al bajar el PWM de una bobina, el imán a veces sube | Ambas bobinas comparten una sola fuente; bajar el consumo de una libera corriente para la otra | Usar una fuente independiente por bobina | ⚠️ Solución definida, **falta instalarla** |
| 5 | No hay control automático | Aún no se ha escrito el PID; se priorizó validar la física primero | Implementar PID vertical usando el sensor de altura | ❌ **No resuelto — es la prioridad #1 de las próximas dos semanas** |

---

## 4. Plan concreto para lo que falta

1. **Semana actual:** instalar la fuente independiente por bobina (Problema 4) — es prerrequisito para que el PID funcione con datos limpios.
2. **Semana actual:** integrar la lectura del sensor de altura al lazo principal (hoy solo se imprime por serial, no se usa).
3. **Próxima semana:** implementar el controlador PID vertical (`millis()`, sin `delay()`), usando el sensor de altura como única realimentación.
4. **Próxima semana:** medir y documentar: altura de equilibrio lograda vs. altura teórica (usando el notebook de cálculo ya definido en la propuesta), tiempo de levitación sostenida, error en mm respecto al punto objetivo.
5. **Antes del Entregable 2:** conversación formal con el profesor sobre el pivote de diseño (Sección 2), para confirmar que la nueva arquitectura de 2 bobinas es aceptable como reemplazo del plan de 8 bobinas.
6. **Evaluar más adelante, sin comprometerlo todavía:** si el tiempo lo permite, agregar bobinas laterales para corrección horizontal. Con el estado actual del proyecto, **no lo damos por hecho**.

---

## 5. ¿Está el MVP funcionando o encaminado?

**Encaminado, no funcionando todavía.** Para ser precisos sobre qué significa cada palabra:

- **Lo que sí funciona hoy:** el imán levita sin soporte mecánico, de forma sostenida, ajustando el PWM a mano. Esto valida que la arquitectura electromagnética elegida es físicamente correcta.
- **Lo que NO funciona hoy:** no hay control automático. Si alguien no está ajustando el PWM en vivo, el sistema no se autocorrige ni mantiene la posición del imán ante perturbaciones.
- **Por qué lo llamamos "encaminado" y no "en riesgo":** la parte más incierta del proyecto (¿existe una configuración de bobinas que físicamente pueda sostener el imán de forma estable?) ya está resuelta con evidencia experimental. Lo que falta —el PID— es trabajo de ingeniería de control estándar sobre una plataforma que ya se sabe que funciona, no una incógnita física abierta.

---

## 6. Plan B

Si el controlador PID no queda completamente implementado para la demo final, el equipo puede mostrar, sin necesidad de más desarrollo adicional:

- Levitación real del imán sin soporte mecánico, con las dos bobinas axiales.
- El punto de equilibrio encontrado y ajustado en vivo mediante PWM manual.
- El sensor de altura funcionando y mostrando lecturas en tiempo real por serial (aunque no esté cerrando el lazo).
- Comparación entre la altura teórica calculada (notebook) y la altura real alcanzada.
- La bitácora completa de las cuatro iteraciones de diseño (Sección 2), como evidencia de proceso de ingeniería.

Esto no demuestra control automático, pero sí demuestra que el equipo entiende y puede defender cada decisión de diseño — que es la regla de oro del curso — incluso en la versión más reducida de la entrega.

---

## 7. Conclusión breve

El diseño original no era viable y lo supimos por evidencia de laboratorio, no por falta de esfuerzo: dos arquitecturas completas se probaron y descartaron antes de llegar a la actual. Donde estamos hoy es en control manual funcionando sobre una plataforma física validada, sin PID todavía. Ese es el estado real del proyecto y lo reportamos así de directo porque preferimos que quede diagnosticado con plan concreto (Sección 4) a que parezca más avanzado de lo que está.
