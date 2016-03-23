#define CYCLE 1000
#define CORRECTION_OFFSET 48

typedef struct Node {
  int reading;
  unsigned long timestamp;
  Node *next;
} Node;
