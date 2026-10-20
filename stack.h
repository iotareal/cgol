#ifndef STACK_H
#define STACK_H
#include <stdint.h>
#include "cell.h"

typedef struct{
    Cell* cell_arr;
    long long cap;
    long long top;
}Stack;

void init(Stack* s, long long capacity);
void push(Stack* s, Cell* cell);
Cell* pop(Stack* s);

#endif