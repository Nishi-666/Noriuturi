/*============================================================

ゲームの敵処理[Game_Boss.cpp]                           Author:Kai Yamaya
												   Date:2020/7/21
-------------------------------------------------------

==============================================================*/
#pragma once
#ifndef GAME_BOSS_H
#define GAME_BOSS_H

#include "Collision.h"
//ゲームプレイヤーの初期化
void GameBoss_initialize(void);

//終了
void GameBoss_Finalize(void);

//更新
void GameBoss_Update(void);

//描画
void GameBoss_Draw(void);

void GameBoss_Spawn(float x, float y);
bool GameBoss_IsEnable(void);//ゲームの敵が有効(true)か

//弾のコリジョン取得
CircleCollision GameBoss_GetCollision(void);

D3DXVECTOR2 GetBoss_thisPos(void);

void GameBoss_Reset(void);
void GameBoss_Damage(int i);
#endif // GAME_Boss_H
