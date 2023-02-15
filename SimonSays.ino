const int ledGreen = 13;
const int ledYellow = 12;
const int ledBlue = 11;
const int ledRed = 10;

const int buttonGreen = 2;
const int buttonYellow = 3;
const int buttonBlue = 4;
const int buttonRed = 5;

const int buttonStart = 6;

int roundNumber = 1;
int userMoveNumberArray = 0;

bool showSequence = true;

int buttonGreenState = 0;
int buttonYellowState = 0;
int buttonBlueState = 0;
int buttonRedState = 0;
int buttonStartState = 0;

const int gameLength = 3;

int simonSequence[gameLength];
int userSequence[gameLength];

int numberToLedName(int number){
  switch (number) {
    case 0: 
    return ledGreen;
    break;

    case 1: 
    return ledYellow;
    break;

    case 2: 
    return ledBlue;
    break;

    case 3: 
    return ledRed;
    break;
  }
}

int getRandomLed()
{
  int randomNumber = random(4);
  return numberToLedName(randomNumber);
}

void startLightSequence() 
{
  for (int i = 0; i < 3; i++)
  {
    digitalWrite(ledGreen, HIGH);
    delay(75);
    digitalWrite(ledYellow, HIGH);
    delay(75);
    digitalWrite(ledBlue, HIGH);
    delay(75);
    digitalWrite(ledRed, HIGH);
    delay(75);
    digitalWrite(ledGreen, LOW);
    delay(75);
    digitalWrite(ledYellow, LOW);
    delay(75);
    digitalWrite(ledBlue, LOW);
    delay(75);
    digitalWrite(ledRed, LOW);
    }
}

void endLightSequence(){
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledYellow, HIGH);
    digitalWrite(ledBlue, HIGH);
    digitalWrite(ledRed, HIGH);
    delay(1500);
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledBlue, LOW);
    digitalWrite(ledRed, LOW);
    delay(500);
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledYellow, HIGH);
    digitalWrite(ledBlue, HIGH);
    digitalWrite(ledRed, HIGH);
    delay(1500);
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledBlue, LOW);
    digitalWrite(ledRed, LOW);
    delay(500);
}

void winLightSequence() 
{
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(ledGreen, HIGH);
    delay(30);
    digitalWrite(ledYellow, HIGH);
    delay(30);
    digitalWrite(ledBlue, HIGH);
    delay(30);
    digitalWrite(ledRed, HIGH);
    delay(30);
    digitalWrite(ledGreen, LOW);
    delay(30);
    digitalWrite(ledYellow, LOW);
    delay(30);
    digitalWrite(ledBlue, LOW);
    delay(30);
    digitalWrite(ledRed, LOW);
    }
    delay(500);
}

void resetGame()
{
  for (int i = 0; i < gameLength - 1; i++)
  {
    simonSequence[i] = 0;
    userSequence[i] = 0;
  }
  simonSequence[0] = getRandomLed();
  userMoveNumberArray = 0;
  showSequence = true;
  startLightSequence();
  roundNumber = 1;
}

void addSimonSequence(){
 simonSequence[roundNumber] = getRandomLed();
}

void checkUserSequence() {
  if(simonSequence[userMoveNumberArray] != userSequence[userMoveNumberArray]){
      endLightSequence();
      resetGame();
  } else {
    userMoveNumberArray++;
  }
}

void setup() {
 pinMode(ledGreen, OUTPUT);
 pinMode(ledYellow, OUTPUT);
 pinMode(ledBlue, OUTPUT);
 pinMode(ledRed, OUTPUT);

 pinMode(buttonGreen, INPUT);
 pinMode(buttonYellow, INPUT);
 pinMode(buttonBlue, INPUT);
 pinMode(buttonRed, INPUT);
 pinMode(buttonStart, INPUT);

 resetGame();
}

void loop() {

  buttonGreenState = digitalRead(buttonGreen);
  buttonYellowState = digitalRead(buttonYellow);
  buttonBlueState = digitalRead(buttonBlue);
  buttonRedState = digitalRead(buttonRed);
  buttonStartState = digitalRead(buttonStart);

  if(buttonStartState == HIGH) {
    resetGame();
  }

  if(showSequence){
    delay(500);
    for(int i = 0; i < roundNumber; i++){  
      digitalWrite(simonSequence[i], HIGH);
      delay(500);
      digitalWrite(simonSequence[i], LOW);
      delay(500);
      showSequence = false;
    }
  }

  if(buttonGreenState == HIGH){
    userSequence[userMoveNumberArray] = ledGreen;
    digitalWrite(ledGreen, HIGH);
    delay(500);
    digitalWrite(ledGreen, LOW);
    checkUserSequence();
  }

  if(buttonYellowState == HIGH){
    userSequence[userMoveNumberArray] = ledYellow;
    digitalWrite(ledYellow, HIGH);
    delay(500);
    digitalWrite(ledYellow, LOW);
    checkUserSequence();
  }

  if(buttonBlueState == HIGH){
    userSequence[userMoveNumberArray] = ledBlue;
    digitalWrite(ledBlue, HIGH);
    delay(500);
    digitalWrite(ledBlue, LOW);
    checkUserSequence();
  }

  if(buttonRedState == HIGH){
    userSequence[userMoveNumberArray] = ledRed;
    digitalWrite(ledRed, HIGH);
    delay(500);
    digitalWrite(ledRed, LOW);
    checkUserSequence();
  }

  if(userMoveNumberArray == roundNumber){
      userMoveNumberArray = 0;
      addSimonSequence();
      roundNumber++;
      showSequence = true;
  }

  if(roundNumber == gameLength + 1){
      winLightSequence();
      resetGame();
  }
}

