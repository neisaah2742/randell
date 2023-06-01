#include "hangman_functions.h"
#include <Servo.h>
Servo frontLeft;  // create servo object to control a servo
Servo backLeft;
Servo frontRight;
Servo backRight;
Servo jaw;
Servo tail;
int pos = 0;    // variable to store the servo position


String wrong_list[7];
int num_wrong = 0;
String chosen_word = " ";
int hangman_state = 0;
String guessed[20];
int rand_int;
bool entered;

String alphabet = "abcdefghijklmnopqrstuvwxyz";
//String alphabet[26] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"}

String hangman_image[7] = {
  " ________\n |      |\n        |\n        |\n        |\n        |\n        |\n        |\n  ___________",
  
  " ________\n |      |\n|_|     |\n        |\n        |\n        |\n        |\n        |\n  ___________",
  
  " ________\n |      |\n|_|     |\n |      |\n |      |\n        |\n        |\n        |\n  ___________",
  
  " ________\n |       |\n|_|      |\n |_      |\n |       |\n         |\n         |\n         |\n  ___________",
  
  " ________\n |       |\n|_|      |\n_|_      |\n |       |\n         |\n         |\n         |\n   ___________",
  
  " ________\n |       |\n|_|      |\n_|_      |\n |       |\n/        |\n         |\n         |\n   ___________",
 
  " ________\n |       |\n|_|      |\n_|_      |\n |       |\n/ |      |\n         |\n        |\n  ____________\n"};

String words[213] = {"abruptly","absurd","abyss","affix","askew","avenue","awkward","axiom","azure","bagpipes","bandwagon","banjo","bayou","beekeeper","bikini","blitz","blizzard","boggle","bookworm","boxcar","boxful","buckaroo","buffalo","buffoon","buxom","buzzard","buzzing","buzzwords","caliph","cobweb","cockiness","croquet","crypt","curacao","cycle","daiquiri","dirndl","disavow","dizzying","duplex","dwarves","embezzle","equip","espionage","euouae","exodus","faking","fishhook","fixable","fjord","flapjack","flopping","fluffiness","flyby","foxglove","frazzled","frizzled","fuchsia","funny","gabby","galaxy","galvanize","gazebo","giaour","gizmo","glowworm","glyph","gnarly","gnostic","gossip","grogginess","haiku","haphazard","hyphen","iatrogenic","icebox","injury","ivory","ivy","jackpot","jaundice","jawbreaker","jaywalk","jazziest","jazzy","jelly","jigsaw","jinx","jiujitsu","jockey","jogging","joking","jovial","joyful","juicy","jukebox","jumbo","kayak","kazoo","keyhole","khaki","kilobyte","kiosk","kitsch","kiwifruit","klutz","knapsack","larynx","lengths","lucky","luxury","lymph","marquis","matrix","megahertz","microwave","mnemonic","mystify","naphtha","nightclub","nowadays","numbskull","nymph","onyx","ovary","oxidize","oxygen","pajama","peekaboo","phlegm","pixel","pizazz","pneumonia","polka","pshaw","psyche","puppy","puzzling","quartz","queue","quips","quixotic","quiz","quizzes","quorum","razzmatazz","rhubarb","rhythm","rickshaw","schnapps","scratch","shiv","snazzy","sphinx","spritz","squawk","staff","strength","strengths","stretch","stronghold","stymied","subway","swivel","syndrome","thriftless","thumbscrew","topaz","transcript","transgress","transplant","triphthong","twelfth","twelfths","unknown","unworthy","unzip","uptown","vaporize","vixen","vodka","voodoo","vortex","voyeurism","walkway","waltz","wave","wavy","waxy","wellspring","wheezy","whiskey","whizzing","whomever","wimpy","witchcraft","wizard","woozy","wristwatch","wyvern","xylophone","yachtsman","yippee","yoked","youthful","yummy","zephyr","zigzag","zigzagging","zilch","zipper","zodiac","zombie"};


int rand_index() {
  int randint = random(sizeof(words));
  return randint;
}

String get_guess(){
    Serial.println("Guess a letter!");
    while (Serial.available() == 0) {
    }
    String user_guess;
    user_guess = Serial.readString();
    for (int i = 0; i < 26; i++) {
      String letter = String(alphabet[i]);
      if (user_guess.indexOf(letter) != -1) {
        user_guess = letter;
      }
    }
    return user_guess;
}

void game_start(int index) {
  chosen_word = String(words[index]);
  for(int i = 0; i < int(chosen_word.length()); i++) {
    String holder = " _ ";
       guessed[i] = holder;
       //chosen_list[i] = chosen_word[i];
   }
   for(int i = 0; i < 7; i++) {
    String holder = " ";
    wrong_list[i] = holder;
   }
   Serial.println(hangman_image[hangman_state]);
  for (int k=0; k < sizeof(chosen_word); k++) {
     Serial.print(guessed[k]);   
  }
}

void play_hangman() {

  String guess = get_guess();
  hangman_round(guess);
  Serial.println(hangman_image[hangman_state]);

  if (hangman_state == 6) {
    Serial.println("The word was " + String(chosen_word));
    return;
  }
}

// the setup routine runs once when you press reset:
void setup() {
  frontLeft.attach(3);  // attaches the servo on pin 3 to the servo object
  backLeft.attach(5);
  frontRight.attach(6);
  backRight.attach(9);
  tail.attach(10);
  jaw.attach(11);
  Serial.begin(9600);
  rand_int = rand_index();
  game_start(rand_int);
  //Serial.println(get_guess());
}

void loop() {

  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    frontLeft.write(pos);  // tell servo to go to position in variable 'pos'
    backLeft.write(pos);
    frontRight.write(pos);
    backRight.write(pos);
    if (pos < 90) {
      tail.write(pos);
      if (pos < 45) {
      jaw.write(pos);
      }
    }
    delay(5);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    frontLeft.write(pos);  // tell servo to go to position in variable 'pos'
    backLeft.write(pos);
    frontRight.write(pos);
    backRight.write(pos);
    if (pos > 90) {
      tail.write(pos);
      if (pos < 45) {
        jaw.write(pos);
      }
    }
    delay(5);                       // waits 15 ms for the servo to reach the position
  }
  play_hangman();
  Serial.print("\n Letters you've guessed wrong: ");
  for (int p = 0; p < 7; p++) {
    Serial.print(wrong_list[p] + " ");
  }
  Serial.print("\n Word so far: ");
  for (int q = 0; q < int(chosen_word.length()); q++) {
    Serial.print(guessed[q] + " ");
  }
  Serial.print("\n");
}
