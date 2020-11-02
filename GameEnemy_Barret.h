/*============================================================

ƒQ[ƒ€‚Ì’e‚Ì§Œä•”[Game_Barret.h]                            Author:Kai Yamaya
												   Date:2020/7/17
-------------------------------------------------------

==============================================================
*/
#pragma once
#include "Collision.h"
#ifndef GAMEENEMY_BARRET_H
#define GAMEENEMY_BARRET_H

//’e‚Ì‰Šú‰»
void GameEnemyBarret_initialize(void);

//’e‚ÌI—¹
void GameEnemyBarret_Finalize(void);

//’e‚ÌXV
void GameEnemyBarret_Update(void);

//’e‚Ì•`‰æ
void GameEnemyBarret_Draw(void);
//’e‚Ì¶¬
void GameEnemyBarret_Create(float x, float y, float mx, float my);
//’e‚ÌƒRƒŠƒWƒ‡ƒ“æ“¾
CircleCollision GameEnemyBarret_GetCollision(int i);
void GameEnemyBarret_Reset(void);
void GameEnemyBarret_Despawn(int i);
bool GameEnemyBarret_IsEnable(int i);
#endif // GAME_BARRET_H