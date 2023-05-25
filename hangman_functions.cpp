
#include "hangman_functions.h"
#include <stdlib.h>
#include <ArduinoSTL.h>
#include <iostream>
#include<string>
#include <list>
using namespace std;


extern String wrong_list[7];
extern int num_wrong;
extern String chosen_word;
extern int hangman_state;
String current_letter;
extern String guessed[20];
extern int j;

/*String get_guess() {
  String guess;
   cout << "Guess a letter! ";
    cin >> guess;
  return guess;
}*/

void hangman_round(String guess) {
  int len = chosen_word.length();
  num_wrong = 0;
   //String guess = get_guess();
   //String guessed[len];
   for(j = 0; j < len; j++) {
       current_letter = chosen_word[j];
       if (guess == current_letter) { //chosen_word[j]
           guessed[j] = guess;
       }
       else {
           num_wrong++;
       }
   }
   if (num_wrong >= len) {
        wrong_list[j] = guess;
        hangman_state++;
   }
   //return hangman_state;
}
