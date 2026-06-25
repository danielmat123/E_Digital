# Revision de informes SO - E_Digital

Actualizacion: 2026-06-25
Repositorio: https://github.com/danielmat123/E_Digital
Fuente nueva revisada: `Inputs/`

## Mapeo de Inputs

| Archivo en `Inputs` | Practica asociada | Uso aplicado |
|---|---|---|
| `Practica4.xlsx` | S04 | Datos de baudrate y tiempos para corregir tabla y generar grafica. |
| `practica4E.docx` | S04 | Evidencias de Monitor Serial, protocolo humanizado y codigo compacto/Python. |
| `lab4-actividad8.txt` | S04 | Referencia para cliente Python con menu. |
| `datos_s6_20260506_082849.xlsx` | S06 | Estadisticas multicanal, cadencia de muestreo y grafica `raw_ldr` vs `t_ms`. |
| `datos_P6.docx` | S06 | Capturas de I2C scanner y CSV continuo durante conmutacion. |
| `IMG-20260625-WA0004/0005/0008.jpg` | S06 | Fotos de OLED y montaje para Actividad 3. |
| `laboratorio8.xlsx` | S08 | Tablas de filtrado, oversampling y graficas derivadas. |
| `IMG-20260608-WA0022/0023.jpg` | S09 | Capturas de osciloscopio para onda periodica, diente de sierra y triangular. |
| `IMG-20260608-WA0025.jpg` | S09 | Foto OLED/FSM del Reto 2. |
| `Lab 4.jpeg` | Sin uso | Archivo vacio de 0 bytes. |

## Estado actualizado

| Informe | Estado actual | Avance estimado | Lo completado en esta iteracion | Lo que aun falta |
|---|---:|---:|---|---|
| S03 | Completo | 95% | Se corrigio la contradiccion de debouncing. | Solo revision fina si se quiere pulir estilo. |
| S04 | Completo con datos disponibles | 95% | Se agregaron imagenes, grafica de tiempos, analisis, codigo compacto/Python, dificultades y pregunta abierta. | Revision humana final de redaccion. |
| S05 | Parcial avanzado | 75% | Se completo interpretacion, preguntas de analisis, dificultades y pregunta abierta usando los datos ya presentes. | Falta fecha de practica/entrega y Figura 1 real del Serial Monitor de Actividad 1. |
| S06 | Completo con datos disponibles | 95% | Se agregaron descripcion CSV, respuestas, fotos OLED, CSV continuo, grafica LDR, codigo, dificultades y pregunta abierta. | Revision humana final; confirmar fecha si no fue 6 de mayo de 2026. |
| S07 | Bloqueado por falta de datos | 15% | Se completaron integrantes y grupo. | Faltan tablas ON/OFF/P/PI, 8 capturas, analisis con datos, codigo y dificultades. |
| S08 | Completo con datos disponibles | 90% | Se llenaron tablas, graficas, analisis, codigo de referencia, dificultades y pregunta abierta desde `laboratorio8.xlsx`. | Confirmar fecha de practica y revisar si el comportamiento de oversampling fue tomado bajo condiciones comparables. |
| S09 | Parcial | 40% | Se agregaron capturas disponibles y respuestas conceptuales. | Faltan captura senoidal, frecuencia min/max, CSV I-V rojo/verde, graficas I-V y codigo final de ambos retos. |
| Proyecto | Avanzado | 80% | Sin nuevos datos aplicables en `Inputs`. | Completar datos administrativos, costos/cantidades, checklist y limpiar texto de plantilla. |

## Pendientes accionables

### Prioridad alta

- **S07:** conseguir datos experimentales de control ON/OFF, P y PI.
- **S07:** agregar capturas `act2-onoff-oscilacion.png`, `act3-control-p-kp1/2/3.png`, `act4-control-pi-windup.png`, `act4-control-pi-ki1/2/3.png`.
- **S07:** pegar codigo de parser serial, ON/OFF, P y PI.
- **S09:** agregar captura de senoidal y capturas de frecuencia minima/maxima.
- **S09:** agregar CSV completo de barrido I-V para LED rojo y verde.
- **S09:** generar graficas I-V cuando existan los CSV.
- **S09:** pegar codigo final de `lab-09-generacion-senales.ino` y `lab-09-iv-led.ino`.
- **S05:** agregar Figura 1 real de Actividad 1 y completar fechas.

### Prioridad media

- **S08:** confirmar fecha de practica.
- **S06:** confirmar fecha exacta de practica.
- **Proyecto:** completar costos/cantidades, checklist y retirar instrucciones de plantilla.
- **Todos:** hacer lectura final de ortografia antes de entrega.

## Archivos generados o agregados

- `S04/imagenes/fig2-grafica-tiempos.png`
- `S04/imagenes/fig4-consola-python-terminal.png`
- `S06/imagenes/s06_raw_ldr_vs_t_ms.png`
- `S06/imagenes/oled_pantalla_general.jpg`
- `S06/imagenes/oled_detalle_temperatura.jpg`
- `S06/imagenes/csv_continuo_conmutacion.png`
- `S08/imagenes/captura-1-serial-plotter-filtrado.png`
- `S08/imagenes/grafica-2-oversampling.png`
- `S09/imagenes/reto-1-onda-periodica.png`
- `S09/imagenes/reto-1-diente-sierra.png`
- `S09/imagenes/reto-1-triangular.png`
- `S09/imagenes/reto-2-oled-fsm.png`

## Nota importante

No se inventaron mediciones donde `Inputs` no tenia datos. En S07 y en parte de S09 quedaron pendientes explicitos porque faltan las tablas, CSV o capturas necesarias para completar esas secciones con evidencia real.
