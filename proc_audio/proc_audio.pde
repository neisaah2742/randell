import processing.serial.*;
import ddf.minim.*;


PFont f;
String typing = "";
String saved = "";
Serial myPort;
Minim minim;
AudioPlayer player;
byte arbitraryCode = 97;
String[] phrases = {
  "Berkeley High School.mp3", 
  "You're overreacting.mp3", 
  "You have such an active imagination.mp3", 
  "That never happened.mp3", 
  "I think you need professional help.mp3", 
  "I don't know what you want me to say.mp3"
};
int index = int(random(phrases.length));
String myText;
 
void setup()
{
  size(480, 270);
  f = createFont("Arial",16);
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
  minim = new Minim(this);
 
  // Put in the name of your sound file below, and make sure it is in the same directory
  String random_phrase = phrases[index];
  player = minim.loadFile(random_phrase);
}

/*boolean saved() {
  if (saved == typing) {
    return true;
  }
 return false;
}*/

 void respond() {
   while (myPort.available() > 0) { 
    int inByte = myPort.read();
    if (inByte == arbitraryCode) {
        player.rewind();
        player.play();
    }
  }
 }
 
void draw() {
  background(255);
  int indent = 25;
  
  textFont(f);
  fill(0);
  //delay(1000);
  text("Click in this window and type", indent, 40);
  text("What do you want to tell randell: " + typing,indent,190);
  text("Saved text: " + saved,indent,230);
  if (typing != "") {
    respond();
  }
}

void keyPressed() {
  // If the return key is pressed, save the String and clear it
  if (key == '\n' ) {
    saved = typing;
    // A String can be cleared by setting it equal to ""
    typing = "";
  } else {
    // Otherwise, concatenate the String
    // Each character typed by the user is added to the end of the String variable.
    typing = typing + key; 
  }
}
