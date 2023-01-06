//
// Created by Administrator on 2023/1/6.
//

#include "dino.h"

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