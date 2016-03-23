#include "constants.h"
#include "Arduino.h"
#include "send.h"

unsigned long last_timestamp;
unsigned long current_timestamp;

byte current_signal;
byte received = 0;
int shift_counter = 0;

String rec = "";
boolean active = 0;

String character = "This is a really long string so that we can test this god damn software. Yep i'm still typing because it's not long enough. Just one more sentence is all he says, but i'm not done yet! AHA! This is the last one!";
char characters[400];

Node *root;
Node *current;

void free_list() {
  Node *node = root;
  while(node) {
    Node *temp = node;
    node = temp->next;
    free(temp);
  }
  root = 0;
}

/* PIN 53 */
void setup() {
  Serial.begin(9600);
  DDRB = B00000000;

  last_timestamp = micros();
}

void loop() {

  while((PINB & B00000001) == current_signal) {
    if(Serial.available() > 0) {
      String transfer_string = Serial.readString();

      transfer_string.toCharArray(characters,400);

      for(int i=0; i<transfer_string.length(); i++) {
        String binary_char = charactersToBinary(String(characters[i]));
        for(int j=0; j<8;j++) {
          if(binary_char.charAt(j) == '1') {
            PORTB |= _BV(0);
            delayCycle();
          }
          else {
            PORTB &= ~(_BV(0));
            delayCycle();
          }
        }
      }
    }
  }
  
  int multiplier;
  
  current_timestamp = micros();
  
  if(current_signal == 1) {
    //Serial.print("1: ");Serial.println(current_timestamp-last_timestamp);
    multiplier = ((current_timestamp-last_timestamp-CORRECTION_OFFSET)/1000);
  }
  else {
    //Serial.print("0: ");Serial.println(current_timestamp-last_timestamp);
    multiplier = ((current_timestamp-last_timestamp+CORRECTION_OFFSET)/1000);
  }
  //Serial.println(multiplier);
  //Serial.println(current_signal);
  if(multiplier < 9) {
    for(int i=0; i<multiplier; i++) {
      received = received << 1;
      received |= current_signal;
      
      shift_counter++;

      //Serial.println(shift_counter);
      
      if(!active && received == B11000101) {
        active = 1;
        shift_counter = 0;
        Serial.println("Message start");
      }
      
      if(shift_counter == 8) {
        //Serial.println(received);
        if(active && received == B11000101) {
          active = 0;
          Serial.println("Message end");
          Serial.println(rec);
          rec = "";
          delay(1000);
        }
        else if(active) {
          rec += String((char)received);
        }
        shift_counter = 0;
      }
    }
  }
  
  current_signal = (PINB & B00000001);
  last_timestamp = current_timestamp;    



  
  /*root = (Node *)malloc(sizeof(Node));
  current = root;
  
  current->reading = (PINB & B00000001);
  current->timestamp = micros();
  current->next = 0;

  last_timestamp = current->timestamp;  
  
  while(true) {
    while((PINB & B00000001) == current->reading);
      current->next = (Node *)malloc(sizeof(Node));
      current = current->next;
      current->reading = (PINB & B00000001);
      current->timestamp = micros();
      current->next = 0;

      if(current->timestamp-last_timestamp > 50000) break;

      last_timestamp = current->timestamp;
  }
  
  current = root;
  last_timestamp = current->timestamp;
  
  while(current->next != 0) {
    current = current->next;
    Serial.print(current->reading);Serial.print(": ");Serial.println(current->timestamp-last_timestamp);
    last_timestamp = current->timestamp;
  }
  
  Serial.println("-----------");
  free_list();*/
}
