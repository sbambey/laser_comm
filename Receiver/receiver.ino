#include "constants.h"

unsigned long last_timestamp;

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

  /*String send_s = "Hi Simon";

  int send_l = send_s.length();

  Serial.println(send_l);

  for(int i=0; i<send_l; i++) {
    for(int j=0; j<8; j++) {
      Serial.print((send_s.charAt(i) & (B10000000 >> j)) >> (7-j));
    }
  }

  delay(5000);*/

  /*Serial.print("Logic: ");
  Serial.println(PINB & B00000001);*/
  Serial.println("ready");
  while((PINB & B00000001) != 1);

  last_timestamp = micros();

  while((PINB & B00000001) == 1);

  if(micros()-last_timestamp > 200000) {
    
    root = (Node *)malloc(sizeof(Node));
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

      if(current->timestamp-last_timestamp > 500000) break;

      last_timestamp = current->timestamp;
    }
    
    current = root;
    last_timestamp = current->timestamp;
    while(current->next != 0) {
      current = current->next;
      //Serial.println(current->reading);
      int val;
      if(current->reading == 1) {
        //Serial.println(current->timestamp-last_timestamp);
        val = (((current->timestamp-last_timestamp-50)/2000)+1);
      }
      else {
        val = ((current->timestamp-last_timestamp+50)/2000);
      }
      //Serial.println(val);
      for(int i=0; i<val; i++) {
        bit_string += String(current->reading);
      }
      last_timestamp = current->timestamp;
    }
    Serial.print("Bit String: ");Serial.println(bit_string);
    bit_string="";
    last_timestamp = 0;
    
  
    free_list();
  Serial.println("-----------");
    //delay(20000);
  }
}
