const int ldrPin = A0; // Pino analógico onde o sensor LDR está conectado
int ldrValue; // Variável para armazenar o valor lido do sensor LDR

void setup() {
  pinMode(ldrPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  ldrValue = analogRead(ldrPin); // Lê o valor do sensor LDR

  if (ldrValue < 200) {
    // Inicia a contagem regressiva de 10 a 0
    for (int i = 10; i >= 0; i--) {
      Serial.println(i);
      delay(1000); // Aguarda 1 segundo
    }
  }

  // Aguarda um breve intervalo antes de fazer a próxima leitura
  delay(100);
}
