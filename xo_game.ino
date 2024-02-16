
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
    Serial.print("Player ");
    Serial.print((currentPlayer == 'X') ? "1" : "2");
    Serial.println(" wins!");
    delay(5000);
    endGame();
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
   if (digitalWrite(redPins[13], HIGH && digitalWrite(redPins[10], HIGH && digitalWrite(redPins[7], HIGH){
     Serial.print(" RED WINS ");
  }
  else if(digitalWrite(redPins[4], HIGH && digitalWrite(redPins[14], HIGH && digitalWrite(redPins[17], HIGH){
    Serial.print(" RED WINS ");
  }
  else if(digitalWrite(redPins[20], HIGH && digitalWrite(redPins[23], HIGH && digitalWrite(redPins[26], HIGH){
    Serial.print(" RED WINS ");
  }

}
/*

bool checkRow(int row) {

  return (buttonState[row * 3] == 1 && buttonState[row * 3 + 1] == 1 && buttonState[row * 3 + 2] == 1);
}

bool checkColumn(int col) {
  return (buttonState[col] == 1 && buttonState[col + 3] == 1 && buttonState[col + 6] == 1);
}

bool checkDiagonal(int a, int b, int c) {
  return (buttonState[a] == 1 && buttonState[b] == 1 && buttonState[c] == 1);
}*/


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
  // Additional reset logic can go here "i try to make the green light for win befor reseting, but i am out of pins :( "
  while (true) {
    
  }
}

