#define PHOTO_DIODE 7

typedef struct Node {
  int reading;
  unsigned long timing;
  Node *next;
} Node;
