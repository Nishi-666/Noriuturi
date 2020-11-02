#pragma once
#ifndef GAME_Player_H
#define GAME_Player_H
#include "Collision.h"

//ゲームプレイヤーの初期化
void GamePlayer_initialize(void);

//終了
void GamePlayer_Finalize(void);

//更新
void GamePlayer_Update(void);

//描画
void GamePlayer_Draw(void);

//ゲームプレイヤー移動
void GamePlayer_MoveUp(void);
void GamePlayer_MoveDown(void);
void GamePlayer_MoveLeft(void);
void GamePlayer_MoveRight(void);


void GamePlayer_Shot(void);

void GamePlayer_Despawn(void);
bool GamePlayer_IsEnable(void);
CircleCollision GamePlayer_GetCollision(void);
void SetDeadCoolTimes(void);
bool GeTDeadCoolTimes(void);
void GamePlayer_Reset(void);
#endif // GAME_Player_H
