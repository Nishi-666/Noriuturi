/*============================================================

ゲームの敵処理[Game_Enemy.cpp]                           Author:Kai Yamaya
												   Date:2020/7/21
-------------------------------------------------------

==============================================================*/
#pragma once
#ifndef GAME_ENEMY_H
#define GAME_ENEMY_H

#include "Collision.h"
//ゲームプレイヤーの初期化
void GameEnemy_initialize(void);

//終了
void GameEnemy_Finalize(void);

//更新
void GameEnemy_Update(void);

//描画
void GameEnemy_Draw(void);

void GameEnemy_Spawn(float x, float y);
bool GameEnemy_IsEnable(int i);//ゲームの敵が有効(true)か

//弾のコリジョン取得
CircleCollision GameEnemy_GetCollision(int i);

D3DXVECTOR2 GetEneemy_thisPos(int i);

void GameEnemy_Reset(void);

void GameEnemy_Despawn(int i);
#endif // GAME_Enemy_H
