#define redled 0
#define greenled 1
#define blueled 2
#define yellowled 3

#define redbutton 4
#define greenbutton 5
#define bluebutton 6
#define yellowbutton 7

int leds[4]    = { redled, greenled, blueled, yellowled };
int buttons[4] = { redbutton, greenbutton, bluebutton, yellowbutton };

int sequence[50];      // stores the Simon sequence
int level = 1;         // game starts at level 1
String state = "idle"; // "idle", "play", "input", "won", "lost"
int ledPlayTime= 0;
int countLED= 0;
int passing= 0;

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
    pinMode(buttons[i], INPUT);
  }

  randomSeed(analogRead(A0)); // better random sequences
}

void loop() {

  if (state == "idle") {
    generateSequence();
    state = "play";
  }

  else if (state == "play") {
    playSequence();
    
  }

  else if (state == "input") {
    if (readPlayerInput() == true) {
      level++;
      state = "idle";      // generate next level
    } else if (readPlayerInput() == false) {
      state = "lost";
    }
  }

  else if (state == "lost") {
    resetGame();
  }
}


// --- FUNCTIONS YOU WILL IMPLEMENT ---

void generateSequence() {
  for (int i = 0; i < level; i++) {
    sequence[i] = random(0, 4);
  }
}

void playSequence() {
  if (millis() - ledPlayTime >= 500) {
    ledPlayTime = millis();

    if (passing == 0) {
      // Turn ON the correct LED
      digitalWrite(leds[sequence[countLED]], HIGH);
      passing = 1;
    }
    else {
      // Turn OFF the LED
      digitalWrite(leds[sequence[countLED]], LOW);

      countLED++;
      passing = 0;

      if (countLED > level) {
        countLED = 0;
        state = "input";
      }
    }
  }
}


bool readPlayerInput() {
  // TODO: wait for button presses & compare with sequence[]

  return false; // or false if user makes a mistake
}

void resetGame() {
  level = 1;
  state = "idle";
}
