/*============================================================

�A�C�X[ICE.h]                           Author:Kai Yamaya
												   Date:2020/11/30
-------------------------------------------------------

==============================================================
*/#ifndef ICE_H
#define ICE_H
#include "CharOBJ.h"
//�f�o�b�O�t�H���g���W���[���̏�����
void ICEInitialize(OBJData* Pj);
//�f�o�b�O�t�H���g���W���[���̏I������
void ICEFinalize(OBJData* Pj);
void ICEUpdate(OBJData* Pj);
void ICESetICE(OBJData* Pj);
void ICECollision(OBJData* Pj);
int IECJudgement(void);
void ICEDraw(OBJData* Pj);
void ICESetLife(OBJData* Pj, int Life);
void ICESetPos(OBJData* Pj, D3DXVECTOR2 Pos);
#endif//ICE_H