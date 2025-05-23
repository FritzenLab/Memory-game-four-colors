#define redled D0
#define greenled D1
#define blueled D2
#define yellowled D3

#define redbutton D4
#define greenbutton D5
#define bluebutton D6
#define yellowbutton D7

void setup() {
  // put your setup code here, to run once:
  pinMode(redled, OUTPUT);
  pinMode(greenled, OUTPUT);
  pinMode(blueled, OUTPUT);
  pinMode(yellowled, OUTPUT);
  pinMode(redbutton, INPUT);
  pinMode(greenbutton, INPUT);
  pinMode(bluebutton, INPUT);
  pinMode(yellowbutton, INPUT);
}

void loop() {
  bool defineSequence; // Whether to pick lights sequence or not (at the beginning of the game)
  int level; // game level control variable (1-10?)
  char state; // Char with text "won", "lost", etc
  int leds[4]= {redled, greenled, blueled, yellowled};
  int buttons[4]= {redbutton, greenbutton, bluebutton, yellowbutton};

  gameState(defineSequence, level, state);
  turnLedsOn(defineSequence, level); // show me the lights
  readButtons(buttons); // keep reading buttons searching for user sequence

}
// create lights sequence
void turnLedsOn(bool defineSequence, int level){
  int sequence[10];
  if(defineSequence == true){
    for(int i = 0; i == level; i++){
      sequence[i]= random(1, 4);
    }
    defineSequence= false; // once sequence of blinks is defined, does not enter here anymore
  }

}
void readButtons(int buttons[], bool buttonsState[]){
  bool buttonsState[4];
  long delayTime;

  if(millis() - delayTime > 400){ // button debounce
    for(int j= 0; j== 4; j++){
      if(digitalRead(buttons[j]) == 1){
        buttonsState[j]= true;
        delayTime= millis();
        break;
      }
    }
  }
  
   
}
void gameState(bool defineSequence, int level, char state){


}