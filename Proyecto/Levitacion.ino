// Control PWM de una bobina con MOSFET IRLZ44N
// Arduino Uno - Un solo canal PWM
// Pin recomendado: D9

const int PWM_PIN = 9;   // Pin PWM conectado al Gate del MOSFET mediante resistencia de 220 ohm

int pwmValue = 0;        // Valor PWM actual: 0 a 255

void setup() {
  pinMode(PWM_PIN, OUTPUT);

  // Por seguridad, arrancamos con la bobina apagada
  analogWrite(PWM_PIN, 0);

  Serial.begin(115200);

  delay(500);

  Serial.println("=== Control PWM de bobina ===");
  Serial.println("Comandos disponibles:");
  Serial.println("  pwm 0       -> Apaga la bobina");
  Serial.println("  pwm 120     -> PWM con valor de 0 a 255");
  Serial.println("  pwm 50%     -> PWM como porcentaje");
  Serial.println("  on          -> PWM al maximo");
  Serial.println("  off         -> Apaga la bobina");
  Serial.println("  status      -> Muestra el PWM actual");
  Serial.println("  help        -> Muestra esta ayuda");
  Serial.println();
  Serial.println("Escribe un comando:");
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    command.toLowerCase();

    processCommand(command);
  }
}

void processCommand(String command) {
  if (command.length() == 0) {
    return;
  }

  if (command == "help") {
    printHelp();
  }

  else if (command == "status") {
    printStatus();
  }

  else if (command == "off") {
    setPWM(0);
  }

  else if (command == "on") {
    setPWM(255);
  }

  else if (command.startsWith("pwm")) {
    command.replace("pwm", "");
    command.trim();

    if (command.endsWith("%")) {
      command.replace("%", "");
      command.trim();

      int percent = command.toInt();
      percent = constrain(percent, 0, 100);

      int value = map(percent, 0, 100, 0, 255);
      setPWM(value);
    } 
    
    else {
      int value = command.toInt();
      value = constrain(value, 0, 255);

      setPWM(value);
    }
  }

  else {
    Serial.println("Comando no reconocido.");
    Serial.println("Escribe 'help' para ver los comandos disponibles.");
  }
}

void setPWM(int value) {
  pwmValue = constrain(value, 0, 255);
  analogWrite(PWM_PIN, pwmValue);

  Serial.print("PWM ajustado a: ");
  Serial.print(pwmValue);
  Serial.print(" / 255  |  ");

  float percent = (pwmValue / 255.0) * 100.0;
  Serial.print(percent, 1);
  Serial.println(" %");
}

void printStatus() {
  Serial.print("PWM actual: ");
  Serial.print(pwmValue);
  Serial.print(" / 255  |  ");

  float percent = (pwmValue / 255.0) * 100.0;
  Serial.print(percent, 1);
  Serial.println(" %");
}

void printHelp() {
  Serial.println();
  Serial.println("=== Comandos disponibles ===");
  Serial.println("pwm 0       -> Apaga la bobina");
  Serial.println("pwm 120     -> PWM con valor entre 0 y 255");
  Serial.println("pwm 50%     -> PWM como porcentaje");
  Serial.println("on          -> PWM al maximo");
  Serial.println("off         -> Apaga la bobina");
  Serial.println("status      -> Muestra el PWM actual");
  Serial.println("help        -> Muestra esta ayuda");
  Serial.println();
}