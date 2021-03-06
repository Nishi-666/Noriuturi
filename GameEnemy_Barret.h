/*============================================================

ゲームの弾の制御部[Game_Barret.h]                            Author:Kai Yamaya
												   Date:2020/7/17
-------------------------------------------------------

==============================================================
*/
#pragma once
#include "Collision.h"
#ifndef GAMEENEMY_BARRET_H
#define GAMEENEMY_BARRET_H

//弾の初期化
void GameEnemyBarret_initialize(void);

//弾の終了
void GameEnemyBarret_Finalize(void);

//弾の更新
void GameEnemyBarret_Update(void);

//弾の描画
void GameEnemyBarret_Draw(void);
//弾の生成
void GameEnemyBarret_Create(float x, float y, float mx, float my);
//弾のコリジョン取得
CircleCollision GameEnemyBarret_GetCollision(int i);
void GameEnemyBarret_Reset(void);
void GameEnemyBarret_Despawn(int i);
bool GameEnemyBarret_IsEnable(int i);
#endif // GAME_BARRET_H