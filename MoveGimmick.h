/*============================================================

�v���C���[[MoveGimmick.h]                           Author:Kai Yamaya
												   Date:2020/10/31
-------------------------------------------------------

==============================================================
*/#ifndef MOVEGIMMICK_H
#define MOVEGIMMICK_H
#include "CharOBJ.h"
//�f�o�b�O�t�H���g���W���[���̏�����
void MoveGimmickInitialize(OBJData* Pj);
//�f�o�b�O�t�H���g���W���[���̏I������
void MoveGimmickFinalize(OBJData* Pj);
void MoveGimmickUpdate(OBJData* Pj);

void MoveGimmickDraw(OBJData* Pj);

#endif//MOVEGIMMICK_H