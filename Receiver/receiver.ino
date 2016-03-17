#include "constants.h"

unsigned long last_timestamp;
unsigned long last_timestamp1;
unsigned long current_timestamp;

byte current_signal;
unsigned short received = 0;

String bit_string = "";

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
}

void loop() {

  /*while((PINB & B00000001) != 1);

  last_timestamp = micros();

  while((PINB & B00000001) == 1);

  last_timestamp1 = micros();

  while((PINB & B00000001) == 0);

  current_timestamp = micros();

  Serial.println(last_timestamp1-last_timestamp);
  Serial.println(current_timestamp-last_timestamp1);*/

  /*current_signal = PINB & B00000001;
  received |= current_signal;*/
  
  last_timestamp = micros();

  while(true) {
    while((PINB & B00000001) == current_signal);
    int val;
    current_timestamp = micros();
    
    //Serial.println(current_timestamp-last_timestamp);
    
    if(current_signal == 1) {
      val = ((current_timestamp-last_timestamp-50)/16000);
    }
    else {
      val = ((current_timestamp-last_timestamp+50)/16000);
    }
    //Serial.println(val);
    //Serial.println(current_signal);
    if(val < 8) {
      for(int i=0; i<val; i++) {
        received = received << 1;
        received |= current_signal;
      }
    }

    if(received & B11000101) Serial.println("Start");
    received = 0;
    
    current_signal = (PINB & B00000001);
    last_timestamp = current_timestamp;    
  }

  //Serial.println(received);
  
  /*while(true) {
    while((PINB & B00000001) == current_signal) {
      //Serial.println("here");
      if(micros()-last_timestamp > 3000000) break;
    }
    //Serial.println(micros()-last_timestamp);
    if(micros()-last_timestamp > 3000000) break;
    
    /*Serial.println(PINB & B00000001);
    Serial.println(current_signal);
    Serial.println((PINB & B00000001) == current_signal);
    Serial.println("-------");
  
    current_timestamp = micros();
    current_signal = PINB & B00000001;

    int val;
    
    if(current_signal == 1) {
      val = ((current_timestamp-last_timestamp-50)/2000);
    }
    else {
      val = ((current_timestamp-last_timestamp+50)/2000);
    }
  
    for(int i=0; i<val; i++) {
      received = received << val;
      received &= current_signal;
    }
  }

  Serial.println(received);

  received = 0;*/
  
  //delay(5000);

  //Serial.println(micros()-last_timestamp);

  
  /*String send_s = "Hi Simon";

  int send_l = send_s.length();

  Serial.println(send_l);

  for(int i=0; i<send_l; i++) {
    for(int j=0; j<8; j++) {
      Serial.print((send_s.charAt(i) & (B10000000 >> j)) >> (7-j));
    }
  }

  delay(5000);*/

  //while((PINB & B00000001) != 1);

  //last_timestamp = micros();

  //while((PINB & B00000001) == 1);

  //Serial.println(micros()-last_timestamp);

  //if(micros()-last_timestamp > 200000) {
    
    /*root = (Node *)malloc(sizeof(Node));
    current = root;
    
    current->reading = (PINB & B00000001);
    current->timestamp = micros();
    current->next = 0;

    last_timestamp = current->timestamp;

    

    while(true) {
      while((PINB & B00000001) == current->reading) {
        if(micros()-current->timestamp > 50000) break;
      }
      if((PINB & B00000001) != current->reading) {
        current->next = (Node *)malloc(sizeof(Node));
        current = current->next;
        current->reading = (PINB & B00000001);
        current->timestamp = micros();
        current->next = 0;
        //Serial.println(current->timestamp-last_timestamp);
        Serial.println(current->reading);
        if(current->timestamp-last_timestamp > 50000) break;
  
        last_timestamp = current->timestamp;
      }
    }
    
    current = root;
    last_timestamp = current->timestamp;

    bit_string += String(current->reading);
    
    while(current->next != 0) {
      current = current->next;
      //Serial.println(current->reading);
      
      //Serial.println(val);
      for(int i=0; i<val; i++) {
        bit_string += String(current->reading);
      }
      last_timestamp = current->timestamp;
    }
    //Serial.println();
    Serial.print("Bit String: ");Serial.println(bit_string);
    bit_string="";
    last_timestamp = 0;
    
    Serial.println("-----------");
    free_list();
  
    //delay(20000);
  //}*/
}
