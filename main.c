#include "dino.h"

int main(int argc, char *argv[]) {
    Init();
    load();
    begin:
    SDL_RenderCopy(R, MainBackTexture, NULL, &rect);
    SDL_RenderPresent(R);

    while (done) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    done = false;
                    Quit();
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.x > 700 && event.button.x < 1030 && event.button.y > 290 && event.button.y < 440) {
                        goto play;
                    }
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_RETURN:
                        case SDLK_SPACE:
                            goto play;
                        case SDLK_ESCAPE:
                            done = false;
                            Quit();
                            break;
                    }
                    break;
            }
        }
    }

    play:
    time = SDL_GetTicks();
    while (done) {
        interval = SDL_GetTicks() - time;

        if (interval < 25)
            SDL_Delay(25 - interval);

        TotalTime += 25;
        time = SDL_GetTicks();
        CreateScore();

        if (time - TimeA > 70) {
            TimeA = time;
            a0 = 1 - a0;
        }

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    done = false;
                    Quit();
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                        case SDLK_SPACE:
                            if (!IsLeap) {
                                IsLeap = 1;
                                IsSub = 1;
                            }
                            break;
                        case SDLK_DOWN:
                            IsLow = 1;
                            break;
                        case SDLK_ESCAPE:
                            goto pause;
                    }
                    break;
                case SDL_KEYUP:
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                        case SDLK_SPACE:
                            IsSub = 0;
                            break;
                        case SDLK_s:
                            IsLow = 0;
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    break;
            }
        }

        if (IsLeap) {
            leap[0] -= leap[1];
            rect1.y -= leap[0];
            if(IsSub && leap[1] > 4 && leap[0] > 0){
                leap[2] += 2;
                leap[1] = 12 - leap[2];
                printf("%d", leap[2]);
            }
            if (rect1.y >= 415) {
                IsLeap = 0;
                rect1.y = 415;
                leap[0] = 75;
                leap[1] = 12;
                leap[2] = 0;
            }
        }

        display1(barnum, a0);
        MoveRect();
    }

    pause:
    while (done) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    done = false;
                    Quit();
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_RETURN:
                        case SDLK_SPACE:
                            goto play;
                        case SDLK_ESCAPE:
                            goto begin;
                    }
                    break;
            }
        }
    }
}

void CreateScore() {
    ScoreCal = TotalTime / 100;
    sprintf_s(ScoreC, 12, "Scores: %d", ScoreCal);
    ScoreS = TTF_RenderUTF8_Blended(ScoreFont, ScoreC, ScoreColor);
    ScoreT = SDL_CreateTextureFromSurface(R, ScoreS);
    speed = ScoreCal / 100 + 3;
}

void MoveRect() {
    rect_road.x = (rect_road.x - (7 * speed)) % 2347;
    rect_road_2.x = rect_road.x + rect_road.w;
}

void Init() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Dino", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    R = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    TTF_Init();
}

void load() {
    img1 = IMG_Load("picture/1.png");
    img2 = IMG_Load("picture/2.png");
    img_road = IMG_Load("picture/3.png");
    img_barrier[0] = IMG_Load("picture/4.png");
    img_barrier[1] = IMG_Load("picture/5.png");
    img_barrier[2] = IMG_Load("picture/6.png");
    img_barrier[3] = IMG_Load("picture/7.png");
    img_barrier[4] = IMG_Load("picture/8.png");
    img_barrier[5] = IMG_Load("picture/9.png");
    ImgLow[0] = IMG_Load("picture/low1.png");
    ImgLow[1] = IMG_Load("picture/low2.png");
    MainBack = IMG_Load("picture/mainbg.PNG");

    MainBackTexture = SDL_CreateTextureFromSurface(R, MainBack);
    texture1 = SDL_CreateTextureFromSurface(R, img1);
    texture2 = SDL_CreateTextureFromSurface(R, img2);
    texture_road = SDL_CreateTextureFromSurface(R, img_road);
    for (int i = 0; i < 6; ++i) {
        texture_barrier[i] = SDL_CreateTextureFromSurface(R, img_barrier[i]);
    }
    TextureLow[0] = SDL_CreateTextureFromSurface(R, ImgLow[0]);
    TextureLow[1] = SDL_CreateTextureFromSurface(R, ImgLow[1]);
    ScoreFont = TTF_OpenFont("a.ttf", 50);

    rect1.x = 55;
    rect1.y = 415;
    rect1.h = img1->h;
    rect1.w = img1->w;

    rect_road.x = 0;
    rect_road.y = 522;
    rect_road.h = img_road->h;
    rect_road.w = img_road->w;

    rect_road_2.x = 0;
    rect_road_2.y = 522;
    rect_road_2.h = img_road->h;
    rect_road_2.w = img_road->w;
}

void display1(const int *j, bool a) {
    SDL_RenderClear(R);
    SDL_RenderCopy(R, BackTexture, NULL, &rect);
    SDL_RenderCopy(R, texture_road, NULL, &rect_road_2);
    SDL_RenderCopy(R, texture_road, NULL, &rect_road);
    for (int i = 0; i < 3; ++i) {
        if (!RectNum[i]) {
            SDL_RenderCopy(R, texture_barrier[j[i]], NULL, &rect_barrier[i]);
        }
    }
    if (a == 0) {
        SDL_RenderCopy(R, texture1, NULL, &rect1);
    }
    if (a == 1) {
        SDL_RenderCopy(R, texture2, NULL, &rect1);
    }
    SDL_RenderCopy(R, ScoreT, NULL, &ScoreR);
    SDL_RenderPresent(R);
}