#include "dino.h"

int main(int argc, char *argv[]) {
    Init();
    load();
    begin:
    InitPlay();
    InitBegin();

    while (done) {
        SDL_Delay(50);
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    done = false;
                    Quit();
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.x > 700 && event.button.x < 1030 && event.button.y > 290 && event.button.y < 440)
                        goto play;
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
            display0.a0 = 1 - display0.a0;
        }

        for (int i = 0; i < 3; ++i) {
            if (RectNum[i] && rect_barrier[0].x <= width && rect_barrier[2].x <= width && rect_barrier[1].x <= width) {
                RectNum[i] = 0;
                srand(SDL_GetTicks());
                Rand = rand() % 2834 + 150 * speed;
                display0.barnum[i] = Select((Rand + 100) % 100);
                BarRect(i, display0.barnum[i], Rand + width);
            }
        }

        Display(&display0);
        MoveRect();

        for (int i = 0; i < 3; ++i) {
            if (rect_barrier[i].x < -180) {
                RectNum[i] = 1;
                rect_barrier[i].x = width;
            }
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
                            EnablePlay = 0;
                            if (!IsLeap) {
                                IsLeap = 1;
                                IsSub = 1;
                            }
                            break;
                        case SDLK_DOWN:
                            display0.IsLow = 1;
                            break;
                        case SDLK_ESCAPE:
                            goto pause;
                    }
                    break;
                case SDL_KEYUP:
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                        case SDLK_SPACE:
                            EnablePlay = 1;
                            IsSub = 0;
                            break;
                        case SDLK_DOWN:
                            display0.IsLow = 0;
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    break;
            }
        }

        if (IsDefeat0(display0.IsLow)) {
            CreatHI();
            display0.IsDefeat = 1;
            goto defeat;
        }

        if (IsLeap) {
            leap[0] -= leap[1];
            rect1.y -= leap[0];

            if (IsSub && leap[1] > 4 && leap[0] > 0) {
                leap[2] += 2;
                leap[1] = 12 - leap[2];
            }

            if (rect1.y >= 415) {
                IsLeap = 0;
                rect1.y = 415;
                leap[0] = 75;
                leap[1] = 12;
                leap[2] = 0;
            }
        }
    }

    pause:
    while (done) {
        SDL_Delay(50);
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

    defeat:
    Display(&display0);
    SDL_Delay(500);
    while (done) {
        SDL_Delay(50);
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
                            if(EnablePlay) {
                                InitPlay();
                                goto play;
                            }
                            break;
                        case SDLK_ESCAPE:
                            goto begin;
                    }
                    break;
                case SDL_KEYUP:
                    switch (event.key.keysym.sym) {
                        case SDLK_RETURN:
                        case SDLK_SPACE:
                            EnablePlay = 1;
                            IsSub = 0;
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.x > 622 && event.button.x < 745 && event.button.y > 321 && event.button.y < 385) {
                        InitPlay();
                        goto play;
                    }
                    if (event.button.x > 890 && event.button.x < 1131 && event.button.y > 320 && event.button.y < 385)
                        goto begin;
                    break;
            }
        }
    }
}

void CreatHI(){
    HI = HI > ScoreCal ? HI : ScoreCal;
    sprintf_s(HIC, 13, "HI %d", HI);
    HIS = TTF_RenderUTF8_Blended(ScoreFont, HIC, ScoreColor);
    HIT = SDL_CreateTextureFromSurface(R, HIS);
}

void InitBegin(){
    SDL_RenderCopy(R, MainBackTexture, NULL, &rect);
    CreatHI();
    SDL_RenderCopy(R, HIT, NULL, &HIRect);
    SDL_RenderPresent(R);
}

void InitPlay() {
    SpeedA = 1;
    speed = 3;
    TotalTime = 0;
    display0.IsDefeat = 0;
    display0.IsLow = 0;
    for (int i = 0; i < 3; ++i) {
        RectNum[i] = 1;
        rect_barrier[i].x = width;
    }
}

bool IsDefeat0(bool a) {
    if (!a) {
        int c[3] = {0};
        for (int i = 0; i < 3; ++i)
            if (rect_barrier[i].x + rect_barrier[i].w - 20 > rect1.x)
                c[i]++;
        for (int i = 0; i < 3; ++i)
            if (rect_barrier[i].x + 80 < rect1.x + rect1.h)
                c[i]++;
        for (int i = 0; i < 3; ++i)
            if (rect_barrier[i].y + rect_barrier[i].h - 30 > rect1.y)
                c[i]++;
        for (int i = 0; i < 3; ++i)
            if (rect_barrier[i].y + 70 < rect1.y + rect1.h)
                c[i]++;
        for (int i = 0; i < 3; ++i)
            if (c[i] >= 4)
                return true;
        return false;
    } else {
        int c[3] = {0};
        for (int i = 0; i < 3; ++i)
            if (rect_barrier[i].x + rect_barrier[i].w - 20 > RectLow.x)
                c[i]++;
        for (int i = 0; i < 3; ++i)
            if (rect_barrier[i].x + 20 < RectLow.x + RectLow.h)
                c[i]++;
        for (int i = 0; i < 3; ++i)
            if (rect_barrier[i].y + rect_barrier[i].h - 30 > RectLow.y)
                c[i]++;
        for (int i = 0; i < 3; ++i)
            if (rect_barrier[i].y + 30 < RectLow.y + RectLow.h)
                c[i]++;
        for (int i = 0; i < 3; ++i)
            if (c[i] >= 4)
                return true;
        return false;
    }
}

void BarRect(int i, int j, uint32_t a) {
    rect_barrier[i].x = a;
    if (j != 4)
        rect_barrier[i].h = img_barrier[j]->h;
    else {
        rect_barrier[i].h = img_barrier[4]->h + ((Rand + 100) % img_barrier[4]->h) / 2;
        rect_barrier[i].y = 550 - rect_barrier[i].h;
    }
    rect_barrier[i].w = img_barrier[j]->w;
    if (j == 0)
        rect_barrier[i].y = 395;
    if (j == 1)
        rect_barrier[i].y = 356;
    if (j == 2)
        rect_barrier[i].y = 380;
    if (j == 3) {
        rect_barrier[i].y = -18;
        rect_barrier[i].h = 470;
    }
    if (j == 5)
        rect_barrier[i].y = 0;
}

int Select(uint32_t i) {
    if (i == 97 && ScoreCal > 500)
        return 1;
    else if (i % 2 == 0)
        return 0;
    else if (i % 3 == 0 && ScoreCal > 100)
        return 4;
    else if (i % 5 == 0 && ScoreCal > 300)
        return 2;
    else if (i % 7 == 0 && ScoreCal > 400)
        return 5;
    else if (ScoreCal > 200)
        return 3;
    else
        return 0;
}

void CreateScore() {
    ScoreCal = TotalTime / 100;
    sprintf_s(ScoreC, 13, "Scores: %d", ScoreCal);
    SDL_FreeSurface(ScoreS);
    ScoreS = TTF_RenderUTF8_Blended(ScoreFont, ScoreC, ScoreColor);
    SDL_DestroyTexture(ScoreT);
    ScoreT = SDL_CreateTextureFromSurface(R, ScoreS);

    if (ScoreCal > SpeedA * 100) {
        speed++;
        SpeedA += speed - 2;
    }
}

void MoveRect() {
    rect_road.x = (rect_road.x - (7 * speed)) % 2347;
    rect_road_2.x = rect_road.x + rect_road.w;

    for (int i = 0; i < 3; ++i)
        if (!RectNum[i])
            rect_barrier[i].x = rect_barrier[i].x - (7 * speed);
}

void Init() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Dino", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    R = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    TTF_Init();
}

void load() {
    SDL_Surface *surface = SDL_GetWindowSurface(window);
    SDL_FillRect(surface, &rect, 0xff222222);
    BackTexture = SDL_CreateTextureFromSurface(R, surface);

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
    DefImg = IMG_Load("picture/defeat.png");
    DefMenu = IMG_Load("picture/DefMenu.png");

    DefMenuT = SDL_CreateTextureFromSurface(R,DefMenu);
    DefTexture = SDL_CreateTextureFromSurface(R,DefImg);
    MainBackTexture = SDL_CreateTextureFromSurface(R, MainBack);
    texture1 = SDL_CreateTextureFromSurface(R, img1);
    texture2 = SDL_CreateTextureFromSurface(R, img2);
    texture_road = SDL_CreateTextureFromSurface(R, img_road);
    for (int i = 0; i < 6; ++i) {
        texture_barrier[i] = SDL_CreateTextureFromSurface(R, img_barrier[i]);
    }
    TextureLow[0] = SDL_CreateTextureFromSurface(R, ImgLow[0]);
    TextureLow[1] = SDL_CreateTextureFromSurface(R, ImgLow[1]);
    ScoreFont = TTF_OpenFont("picture/a.ttf", 50);
    DefeatS = TTF_RenderUTF8_Blended(ScoreFont, "G A M E  O V E R", ScoreColor);
    DefeatT = SDL_CreateTextureFromSurface(R, DefeatS);

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

    RectLow.x = 55;
    RectLow.y = 463;
    RectLow.h = ImgLow[0]->h;
    RectLow.w = ImgLow[0]->w;

    DefMenuR.w = DefMenu->w;
    DefMenuR.h = DefMenu->h;
}

void Display(display *a) {
    SDL_RenderClear(R);
    SDL_RenderCopy(R, BackTexture, NULL, &rect);
    SDL_RenderCopy(R, texture_road, NULL, &rect_road_2);
    SDL_RenderCopy(R, texture_road, NULL, &rect_road);

    for (int i = 0; i < 3; ++i)
        if (!RectNum[i])
            SDL_RenderCopy(R, texture_barrier[a->barnum[i]], NULL, &rect_barrier[i]);

    if(a->IsDefeat){
        SDL_RenderCopy(R, DefMenuT, NULL, &DefMenuR);
        SDL_RenderCopy(R, DefTexture, NULL, &rect1);
        SDL_RenderCopy(R, DefeatT, NULL, &game_over);
    }else {
        if (!a->IsLow) {
            if (a->a0 == 0)
                SDL_RenderCopy(R, texture1, NULL, &rect1);
            if (a->a0 == 1)
                SDL_RenderCopy(R, texture2, NULL, &rect1);
        }

        if (a->IsLow) {
            if (a->a0 == 0)
                SDL_RenderCopy(R, TextureLow[0], NULL, &RectLow);
            if (a->a0 == 1)
                SDL_RenderCopy(R, TextureLow[1], NULL, &RectLow);
        }
    }

    SDL_RenderCopy(R, ScoreT, NULL, a->IsDefeat ? &DefScoreR : &ScoreR);
    SDL_RenderCopy(R, HIT, NULL, &HIRect);
    SDL_RenderPresent(R);
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
    SDL_FreeSurface(DefImg);
    SDL_FreeSurface(DefeatS);
    SDL_FreeSurface(DefMenu);
    SDL_DestroyTexture(DefMenuT);
    SDL_DestroyTexture(DefeatT);
    SDL_DestroyTexture(DefTexture);
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