#include "stack.h"
#include <stdlib.h>
// #include <stdlib.h>
void init(Stack* s, long long capacity){
    s->cap = capacity;
    s->cell_arr = calloc(capacity,sizeof(Cell));
    s->top = -1;
}

void push(Stack* s, Cell* cell){
    if(s->top >= s->cap - 1){
        return;
    }
    s->top+=1;
    s->cell_arr[s->top] = *cell;
}

Cell* pop(Stack* s){
    if(s->top<=-1) return NULL;
    Cell* element = &s->cell_arr[s->top];
    s->top-=1;
    return element;
}