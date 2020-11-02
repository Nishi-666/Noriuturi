#pragma once
#ifndef GAME_GND_H
#define GAME_GND_H
#include "Collision.h"

//ゲームプレイヤーの初期化
void GameGND_initialize(void);

//終了
void GameGND_Finalize(void);

//更新
void GameGND_Update(void);

//描画
void GameGND_Draw(void);

float GameGND_GetY(float Pos);

int GameGND_GetHeightSPR(float PosX);

int GameGND_GetSPR(float PosX);
int GameGND_GetHeightPos(float PosX);
#endif