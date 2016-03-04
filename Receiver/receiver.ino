#include "constants.h"
#include "digitalWriteFast.h"

unsigned long last_time;
unsigned long current_time;

int last_state = 0;
int state = 0;

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

void setup() {
  Serial.begin(9600);
  DDRB = B00000000;
}

void loop() {

  if(!root) {
    root = (Node *)malloc(sizeof(Node));
    root->next = 0;
    current = root;
    current->reading = ~(PINB & B1);
  }
  
  last_time=micros();
  
  for(int i=0; i<100; i++) {
    while((~PINB & B00000001) == current->reading);
    current->next = (Node *)malloc(sizeof(Node));
    current = current->next;
    current->next = 0;
    current->reading = (~PINB & B00000001);
    current_time = micros();
    current->timing = current_time-last_time;
    last_time = current_time;
  }

  current = root;
  while(current->next != 0) {
    Serial.println(current->timing);
    current = current->next;
  }
  Serial.println("-----------");

  free_list();
}
