const int ldrPin = A0; // Pino analógico onde o sensor LDR está conectado
const int ledPin = 4; // Pino onde o LED está conectado

int ldrValue; // Variável para armazenar o valor lido do sensor LDR
int threshold = 210; // Valor de limiar para determinar a luminosidade baixa

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  ldrValue = analogRead(ldrPin); // Lê o valor do sensor LDR

  if (ldrValue < threshold) {
    digitalWrite(ledPin, HIGH); // Acende o LED se a luminosidade for baixa
  } else {
    digitalWrite(ledPin, LOW); // Apaga o LED se a luminosidade for alta
  }

  Serial.print("LDR Value: ");
  Serial.println(ldrValue);
  delay(100); // Aguarda um segundo antes de fazer a próxima leitura
}
