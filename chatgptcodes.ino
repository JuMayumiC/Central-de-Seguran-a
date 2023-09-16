const int buttonPin1 = 13; // Pino do primeiro botão
const int buttonPin2 = 12; // Pino do segundo botão
const int buttonPin3 = 11; // Pino do terceiro botão
const int confirmPin = 10; // Pino do botão de confirmação
const int ledCorrectPin = 8; // Pino do LED de senha correta
const int ledEnterPassword = 9; // Pino do LED para inserir a senha
const int ldrPin = A0; // Pino analógico onde o sensor LDR está conectado

int ldrValue; // Variável para armazenar o valor lido do sensor LDR
int countdownValue = 20; // Contagem regressiva de 20 segundos
bool countdownActive = false; // Flag para indicar se a contagem regressiva está ativa

const int passwordLength = 6; // Comprimento da senha
const int correctPassword[passwordLength] = {1, 1, 1, 1, 1, 1}; // Substitua pelos dígitos da senha correta
int enteredPassword[passwordLength];
int currentIndex = 0;
bool passwordEntered = false;

unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
unsigned long lastDebounceTime3 = 0;
unsigned long debounceDelay = 50;


bool buttonState = LOW;

void setup() {
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(confirmPin, INPUT_PULLUP);
  pinMode(ledCorrectPin, OUTPUT);
  pinMode(ledEnterPassword, OUTPUT);
  pinMode(ldrPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  ldrValue = analogRead(ldrPin); // Lê o valor do sensor LDR

  if (ldrValue < 200) {
    if (!passwordEntered) {
      checkButtonDebounced(buttonPin1, 1, lastDebounceTime1);
      checkButtonDebounced(buttonPin2, 2, lastDebounceTime2);
      checkButtonDebounced(buttonPin3, 3, lastDebounceTime3);

      if (digitalRead(confirmPin) == HIGH && !passwordEntered) {
        checkPassword();
      }
    }

    if (!passwordEntered && !countdownActive) {
      startCountdown();
    }
  }

  if (countdownActive) {
    updateCountdown();
    
    // Verifica se a senha foi inserida com sucesso e interrompe a contagem regressiva
    if (passwordEntered) {
      countdownActive = false;
      digitalWrite(ledEnterPassword, LOW); // Apaga o LED após a contagem regressiva
    }
  }

  // Aguarda um breve intervalo antes de fazer a próxima leitura
  delay(1000); // Alterado para 1000 ms (1 segundo)
}

void checkButtonDebounced(int pin, int digit, const bool &lastButtonState, unsigned long &lastDebounceTime) {
  int reading = digitalRead(pin);
  static bool buttonState = LOW; // Adicione esta linha para definir buttonState como uma variável estática

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        // O botão foi pressionado, faça alguma ação aqui
        Serial.print("Botão ");
        Serial.print(digit);
        Serial.println(" pressionado.");
        enteredPassword[currentIndex] = digit;
        currentIndex = (currentIndex + 1) % passwordLength;
      }
    }
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
    digitalWrite(ledEnterPassword, LOW);
    passwordEntered = true;
  } else {
    digitalWrite(ledCorrectPin, LOW);
    digitalWrite(ledEnterPassword, LOW);
    delay(1000); // Pisca o LED de senha incorreta por 1 segundo
    digitalWrite(ledEnterPassword, HIGH);
    clearEnteredPassword();
  }
}

void startCountdown() {
  countdownActive = true;
}

void updateCountdown() {
  if (countdownValue > 0) {
    Serial.println(countdownValue);
    countdownValue--;
    digitalWrite(ledEnterPassword, HIGH); // Acende o LED durante a contagem regressiva
  } else {
    countdownActive = false;
    digitalWrite(ledEnterPassword, LOW); // Apaga o LED após a contagem regressiva
  }
}

void clearEnteredPassword() {
  for (int i = 0; i < passwordLength; i++) {
    enteredPassword[i] = 0;
  }
  currentIndex = 0;
}
