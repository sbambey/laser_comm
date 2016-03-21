#define PHOTO_DIODE 7

#define CORRECTION_OFFSET 48

typedef struct Node {
  int reading;
  unsigned long timestamp;
  Node *next;
} Node;
