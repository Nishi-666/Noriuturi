/*============================================================

�v���C���[[Player.h]                           Author:Kai Yamaya
												   Date:2020/10/31
-------------------------------------------------------

==============================================================
*/#ifndef Player_H
#define Player_H
#include "CharOBJ.h"
//�f�o�b�O�t�H���g���W���[���̏�����
void PlayerInitialize(OBJData* Pj);
//�f�o�b�O�t�H���g���W���[���̏I������
void PlayerFinalize(OBJData* Pj);
void PlayerUpdate(OBJData* Pj);

void PlayerDraw(OBJData* Pj);
void SetLife(OBJData* Pj, int Life);

void MinasNowOLDNum(void);
void PorYChange(void);
bool GetYChange(void);
void SetAutomatic(OBJData* Pj,D3DXVECTOR3 MovePos);
D3DXVECTOR3 RetOldPos(void);
#endif//Player_H