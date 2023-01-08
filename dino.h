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

typedef struct display{
    int barnum[3];
    bool a0;
    bool IsLow;
    bool IsDefeat;
}display;

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
static SDL_Surface *HIS = NULL;
static SDL_Surface *DefImg = NULL;
static SDL_Surface *DefeatS = NULL;
static SDL_Surface *DefMenu = NULL;
static SDL_Texture *DefMenuT = NULL;
static SDL_Texture *DefeatT = NULL;
static SDL_Texture *DefTexture = NULL;
static SDL_Texture *HIT = NULL;
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
static SDL_Rect HIRect = {1250, 0, 150, 50};
static SDL_Rect DefScoreR = {748, 261, 200, 50};
static SDL_Rect rect_barrier[3] = {{width, 500, 166, 160},
                     {width, 500, 166, 160},
                     {width, 500, 166, 160}};
static SDL_Rect RectLow;
static SDL_Rect game_over = {609, 90, 500, 200};
static SDL_Rect DefMenuR = {621, 321};
static TTF_Font *ScoreFont = NULL;

static bool IsLeap = 0;
static bool IsSub = 0;
static bool done = true;
static bool RectNum[3] = {true, true, true};
static int speed = 3;
static int SpeedA = 1;
static int leap[3] = {75,12, 0};
static uint32_t Rand;
static uint32_t ScoreCal = 0;
static uint32_t HI = 0;
static uint32_t time = 0;
static uint32_t TimeA = 0;
static uint32_t interval = 0;
static uint32_t ScoreNum;
static uint32_t TotalTime = 0;
static char ScoreC[13];
static char HIC[9];
static display display0 = {{0},0,0, 0};

void Quit();
void load();
int Select(uint32_t i);
void BarRect(int i, int j, uint32_t a);
bool IsDefeat0(bool a);
void Init();
void CreateScore();
void MoveRect();
void Display(display *a);
void InitPlay();
void InitBegin();
void CreatHI();

#endif //PROJECT1_DINO_H
