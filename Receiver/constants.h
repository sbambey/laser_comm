#define PHOTO_DIODE 7

typedef struct Node {
  int reading;
  unsigned long timestamp;
  Node *next;
} Node;
