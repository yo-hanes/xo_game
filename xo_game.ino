
void makeMove(int index);
void turnOffAllLEDs();
bool checkForWin();
bool checkForDraw();
void endGame();

const int redPins[9] = {13, 10, 7, 4, 14, 17, 20, 23, 26};
const int greenPins[9] = {12, 9, 6, 3, 15, 18, 21, 24, 27};
const int bluePins[9] = {11, 8, 5, 2, 16, 19, 22, 25, 28};
const int buttonPins[9] = {33, 36, 39, 34, 37, 40, 35, 38, 41};

char currentPlayer = 'X';
int buttonState[9] = {0};

void setup() {
  Serial.begin(9600); 
  for (int i = 0; i < 9; i++) {
    pinMode(redPins[i], OUTPUT);
    pinMode(greenPins[i], OUTPUT);
    pinMode(bluePins[i], OUTPUT);
  }

  for (int i = 0; i < 9; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  Serial.println("Game Start!");
  Serial.println("Player 1 (Red) goes first.");
}

void loop() {
  for (int i = 0; i < 9; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      makeMove(i);
    }
  }

  if (checkForWin()) {

 if ((digitalRead(redPins[13]) == HIGH && digitalRead(redPins[10]) == HIGH && digitalRead(redPins[7]) == HIGH) ||  // First row
      (digitalRead(redPins[4]) == HIGH && digitalRead(redPins[14]) == HIGH && digitalRead(redPins[17]) == HIGH) ||  // Second row
      (digitalRead(redPins[20]) == HIGH && digitalRead(redPins[23]) == HIGH && digitalRead(redPins[26]) == HIGH) ||  // Third row
      (digitalRead(redPins[13]) == HIGH && digitalRead(redPins[4]) == HIGH && digitalRead(redPins[20]) == HIGH) ||  // First column
      (digitalRead(redPins[10]) == HIGH && digitalRead(redPins[14]) == HIGH && digitalRead(redPins[23]) == HIGH) ||  // Second column
      (digitalRead(redPins[7]) == HIGH && digitalRead(redPins[17]) == HIGH && digitalRead(redPins[26]) == HIGH) ||  // Third column
      (digitalRead(redPins[13]) == HIGH && digitalRead(redPins[14]) == HIGH && digitalRead(redPins[26]) == HIGH) ||  // Diagonal from top-left to bottom-right
      (digitalRead(redPins[7]) == HIGH && digitalRead(redPins[14]) == HIGH && digitalRead(redPins[20]) == HIGH)) {  // Diagonal from top-right to bottom-left
    Serial.println("RED WINS!");
    delay(5000);
    endGame();
  } 
  else if ((digitalRead(greenPins[12]) == HIGH && digitalRead(greenPins[9]) == HIGH && digitalRead(greenPins[6]) == HIGH) ||  // First row
           (digitalRead(greenPins[3]) == HIGH && digitalRead(greenPins[15]) == HIGH && digitalRead(greenPins[18]) == HIGH) ||  // Second row
           (digitalRead(greenPins[21]) == HIGH && digitalRead(greenPins[24]) == HIGH && digitalRead(greenPins[27]) == HIGH) ||  // Third row
           (digitalRead(greenPins[12]) == HIGH && digitalRead(greenPins[3]) == HIGH && digitalRead(greenPins[21]) == HIGH) ||  // First column
           (digitalRead(greenPins[9]) == HIGH && digitalRead(greenPins[15]) == HIGH && digitalRead(greenPins[24]) == HIGH) ||  // Second column
           (digitalRead(greenPins[6]) == HIGH && digitalRead(greenPins[18]) == HIGH && digitalRead(greenPins[27]) == HIGH) ||  // Third column
           (digitalRead(greenPins[13]) == HIGH && digitalRead(greenPins[14]) == HIGH && digitalRead(greenPins[26]) == HIGH) ||  // Diagonal from top-left to bottom-right
           (digitalRead(greenPins[7]) == HIGH && digitalRead(greenPins[14]) == HIGH && digitalRead(greenPins[20]) == HIGH)) {  // Diagonal from top-right to bottom-left
    Serial.println("GREEN WINS!");
    delay(5000);
    endGame();
  } 

  } else if (checkForDraw()) {
    Serial.println("It's a draw!");
    delay(5000);
    endGame();
  }
}

void makeMove(int index) {
  if (buttonState[index] == 1) {
    return; 
  }

  if (currentPlayer == 'X') {
    digitalWrite(redPins[index], HIGH);
  } else {
    digitalWrite(greenPins[index], HIGH);
  }

  buttonState[index] = 1;

  Serial.print("Player ");
  Serial.print((currentPlayer == 'X') ? "1" : "2");
  Serial.println("'s turn.");

  currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';

  delay(200);
}

void turnOffAllLEDs() {
  for (int i = 0; i < 9; i++) {
    digitalWrite(redPins[i], LOW);
    digitalWrite(greenPins[i], LOW);
    digitalWrite(bluePins[i], LOW);
  }
}

bool checkForWin() {
  for (int i = 0; i < 3; i++) {
    if (checkRow(i)) {
      return true;
    }
  }
  for (int i = 0; i < 3; i++) {
    if (checkColumn(i)) {
      return true;
    }
  }

  if (checkDiagonal(0, 4, 8) || checkDiagonal(2, 4, 6)) {
    return true;
  }

  return false;
}

bool checkRow(int row) {
  return (buttonState[row * 3] == 1 && buttonState[row * 3 + 1] == 1 && buttonState[row * 3 + 2] == 1);
}

bool checkColumn(int col) {
  return (buttonState[col] == 1 && buttonState[col + 3] == 1 && buttonState[col + 6] == 1);
}

bool checkDiagonal(int a, int b, int c) {
  return (buttonState[a] == 1 && buttonState[b] == 1 && buttonState[c] == 1);
}


bool checkForDraw() {
  for (int i = 0; i < 9; i++) {
    if (buttonState[i] == 0) {
      return false;
    }
  }
  return true;
}

void turnOnAllLEDs() {
  for (int i = 0; i < 9; i++) {
    digitalWrite(redPins[i], HIGH);
    digitalWrite(greenPins[i], HIGH);
    digitalWrite(bluePins[i], HIGH);
  }
}

void endGame() {
  Serial.println("Game Over!");
  Serial.println("Press the reset button to start a new game.");

  for (int i = 0; i < 3; i++) {
    turnOffAllLEDs();
    delay(500);
    turnOnAllLEDs();
    delay(500);
  }

  turnOffAllLEDs();
  
  while (true) {
    
  }
}

