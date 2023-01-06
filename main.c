#include "dino.h"

int main(int argc, char *argv[]) {
    Init();
    load();
    Begin:
    SDL_RenderCopy(R, MainBackTexture, NULL, &rect);
    SDL_RenderPresent(R);

    while (done){
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    done = false;
                    Quit();
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.x > 700 && event.button.x < 1030 && event.button.y > 290 && event.button.y < 440) {
                        break;
                    }
            }
        }
    }

    main:
    time = SDL_GetTicks();
    while (done){
        TotalTime += SDL_GetTicks() - time;
        time = SDL_GetTicks();
        CreateScore();

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    done = false;
                    Quit();
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_w:
                        case SDLK_SPACE:
                            break;
                        case SDLK_DOWN:
                            IsLow = 1;
                            break;
                        case SDLK_ESCAPE:
                            goto l;
                    }
                    break;
                case SDL_KEYUP:
                    switch (event.key.keysym.sym) {
                        case SDLK_s:
                            IsLow = 0;
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    printf("(%d %d)", event.button.x, event.button.y);
                    break;
            }
        }
    }
}

void Init(){
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
    rect1.x = 0;
    rect1.y = 430;
    rect1.h = img1->h;
    rect1.w = img1->w;
}

void Quit() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(R);
    SDL_FreeSurface(img1);
    SDL_FreeSurface(img2);
    SDL_FreeSurface(img_road);
    for (int i = 0; i < 6; ++i) {
        SDL_FreeSurface(img_barrier[i]);
    }
    SDL_FreeSurface(ImgLow[0]);
    SDL_FreeSurface(ImgLow[1]);
    SDL_FreeSurface(MainBack);
    SDL_FreeSurface(ScoreS);
    SDL_DestroyTexture(ScoreT);
    SDL_DestroyTexture(MainBackTexture);
    SDL_DestroyTexture(TextureLow[0]);
    SDL_DestroyTexture(TextureLow[1]);
    for (int i = 0; i < 6; ++i) {
        SDL_DestroyTexture(texture_barrier[i]);
    }
    SDL_DestroyTexture(texture1);
    SDL_DestroyTexture(texture2);
    SDL_DestroyTexture(texture_road);
    SDL_DestroyTexture(BackTexture);
    TTF_CloseFont(ScoreFont);
    SDL_Quit();
}
