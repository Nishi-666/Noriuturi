/*============================================================

���ڂ�Ώ�[NoriUturi.h]                           Author:Kai Yamaya
												   Date:2020/7/13
-------------------------------------------------------

==============================================================
*/#ifndef NORIUTURI_H
#define NORIUTURI_H
#include "CharOBJ.h"
//�f�o�b�O�t�H���g���W���[���̏�����
void NoriuturiInitialize(OBJData* Pj);
//�f�o�b�O�t�H���g���W���[���̏I������
void NoriuturiFinalize(OBJData* Pj);
void NoriuturiUpdate(OBJData* Pj);

void NoriuturiDraw(OBJData* Pj);

#endif//NORIUTURI_H