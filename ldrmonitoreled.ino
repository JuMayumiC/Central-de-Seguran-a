const int ledPin = 4; // Pino do LED vermelho
const int ldrPin = A0; // Pino analógico onde o sensor LDR está conectado
int ldrValue; // Variável para armazenar o valor lido do sensor LDR

void setup() {
  pinMode(ldrPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  ldrValue = analogRead(ldrPin); // Lê o valor do sensor LDR

  if (ldrValue < 200) {
    // Inicia a contagem regressiva de 10 a 0
    for (int i = 10; i >= 0; i--) {
      Serial.println(i);
      digitalWrite(ledPin, HIGH); // Acende o LED se a luminosidade for baixa
      delay(1000); // Aguarda 1 segundo
      digitalWrite(ledPin, LOW); // Apaga o LED
    }
}
   
        


  // Aguarda um breve intervalo antes de fazer a próxima leitura
  delay(100);
}
