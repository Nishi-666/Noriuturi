/*============================================================

�Q�[���̒e�̐��䕔[Game_Barret.h]                            Author:Kai Yamaya
												   Date:2020/7/17
-------------------------------------------------------

==============================================================
*/
#pragma once
#include "Collision.h"
#ifndef GAMEENEMY_BARRET_H
#define GAMEENEMY_BARRET_H

//�e�̏�����
void GameEnemyBarret_initialize(void);

//�e�̏I��
void GameEnemyBarret_Finalize(void);

//�e�̍X�V
void GameEnemyBarret_Update(void);

//�e�̕`��
void GameEnemyBarret_Draw(void);
//�e�̐���
void GameEnemyBarret_Create(float x, float y, float mx, float my);
//�e�̃R���W�����擾
CircleCollision GameEnemyBarret_GetCollision(int i);
void GameEnemyBarret_Reset(void);
void GameEnemyBarret_Despawn(int i);
bool GameEnemyBarret_IsEnable(int i);
#endif // GAME_BARRET_H