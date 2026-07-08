# Reporte de Progreso – Proyecto Final
## Sistema de Levitación Magnética Activa

**Grupo:** ___

**Integrantes:**
- Daniel Mateo González Sánchez
- Andres Felipe Polanco Olaya
- Juan Sebastian Baquero Pinzón
- Juan Felipe Sánchez Poveda

---

# 1. Estado actual de los subsistemas

Durante el desarrollo del proyecto se realizaron múltiples iteraciones sobre el diseño original. Los resultados experimentales obtenidos permitieron identificar limitaciones importantes de la propuesta inicial y llevaron a un rediseño progresivo del sistema hasta obtener una configuración más estable y viable para implementar el control automático.

## Subsistema mecánico

Actualmente se encuentra construido el soporte mecánico para una configuración de dos bobinas axiales enfrentadas. Esta estructura permite mantener ambas bobinas alineadas sobre un mismo eje, facilitando la generación del campo magnético necesario para la levitación.

La estructura fue diseñada pensando en futuras modificaciones, permitiendo incorporar bobinas adicionales en dirección cardinal para implementar control lateral si el desarrollo del proyecto lo permite.

> **Foto 1.** Soporte mecánico del sistema.

---

## Subsistema de actuación

Inicialmente se construyeron ocho bobinas con núcleo de hierro, aproximadamente de 200 espiras de alambre calibre AWG 22 cada una.

Posteriormente, tras las pruebas experimentales, se construyó una bobina individual de aproximadamente 500–600 espiras con núcleo de aire para realizar experimentos de control mediante sensor Hall.

Finalmente, el diseño actual utiliza únicamente dos bobinas axiales con núcleo de aire enfrentadas, alimentadas mediante MOSFETs controlados por Arduino.

El control realizado hasta el momento ha sido completamente manual, variando el PWM suministrado a cada bobina para encontrar un punto de equilibrio del imán.

> **Foto 2.** Bobinas actualmente instaladas.

---

## Subsistema de sensado

En el diseño original se contemplaba el uso de cinco sensores Hall para determinar la posición del imán y realizar correcciones tanto verticales como laterales.

Durante el desarrollo se realizaron pruebas utilizando un sensor Hall para compensar el efecto del campo generado por la bobina mediante una calibración experimental.

Actualmente el sensor Hall fue descartado debido a los inconvenientes encontrados durante las pruebas.

El diseño actual contempla utilizar un sensor de altura como única realimentación para implementar el controlador PID vertical.

Las primeras pruebas del sensor muestran un funcionamiento aceptable, aunque todavía debe integrarse completamente al sistema.

> **Foto 3.** Sensor de altura instalado.

---

## Subsistema de control

Hasta el momento no se encuentra implementado el controlador PID.

Las pruebas realizadas consistieron en modificar manualmente el PWM enviado a ambas bobinas para encontrar experimentalmente un punto de equilibrio del imán.

Estas pruebas permitieron verificar que la nueva configuración electromagnética es capaz de mantener suspendido el imán sin soporte mecánico cuando ambas bobinas trabajan conjuntamente.

El siguiente paso consiste en automatizar este proceso utilizando el sensor de altura y un controlador PID.

---

## Subsistema electrónico

Actualmente el sistema está compuesto por:

- Arduino Uno
- MOSFETs de potencia
- Dos bobinas electromagnéticas
- Fuente de alimentación
- Sensor de altura

Durante las pruebas se detectó un problema importante relacionado con la alimentación de ambas bobinas utilizando una única fuente de potencia.

Este comportamiento motivó una modificación del diseño eléctrico, utilizando una fuente independiente para cada bobina.

> **Foto 4.** Circuito electrónico del sistema.

---

# 2. Cambios respecto al diseño original

El proyecto sufrió varios cambios importantes durante su desarrollo. Estos cambios fueron consecuencia directa de los resultados obtenidos en laboratorio y no de modificaciones arbitrarias del alcance del proyecto.

## Primer diseño: ocho bobinas con núcleo de hierro

La propuesta inicial contemplaba un sistema compuesto por ocho bobinas con núcleo ferromagnético distribuidas alrededor del imán.

El objetivo era controlar tanto el movimiento vertical como las desviaciones laterales mediante múltiples sensores Hall y control PID.

Sin embargo, al construir las ocho bobinas y realizar las primeras pruebas se encontró un comportamiento no previsto.

El núcleo de hierro ejercía una atracción sobre el imán considerablemente mayor que la fuerza de repulsión generada por las bobinas. Como consecuencia, el imán tendía a adherirse al núcleo, imposibilitando la levitación estable.

Este comportamiento hizo inviable continuar desarrollando esta arquitectura.

---

## Segundo diseño: ocho bobinas trabajando a favor de la gravedad

Como alternativa se decidió modificar el funcionamiento del sistema.

En lugar de intentar repeler el imán, todas las bobinas fueron configuradas para atraerlo hacia arriba, aprovechando la gravedad como fuerza restauradora.

Aunque conceptualmente esta configuración resultaba más estable, el campo magnético generado por las ocho bobinas no fue suficiente para sostener el imán.

Las pruebas demostraron que la intensidad del campo obtenida con esta arquitectura era insuficiente para alcanzar la levitación.

---

## Tercer diseño: una bobina y sensor Hall

Posteriormente se construyó una bobina de aproximadamente 500–600 espiras con núcleo de aire.

La estrategia consistía en controlar la posición del imán utilizando un sensor Hall.

Para ello se realizó una calibración experimental midiendo la respuesta del sensor para diferentes valores de PWM aplicados a la bobina.

A partir de estos datos se obtuvo una regresión lineal que permitía estimar la contribución del campo generado por la bobina y restarla de la medición total del sensor, obteniendo así únicamente la componente producida por el imán.

Esta metodología mostró resultados prometedores.

Sin embargo, posteriormente se identificó que parte del funcionamiento se debía a la presencia de pequeñas piezas ferromagnéticas en el encapsulado del sensor Hall.

Al eliminar estos elementos, la levitación dejó de ser estable, por lo que esta arquitectura también fue descartada.

---

## Diseño actual

Finalmente se adoptó una configuración formada por dos bobinas axiales enfrentadas, ambas con núcleo de aire y orientadas de forma que sus campos magnéticos apuntan en la misma dirección.

En esta configuración:

- la bobina superior atrae el imán hacia su centro;
- la bobina inferior genera una fuerza de repulsión.

La interacción entre ambas produce una región de equilibrio donde el imán puede permanecer suspendido sin contacto físico.

Durante las pruebas experimentales fue posible obtener levitación del imán mediante ajuste manual del PWM aplicado a ambas bobinas.

Este resultado constituye la base sobre la cual se implementará el controlador automático.

---

# 3. Problemas encontrados y soluciones implementadas

## Problema 1: atracción del núcleo de hierro

El mayor inconveniente encontrado durante el desarrollo fue la utilización de núcleos ferromagnéticos.

En lugar de favorecer la levitación, estos producían una atracción dominante sobre el imán.

**Solución implementada**

Se descartó completamente el uso de núcleos de hierro y se migró hacia bobinas con núcleo de aire.

---

## Problema 2: campo magnético insuficiente

La configuración de ocho bobinas trabajando a favor de la gravedad no logró generar una fuerza suficiente para sostener el imán.

**Solución implementada**

Se rediseñó completamente la arquitectura hacia una configuración de dos bobinas axiales.

---

## Problema 3: limitaciones del sensor Hall

La estrategia basada en compensar el campo magnético mediante regresión lineal funcionó parcialmente.

Sin embargo, posteriormente se identificó que la presencia de material ferromagnético en el sensor alteraba las mediciones y contribuía artificialmente a la estabilidad observada.

**Solución implementada**

Se decidió reemplazar el sistema de medición por un sensor de altura.

---

## Problema 4: alimentación compartida

Durante las pruebas se observó que al disminuir el PWM de la bobina inferior para hacer descender el imán, este en ocasiones ascendía.

El análisis del circuito permitió concluir que ambas bobinas compartían la misma fuente de alimentación.

Al disminuir el consumo de una bobina aumentaba la corriente disponible para la otra, modificando involuntariamente el campo magnético total.

**Solución implementada**

Como siguiente etapa del proyecto se utilizarán dos fuentes independientes, una para cada bobina.

---

# 4. Plan de trabajo

Las siguientes actividades corresponden al desarrollo restante del proyecto.

1. Integrar completamente el sensor de altura.
2. Calibrar la medición de posición.
3. Implementar un controlador PID para el eje vertical.
4. Alimentar cada bobina mediante una fuente independiente.
5. Ajustar experimentalmente los parámetros del controlador.
6. Evaluar la incorporación de bobinas laterales para implementar estabilización horizontal.

---

# 5. Estado del MVP

Actualmente el proyecto se considera **encaminado**, aunque aún no completamente terminado.

La arquitectura electromagnética definitiva ya fue identificada y validada experimentalmente.

Se logró obtener levitación del imán sin soporte mecánico utilizando únicamente las dos bobinas axiales, ajustando manualmente la intensidad de corriente mediante PWM.

El trabajo restante corresponde principalmente al cierre del lazo de control automático mediante el sensor de altura y el controlador PID.

---

# 6. Plan B

En caso de no lograr implementar completamente el controlador PID antes de la entrega final, el proyecto podrá demostrar:

- funcionamiento del sistema electromagnético de dos bobinas;
- levitación del imán mediante ajuste manual del PWM;
- funcionamiento del sensor de altura;
- implementación parcial del sistema de control;
- evidencia experimental de todas las iteraciones de diseño realizadas.

Este plan B continúa demostrando las competencias desarrolladas durante el curso en electrónica digital, adquisición de señales, accionamiento mediante PWM, integración de hardware y proceso de diseño basado en evidencia experimental.

---

# 7. Conclusiones

Aunque el diseño original no produjo los resultados esperados, las diferentes iteraciones permitieron comprender las limitaciones físicas del sistema y conducir el proyecto hacia una arquitectura considerablemente más viable.

El proceso seguido refleja una metodología de ingeniería basada en experimentación, análisis de resultados y rediseño continuo. En lugar de insistir sobre una arquitectura cuya viabilidad experimental era limitada, se optó por una solución más sencilla pero físicamente robusta, conservando el objetivo principal del proyecto: implementar un sistema de levitación magnética controlado mediante realimentación y control PID.

Actualmente el proyecto cuenta con una plataforma funcional sobre la cual puede implementarse el sistema de control automático durante la siguiente etapa del desarrollo.
