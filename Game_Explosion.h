/*============================================================

ゲームの敵処理[Game_Explosion.cpp]                           Author:Kai Yamaya
												   Date:2020/7/21
-------------------------------------------------------

==============================================================*/
#pragma once
#ifndef GAME_EXPLOSION_H
#define GAME_EXPLOSION_H

#include "Collision.h"
//ゲームプレイヤーの初期化
void GameExplosion_initialize(void);

//終了
void GameExplosion_Finalize(void);

//更新
void GameExplosion_Update(void);

//描画
void GameExplosion_Draw(void);

void GameExplosion_Spawn(float x, float y);
bool GameExplosion_IsEnable(int i);//ゲームの敵が有効(true)か

//弾のコリジョン取得
CircleCollision GameExplosion_GetCollision(int i);


void GameExplosion_Despawn(int i);
#endif // GAME_Explosion_H
