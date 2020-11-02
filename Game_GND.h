#pragma once
#ifndef GAME_GND_H
#define GAME_GND_H
#include "Collision.h"

//�Q�[���v���C���[�̏�����
void GameGND_initialize(void);

//�I��
void GameGND_Finalize(void);

//�X�V
void GameGND_Update(void);

//�`��
void GameGND_Draw(void);

float GameGND_GetY(float Pos);

int GameGND_GetHeightSPR(float PosX);

int GameGND_GetSPR(float PosX);
int GameGND_GetHeightPos(float PosX);
#endif