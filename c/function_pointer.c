
#include <stdio.h>
#define ADD 0
#define SUB 1
#define MUL 2
#define DIV 3
#define MOD 4

typedef int (*fPointer)(int, int);

struct calc_s
{
  int a;
  int b;
  fPointer operator;
};
typedef struct calc_s calc_t;

int fAdd(int a, int b);
int fSub(int a, int b);
int fMul(int a, int b);
int fDiv(int a, int b);
int fMod(int a, int b);

int calc_do(calc_t *calc, int operator, int a, int b);

int main (void)
{
  calc_t calc;

  calc_do(&calc, ADD, 10, 5);
  calc_do(&calc, SUB, 10, 5);
  calc_do(&calc, MUL, 10, 5);
  calc_do(&calc, DIV, 10, 5);
  calc_do(&calc, MOD, 10, 5);

  return 0;
}

int calc_do(calc_t *calc, int operator, int a, int b)
{
  calc->a = a;
  calc->b = b;

  switch (operator) {
    case ADD:
      calc->operator = fAdd;
      printf("add = ");
      break;
    case SUB:
      calc->operator = fSub;
      printf("sub = ");
      break;
    case MUL:
      calc->operator = fMul;
      printf("mul = ");
      break;
    case DIV:
      calc->operator = fDiv;
      printf("div = ");
      break;
    case MOD:
      calc->operator = fMod;
      printf("mod = ");
      break;
    default:
      printf("error !\n");
      return 0;
  }

  printf("%d\n", calc->operator(a, b));

  return 0;
}

int fAdd(int a, int b)
{
  return (a+b);
}

int fSub(int a, int b)
{
  return (a-b);
}

int fMul(int a, int b)
{
  return (a*b);
}

int fDiv(int a, int b)
{
  return (a/b);
}

int fMod(int a, int b)
{
  return (a%b);
}
