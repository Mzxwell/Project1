//
// Created by Administrator on 2023/1/6.
//

#include "dino.h"

void CreateScore(){
    ScoreCal = TotalTime / 100;
    sprintf_s(ScoreC, 12, "Scores: %d", ScoreCal);
    ScoreS = TTF_RenderUTF8_Blended(ScoreFont, ScoreC, ScoreColor);
    ScoreT = SDL_CreateTextureFromSurface(R, ScoreS);
}