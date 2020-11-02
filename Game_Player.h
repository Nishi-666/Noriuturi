#pragma once
#ifndef GAME_Player_H
#define GAME_Player_H
#include "Collision.h"

//�Q�[���v���C���[�̏�����
void GamePlayer_initialize(void);

//�I��
void GamePlayer_Finalize(void);

//�X�V
void GamePlayer_Update(void);

//�`��
void GamePlayer_Draw(void);

//�Q�[���v���C���[�ړ�
void GamePlayer_MoveUp(void);
void GamePlayer_MoveDown(void);
void GamePlayer_MoveLeft(void);
void GamePlayer_MoveRight(void);


void GamePlayer_Shot(void);

void GamePlayer_Despawn(void);
bool GamePlayer_IsEnable(void);
CircleCollision GamePlayer_GetCollision(void);
void SetDeadCoolTimes(void);
bool GeTDeadCoolTimes(void);
void GamePlayer_Reset(void);
#endif // GAME_Player_H
