#define redled D0
#define greenled D1
#define blueled D2
#define yellowled D3

#define redbutton D4
#define greenbutton D5
#define bluebutton D6
#define yellowbutton D7

bool defineSequence = true; // Whether to pick lights sequence or not (at the beginning of the game)
int level = 1;              // Game level control variable
char state[] = "play";      // "won", "lost", etc.
int leds[4] = {redled, greenled, blueled, yellowled};
int buttons[4] = {redbutton, greenbutton, bluebutton, yellowbutton};
bool buttonState[4];

struct GameResult {
  bool defineSequence;
  int level;
};

void setup() {
  pinMode(redled, OUTPUT);
  pinMode(greenled, OUTPUT);
  pinMode(blueled, OUTPUT);
  pinMode(yellowled, OUTPUT);
  pinMode(redbutton, INPUT);
  pinMode(greenbutton, INPUT);
  pinMode(bluebutton, INPUT);
  pinMode(yellowbutton, INPUT);

  Serial.begin(115200);
}

// 🧠 Declare your functions BEFORE using them
GameResult gameState(bool defineSequence, int level, char* state);
void turnLedsOn(bool defineSequence, int level, int leds[]);
void readButtons(int buttons[], bool buttonState[]);

void loop() {
  delay(1000);
  GameResult result = gameState(defineSequence, level, state);
  defineSequence = result.defineSequence;
  level = result.level;

  delay(1000);
  turnLedsOn(defineSequence, level, leds); // ✅ No brackets like leds[]
  delay(1000);
  readButtons(buttons, buttonState);       // ✅ Same here
}

// 💡 Create lights sequence
void turnLedsOn(bool defineSequence, int level, int leds[]) {
  static int sequence[10];
  static long ledTime = 0;
  static bool anotherHalf = false;
  static int sequenceControl = 0;

  if (level == 1) {
    defineSequence = true;
    anotherHalf = true;
  }

  if (defineSequence == true) {
    for (int i = 0; i < level; i++) {
      sequence[i] = random(0, 4);
    }
    defineSequence = false;
  }

  if (millis() - ledTime > 200) { // essentially every 200ms I will do something with the LEDs
    if (anotherHalf == false) { // "anotherHalf" takes care of LED blinking (goes between true and false every 200ms)
      ledTime = millis();
      digitalWrite(leds[sequence[sequenceControl]], HIGH);
      Serial.println("LED ON");
      anotherHalf = true;
    } else {
      ledTime= millis();
      digitalWrite(leds[sequence[sequenceControl]], LOW);
      sequenceControl++;
      if (sequenceControl >= level) {
        sequenceControl = 0;
       Serial.println("Reset of sequenceControl");
      }
      anotherHalf = false;
    }
  }
}

void readButtons(int buttons[], bool buttonsState[]) {
  static long delayTime = 0;

  if (millis() - delayTime > 400) { // every 400ms reads all four buttons
    for (int j = 0; j < 4; j++) {  
      if (digitalRead(buttons[j]) == HIGH) { // if a given button is HIGH
        buttonsState[j] = true;               // gives the buttonState of said button a "true"
        break;
      }else{
        buttonsState[j] = false; // if button reading returns LOW, gives its buttonState a "false"
      }
    }
    delayTime = millis();
  }
}

GameResult gameState(bool defineSequence, int level, char* state) {
  static bool defineLevel = true;

  if (level == 1 && strcmp(state, "lost") == 0 && defineLevel == true) {
    level = 1;
  } else if (strcmp(state, "lost") != 0 && defineLevel == true) {
    level++;
  } else if (strcmp(state, "lost") == 0) {
    level = 1;
    defineSequence = true;
  }

  GameResult result = {defineSequence, level};
  return result;
}
