/*============================================================

�Q�[���̓G����[Game_Enemy.cpp]                           Author:Kai Yamaya
												   Date:2020/7/21
-------------------------------------------------------

==============================================================*/
#pragma once
#ifndef GAME_ENEMY_H
#define GAME_ENEMY_H

#include "Collision.h"
//�Q�[���v���C���[�̏�����
void GameEnemy_initialize(void);

//�I��
void GameEnemy_Finalize(void);

//�X�V
void GameEnemy_Update(void);

//�`��
void GameEnemy_Draw(void);

void GameEnemy_Spawn(float x, float y);
bool GameEnemy_IsEnable(int i);//�Q�[���̓G���L��(true)��

//�e�̃R���W�����擾
CircleCollision GameEnemy_GetCollision(int i);

D3DXVECTOR2 GetEneemy_thisPos(int i);

void GameEnemy_Reset(void);

void GameEnemy_Despawn(int i);
#endif // GAME_Enemy_H
