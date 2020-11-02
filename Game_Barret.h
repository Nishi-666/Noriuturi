/*============================================================

�Q�[���̒e�̐��䕔[Game_Barret.h]                            Author:Kai Yamaya
												   Date:2020/7/17
-------------------------------------------------------

==============================================================
*/
#pragma once
#include "Collision.h"
#ifndef GAME_BARRET_H
#define GAME_BARRET_H

//�e�̏�����
void GameBarret_initialize(void);

//�e�̏I��
void GameBarret_Finalize(void);

//�e�̍X�V
void GameBarret_Update(void);

//�e�̕`��
void GameBarret_Draw(void);
//�e�̐���
void GameBarret_Create(float x, float y, float MoveX, float MoveY, double angle);
//�e�̃R���W�����擾
CircleCollision GameBarret_GetCollision(int Num);

void GameBarret_Despawn(int Num);
bool GameBarret_IsEnable(int Num);

int GameBarret_GetMax(void);
void GameBarret_Reset(void);
#endif // GAME_BARRET_H