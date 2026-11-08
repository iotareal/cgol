#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "fenster.h"
#define W 1281
#define H 721

const int width = W;
const int height = H;
const int border_color = 0x6C6B6B;
const uint8_t min_box_size = 10;
const uint8_t max_box_size = 50;
const uint8_t step = 10;
const uint8_t polling_delay = 150;
const int cell_color = 0xFFD700;
uint32_t buffer[W * H];

void draw_grid(struct fenster* f, int* lines_gap);
void drawbox(struct fenster *f, int* x, int* y, uint8_t* scale, int* color);
#endif