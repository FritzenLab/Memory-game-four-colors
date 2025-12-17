#define redled 5
#define greenled 6
#define blueled 7
#define yellowled 8

#define redbutton 9
#define greenbutton 10
#define bluebutton 20
#define yellowbutton 21

int leds[4]    = { redled, greenled, blueled, yellowled };
int buttons[4] = { redbutton, greenbutton, bluebutton, yellowbutton };

int sequence[50];      // stores the Simon sequence
int level = 10;         // game starts at level 1
int gameStatus = 1; // 1= begin/restart 2= playing 
int buttonState= 0; // variable to read buttons pressing
bool hasShownSequence= false;
bool compareButtonsToLEDs= false;
bool rightOrder= false;
bool hasReadAllButtons= false;
bool hasSelectedRandomSequence= false;
int firstPass= 0;
long showTime= 0;
int interestLED= 0;
int i= 0;
int counterToBlink= 0;

void setup() {
  Serial.begin(115200);

  pinMode(redled, OUTPUT);
  pinMode(greenled, OUTPUT);
  pinMode(blueled, OUTPUT);
  pinMode(yellowled, OUTPUT);
  

  randomSeed(analogRead(A0)); // better random sequences
}

void loop() {

  if(gameStatus == 1){ // if game started or restarted
    showSequence(); // shows lights sequence. This updates "hasShownSequence"
    if(hasShownSequence == true){
      gameStatus= 2; // goes to "playing"
    }
    

  }else if(gameStatus == 2){ // status is "playing"
    if(hasReadAllButtons == false){ // were all expected buttons read?
      readButtons(buttonState); // check for buttons pressing in the right sequence
    }
    
    
    if(compareButtonsToLEDs == true){ // was the comparison LEDs <-> Buttons made?
      if(rightOrder == true){ // if buttons pressed in the right order
        gameStatus= 1; // goes back to showing LEDs sequence
      }else{
        //lostGame(); // shows "lost game" animation . Has to "hasSelectedRandomSequence= false"
        compareButtonsToLEDs= false; // resets the buttons to LEDs comparison
        hasShownSequence= false; // resets the "show LEDs sequence"
      }
    }
  }
}
void showSequence(){
  if(hasSelectedRandomSequence == false){ // if no LED sequence was selected yet
    for(i= 0; i <= level; i++){ // iterates from zero to the present game level
      sequence[i]= random(0, 4);
    }
    hasSelectedRandomSequence = true; // makes sure the sequence is selected only once;
    //counterToBlink= level;
  }
  if(millis() - showTime > 300){
    showTime= millis();
    if(firstPass < 2){ // runs between 0 and 1, or HIGH and LOW of each LED
      digitalWrite(leds[interestLED], !digitalRead(leds[interestLED])); // turn ON and OFF "interestLED", whose position/size depends on "level"
    }else{
      firstPass= 0; // if LED has blink (both ON and OFF), restarts the cycle
      digitalWrite(leds[interestLED], LOW); // makes sure the LEDs are always off at the end of every blinking cycle
      if(counterToBlink <= level){ // if not all LEDs have blink
        interestLED= sequence[counterToBlink]; // the next LED to blink is decided here
        counterToBlink++;
        
      }else{
        hasSelectedRandomSequence= true; // enables next cycle
        hasShownSequence= true; // finishes LED blinking
      }
      
        
      
      
    }
    firstPass++; // makes sure the LED goes ON then OFF

  }  
}