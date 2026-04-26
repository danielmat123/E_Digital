/*
para este caso se toma el pin A2 para conectar el sensor de temperatura LM35,
aunque también se puede usar A0, A1, A3, A4 o A5. 
El código es el mismo, solo cambia la constante pinLM35.
*/

const int pinLM35 = A2;


unsigned long t0 = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("t(ms)\traw\ttempC");
}

void loop() {

 /*
 muetreando los datos cada 500 ms (2 Hz), se evita saturar el Serial Monitor con demasiados datos,
 permitiendo observar los cambios en la temperatura de manera clara y legible.
 */  
  if (millis() - t0 >= 500) {
    t0 = millis();

/*
el factor de escala es 500, puesto el que sensor LM35 produce una salida de 10 mV/°C
el voltaje de referencia son 5 V, por lo que 5/0.01 = 500.0
se divide por 1023.0 porque el ADC produce 1024 niveles (0 a 1023), y el nivel 1023 corresponde exactamente a V_ref = 5.00 V
*/
    int rawLM35 = analogRead(pinLM35);
    float tempC = rawLM35 * (500.0 / 1023.0);

    Serial.print(t0);
    Serial.print("\t");
    Serial.print(rawLM35);
    Serial.print("\t");
    Serial.println(tempC, 2);
  }

}
