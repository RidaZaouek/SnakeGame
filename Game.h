#pragma once
// Les constantes de direction
#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2
#define MAXBODYSERPENT 60

void initGrid(int,int);
void drawGrid();
void unit(int,int);
void drawSnake();
void drawFood();
void random(int&, int&);

