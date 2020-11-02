/*============================================================

�Q�[���̓G����[Game_Boss.cpp]                           Author:Kai Yamaya
												   Date:2020/7/21
-------------------------------------------------------

==============================================================*/
#pragma once
#ifndef GAME_BOSS_H
#define GAME_BOSS_H

#include "Collision.h"
//�Q�[���v���C���[�̏�����
void GameBoss_initialize(void);

//�I��
void GameBoss_Finalize(void);

//�X�V
void GameBoss_Update(void);

//�`��
void GameBoss_Draw(void);

void GameBoss_Spawn(float x, float y);
bool GameBoss_IsEnable(void);//�Q�[���̓G���L��(true)��

//�e�̃R���W�����擾
CircleCollision GameBoss_GetCollision(void);

D3DXVECTOR2 GetBoss_thisPos(void);

void GameBoss_Reset(void);
void GameBoss_Damage(int i);
#endif // GAME_Boss_H
