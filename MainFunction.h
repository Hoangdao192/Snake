 
#ifndef MAINFUNCTION_H_
#define MAINFUNCTION_H_

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <ctime>
#include <sys/time.h>
#include<cstdlib>
#include<stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <stdio.h>     
#include <stdlib.h>
#include <vector>
#include <cstdlib>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>


using namespace std;

static Mix_Music *g_music = NULL;
static Mix_Chunk *g_chunk = NULL;

const int SNAKE_COLOR_FORE = 34;
const int SNAKE_COLOR_BACK = 44;
const int SNAKE_HEAD_COLOR_FORE = 33;
const int SNAKE_HEAD_COLOR_BACK = 43;
const int FOOD_COLOR_FORE = 32;
const int FOOD_COLOR_BACK = 42;

const string SNAKE_COLOR_TEXT = "\033[" + to_string(SNAKE_COLOR_FORE) + ";" + to_string(SNAKE_COLOR_BACK) + "m";
const string SNAKE_HEAD_COLOR_TEXT = "\033[" + to_string(SNAKE_HEAD_COLOR_FORE) + ";" + to_string(SNAKE_HEAD_COLOR_BACK) + "m";
const string FOOD_COLOR_TEXT = "\033[" + to_string(FOOD_COLOR_FORE) + ";" + to_string(FOOD_COLOR_BACK) + "m";

const int MOVE_LEFT = 0;
const int MOVE_RIGHT = 1;
const int MOVE_UP = 2;
const int MOVE_DOWN = 3;

void gotoXY(int x, int y);
void clearScreen();
char getch();
int kbhit();
void delay(long miliseconds);
void playMusic(string path);

#endif