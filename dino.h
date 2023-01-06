//
// Created by Administrator on 2023/1/6.
//

#ifndef PROJECT1_DINO_H
#define PROJECT1_DINO_H

#include "stdio.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "stdbool.h"
#include "stdlib.h"

#undef main

#define width 1700
#define height 700

SDL_Window *window = NULL;
SDL_Renderer *R = NULL;
SDL_Surface *img1 = NULL;
SDL_Surface *img2 = NULL;
SDL_Surface *img_road = NULL;
SDL_Surface *img_barrier[6] = {NULL};
SDL_Surface *ImgLow[2] = {NULL};
SDL_Surface *MainBack = NULL;
SDL_Surface *ScoreS = NULL;
SDL_Texture *ScoreT = NULL;
SDL_Texture *MainBackTexture = NULL;
SDL_Texture *texture1 = NULL;
SDL_Texture *texture2 = NULL;
SDL_Texture *texture3 = NULL;
SDL_Texture *texture_barrier[6] = {NULL};
SDL_Texture *TextureLow[2] = {NULL};
SDL_Rect rect = {0, 0, width, height};
SDL_Color ScoreColor = {172, 172, 172, 255};
SDL_Rect rect1;
SDL_Rect rect4;
SDL_Rect rect4_2;
SDL_Rect ScoreR = {1500, 0, 200, 50};
SDL_Rect rect5[3] = {{width, 500, 166, 160},
                     {width, 500, 166, 160},
                     {width, 500, 166, 160}};
SDL_Rect RectLow = {0, 480, 248, 128};
TTF_Font *ScoreFont = NULL;

int IsLow = 0;
uint32_t Rand;
int road1 = 0;
uint32_t rand0;
int barnum[3];
int b = 1;
int genxin = 3;
int speed;
uint32_t ScoreCal;
bool RectNum[3] = {true, true, true};
bool stop = true;
uint32_t time = 0;
uint32_t time0 = 0;
uint32_t ScoreNum;
char ScoreC[12] = "Scores:";

void Quit();

void load();

void display1(const int *j, int a);

void display2(const int *j, int a);

void leap(int i, const int *j);

void fall(int i, const int *j);

void LoadRect(int r1);

void ReBarRect(uint32_t a, int i);

int Select(uint32_t i);

void BarRect(int i, int j, uint32_t a);

bool IsDefeat0(int a);

void Score(char *a, uint32_t c);

#endif //PROJECT1_DINO_H
