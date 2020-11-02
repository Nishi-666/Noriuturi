/*============================================================

�Q�[���̓G����[Game_Explosion.cpp]                           Author:Kai Yamaya
												   Date:2020/7/21
-------------------------------------------------------

==============================================================*/
#pragma once
#ifndef GAME_EXPLOSION_H
#define GAME_EXPLOSION_H

#include "Collision.h"
//�Q�[���v���C���[�̏�����
void GameExplosion_initialize(void);

//�I��
void GameExplosion_Finalize(void);

//�X�V
void GameExplosion_Update(void);

//�`��
void GameExplosion_Draw(void);

void GameExplosion_Spawn(float x, float y);
bool GameExplosion_IsEnable(int i);//�Q�[���̓G���L��(true)��

//�e�̃R���W�����擾
CircleCollision GameExplosion_GetCollision(int i);


void GameExplosion_Despawn(int i);
#endif // GAME_Explosion_H
