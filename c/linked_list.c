
#include <stdio.h>
#include <stdlib.h>

struct node_s {
  int data;
  struct node_s *next;
};

typedef struct node_s node_t;

int display(node_t *node);
int destroy(node_t *node);
node_t *insert(node_t *node, int data);
node_t *reverse(node_t *node);

int main ()
{
  node_t *node = 0;

  node = insert(node, 5);
  node = insert(node, 7);
  node = insert(node, 2);
  node = insert(node, 4);
  node = insert(node, 9);
  display(node);

  node = reverse(node);
  display(node);

  destroy(node);

  printf("\n");

  return 0;
}

node_t *reverse(node_t *node)
{
  node_t *right = 0;
  node_t *left = 0;
  node_t *mid = 0;

  printf("\nreversing ... ");

  if (!node) return 0;
  if (!node->next) return node;

  left = node;
  mid = node->next;
  node->next = 0;

  while(mid) {
    right = mid->next;
    mid->next = left;
    left = mid;
    mid = right;
  }

  return left;
}

node_t *insert(node_t *node, int data)
{
  node_t *lastNode = 0;
  node_t *newNode = 0;
  node_t *curNode = node;

  printf("\ninserting ... ");

  newNode = (node_t*)malloc(sizeof(node_t));
  newNode->data = data;
  newNode->next = 0;

  if (!curNode) {
    node = newNode;
  }
  else {
    while(curNode) {
      lastNode = curNode;
      curNode = curNode->next;
    }
    lastNode->next = newNode;
  }

  return node;
}

int destroy(node_t *node)
{
  node_t *tmp = 0;

  printf("\ndestroying ...");

  while(node) {
    tmp = node->next;
    free(node);
    node = tmp;
  }

  return 0;
}

int display(node_t *node)
{
  printf("\nlist ... ");
  while(node) {
    printf("%d, ", node->data);
    node = node->next;
  }


  return 0;
}
