#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <windows.h>
#include "stack.h"

const uint8_t *cell_state = (uint8_t *)".#";

uint8_t **get_newframe(const long long frame_size)
{
    uint8_t **grid = (uint8_t **)calloc(frame_size, sizeof(uint8_t *));
    for (int x = 0; x < frame_size; x += 1)
    {
        grid[x] = ((uint8_t *)calloc(frame_size, sizeof(uint8_t)));
    }
    return grid;
}

void drawframe(uint8_t **grid, const long long frame_size)
{
    for (int x = 0; x < frame_size; x += 1)
    {
        for (int y = 0; y < frame_size; y += 1)
        {
            printf(" %c ", cell_state[grid[x][y]]);
        }
        printf("\n");
    }
}

void flip(uint8_t *value)
{
    *value = *value ^ (1 << 0);
}

void buffer_filler(const uint8_t **frame, const long long frame_size, Stack* buffer)
{
    for (int i = 0; i < frame_size; i++)
    {
        for (int j = 0; j < frame_size; j++)
        {
            // Checking Moore Neighbors
            int n_alive = 0;
            for (int x = i - 1; x <= i + 1; x++)
            {
                if (x < 0 || x >= frame_size)
                    continue;
                for (int y = j - 1; y <= j + 1; y++)
                {
                    if ((x == i && y == j) || y < 0 || y >= frame_size)
                        continue;
                    // incrementing the "1" neighbors
                    n_alive += frame[x][y];
                }
            }

            if ((frame[i][j] == 1 && (n_alive < 2 || n_alive > 3)) || (frame[i][j] == 0 && n_alive == 3))
            {
                Cell cell = {i, j};
                push(buffer, &cell);
            }
        }
    }
}

void buffer_drainer(uint8_t** frame,Stack* buffer)
{
    Cell *cell = NULL;
    while ((cell = pop(buffer)))
    {
        flip(&frame[cell->x][cell->y]);
    }
}

int main()
{
    const long long size = 35;
    uint8_t **frame = get_newframe(size);
    Stack *buffer = calloc(1, sizeof(Stack));
    init(buffer, size * size);
    
    // Spawn a Glider near the top-left corner
    int cx = 3, cy = 3;
    flip(&frame[cx][cy + 1]);       
    flip(&frame[cx + 1][cy + 2]);   
    flip(&frame[cx + 2][cy]);       
    flip(&frame[cx + 2][cy + 1]);
    flip(&frame[cx + 2][cy + 2]);

    printf("\033[2J");
    long long tick = 0;
    while (1)
    {   
        printf("\033[H");
        printf("Tick: %lld\n", ++tick);
        
        buffer_filler((const uint8_t**)frame, size, buffer);
        buffer_drainer(frame, buffer);
        drawframe(frame, size);
        
        Sleep(300);
    }
    return 0;
}