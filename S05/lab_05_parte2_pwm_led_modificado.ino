// === DEFINICIÓN DE PINES ===
const int ENA = 9;   // Salida PWM para velocidad
const int IN1 = 7;   // Sentido 1
const int IN2 = 8;   // Sentido 2
const int Botton = 3; // Botón físico para cambio manual de sentido

// === VARIABLES GLOBALES ===
bool est_btn = false;       // Estado de dirección
int last_btn_state = HIGH;  // Para detectar presión del botón
int velocidadActual = 0;    // Velocidad controlada solo por Serial (0-255)

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(Botton, INPUT_PULLUP); // Resistencia interna activa

  Serial.begin(9600);
  Serial.println("--- Sistema Listo (Control Serial) ---");
  Serial.println("Comandos: STATUS, SENTIDO, VEL=XXX (0-255)");
  
  // Iniciar con el motor detenido
  analogWrite(ENA, 0);
  actualizarMotores();
}

void loop() {
  leerSerial(); // Escucha si hay nuevos comandos

  // 1. Detección del botón físico (siempre activo para emergencias o pruebas)
  int current_btn_state = digitalRead(Botton);
  if (current_btn_state == LOW && last_btn_state == HIGH) {
    est_btn = !est_btn;
    actualizarMotores();
    delay(50); // Debounce
    Serial.println("EVENTO: Cambio de sentido por BOTON");
  }
  last_btn_state = current_btn_state;
}

// === PROCESAMIENTO DE COMANDOS ===
void procesarComando(char* cmd) {
  
  // Comando: STATUS (Muestra datos actuales)
  if (strcmp(cmd, "STATUS") == 0) {
    Serial.println("\n--- ESTADO ACTUAL ---");
    Serial.print("Velocidad PWM: "); Serial.println(velocidadActual);
    Serial.print("Dirección: "); Serial.println(est_btn ? "IN1:H / IN2:L Horario" : "IN1:L / IN2:H  Antihorario");
    Serial.println("---------------------");
  }

  // Comando: SENTIDO (Alterna giro)
  else if (strcmp(cmd, "SENTIDO") == 0) {
    est_btn = !est_btn;
    actualizarMotores();
    Serial.println("OK: Sentido cambiado por SERIAL");
  }

  // Comando: VEL=XXX (Ajusta velocidad de 0 a 255)
  else if (strncmp(cmd, "VEL=", 4) == 0) {
    int nuevaVel = atoi(&cmd[4]); // Extrae el número después de "VEL="
    
    if (nuevaVel >= 0 && nuevaVel <= 255) {
      velocidadActual = nuevaVel;
      analogWrite(ENA, velocidadActual);
      Serial.print("OK: Velocidad actualizada a ");
      Serial.println(velocidadActual);
    } else {
      Serial.println("ERROR: Rango inválido (Usa 0-255)");
    }
  }
}

// Función para escribir en los pines de dirección
void actualizarMotores() {
  if (est_btn) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }
}

// Función básica para leer el puerto serial (Debes tenerla o usar esta)
void leerSerial() {
  static char buffer[20];
  static int index = 0;

  while (Serial.available() > 0) {
    char c = Serial.read();
    if (c == '\n' || c == '\r') {
      buffer[index] = '\0';
      if (index > 0) {
        procesarComando(buffer);
      }
      index = 0;
    } else if (index < 19) {
      buffer[index++] = c;
    }
  }
}