/*============================================================

ゲームの弾の制御部[Game_Barret.h]                            Author:Kai Yamaya
												   Date:2020/7/17
-------------------------------------------------------

==============================================================
*/
#pragma once
#include "Collision.h"
#ifndef GAME_BARRET_H
#define GAME_BARRET_H

//弾の初期化
void GameBarret_initialize(void);

//弾の終了
void GameBarret_Finalize(void);

//弾の更新
void GameBarret_Update(void);

//弾の描画
void GameBarret_Draw(void);
//弾の生成
void GameBarret_Create(float x, float y, float MoveX, float MoveY, double angle);
//弾のコリジョン取得
CircleCollision GameBarret_GetCollision(int Num);

void GameBarret_Despawn(int Num);
bool GameBarret_IsEnable(int Num);

int GameBarret_GetMax(void);
void GameBarret_Reset(void);
#endif // GAME_BARRET_H