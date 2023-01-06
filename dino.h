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

static SDL_Event event;
static SDL_Window *window = NULL;
static SDL_Renderer *R = NULL;
static SDL_Surface *img1 = NULL;
static SDL_Surface *img2 = NULL;
static SDL_Surface *img_road = NULL;
static SDL_Surface *img_barrier[6] = {NULL};
static SDL_Surface *ImgLow[2] = {NULL};
static SDL_Surface *MainBack = NULL;
static SDL_Surface *ScoreS = NULL;
static SDL_Texture *ScoreT = NULL;
static SDL_Texture *MainBackTexture = NULL;
static SDL_Texture *texture1 = NULL;
static SDL_Texture *texture2 = NULL;
static SDL_Texture *BackTexture = NULL;
static SDL_Texture *texture_road = NULL;
static SDL_Texture *texture_barrier[6] = {NULL};
static SDL_Texture *TextureLow[2] = {NULL};
static SDL_Rect rect = {0, 0, width, height};
static SDL_Color ScoreColor = {172, 172, 172, 255};
static SDL_Rect rect1;
static SDL_Rect rect_road;
static SDL_Rect rect_road_2;
static SDL_Rect ScoreR = {1500, 0, 200, 50};
static SDL_Rect rect_barrier[3] = {{width, 500, 166, 160},
                     {width, 500, 166, 160},
                     {width, 500, 166, 160}};
static SDL_Rect RectLow = {0, 480, 248, 128};
static TTF_Font *ScoreFont = NULL;

static bool IsLow = 0;
static uint32_t Rand;
static int road1 = 0;
static uint32_t rand0;
static int barnum[3];
static int b = 1;
static int genxin = 3;
static int speed;
static uint32_t ScoreCal;
static bool RectNum[3] = {true, true, true};
static bool stop = true;
static bool done = true;
static uint32_t time = 0;
static uint32_t time0 = 0;
static uint32_t ScoreNum;
static uint32_t TotalTime = 0;
static char ScoreC[12];

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
void Init();
void CreateScore();

#endif //PROJECT1_DINO_H