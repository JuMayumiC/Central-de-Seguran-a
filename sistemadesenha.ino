const int buttonPin1 = 13; // Pino do primeiro botão
const int buttonPin2 = 12; // Pino do segundo botão
const int buttonPin3 = 11; // Pino do terceiro botão
const int confirmPin = 10; // Pino do botão de confirmação
const int ledCorrectPin = 8; // Pino do LED de senha correta
const int ledIncorrectPin = 9; // Pino do LED de senha incorreta

const int passwordLength = 6; // Comprimento da senha
const int correctPassword[passwordLength] = {1, 2, 3, 1, 2, 3}; // Substitua pelos dígitos da senha correta

int enteredPassword[passwordLength];
int currentIndex = 0;
bool passwordEntered = false;

void setup() {
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(confirmPin, INPUT_PULLUP);
  pinMode(ledCorrectPin, OUTPUT);
  pinMode(ledIncorrectPin, OUTPUT);
  
  Serial.begin(9600);
  
  digitalWrite(ledIncorrectPin, LOW); // Inicia com o LED de senha incorreta aceso
}

void loop() {
  if (!passwordEntered) {
    checkButton(buttonPin1, 1);
    checkButton(buttonPin2, 2);
    checkButton(buttonPin3, 3);
  }
  
  if (digitalRead(confirmPin) == HIGH && !passwordEntered) {
    checkPassword();
  }
}

void checkButton(int pin, int digit) {
  if (digitalRead(pin) == HIGH) {
     Serial.print("Botão ");
    Serial.print(digit);
    Serial.println(" pressionado.");
    enteredPassword[currentIndex] = digit;
    currentIndex = (currentIndex + 1) % passwordLength;
    delay(250); // Para evitar leituras múltiplas com um único pressionamento
  }
}

void checkPassword() {
  bool passwordCorrect = true;
  for (int i = 0; i < passwordLength; i++) {
    if (enteredPassword[i] != correctPassword[i]) {
      passwordCorrect = false;
      break;
    }
  }

  if (passwordCorrect) {
    digitalWrite(ledCorrectPin, HIGH);
    digitalWrite(ledIncorrectPin, LOW);
    passwordEntered = true;
  } else {
    digitalWrite(ledCorrectPin, LOW);
    digitalWrite(ledIncorrectPin, HIGH);
    delay(1000); // Pisca o LED de senha incorreta por 1 segundo
    digitalWrite(ledIncorrectPin, LOW);
    clearEnteredPassword();
  }
}

void clearEnteredPassword() {
  for (int i = 0; i < passwordLength; i++) {
    enteredPassword[i] = 0;
  }
  currentIndex = 0;
}
