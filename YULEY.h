#pragma once
/*============================================================

�H��[Yuley.h]                           Author:Kai Yamaya
												   Date:2020/7/13
-------------------------------------------------------

==============================================================
*/#ifndef YULEY_H
#define YULEY_H
#include "CharOBJ.h"
//�f�o�b�O�t�H���g���W���[���̏�����
void YuleyInitialize(OBJData* Pj);
//�f�o�b�O�t�H���g���W���[���̏I������
void YuleyFinalize(OBJData* Pj);
void YuleyUpdate(OBJData* Pj);
void YuleyControl(OBJData* Pj);
void YuleyDraw(OBJData* Pj);
void YuleyPosChange(OBJData* Pj);
#endif//Yuley_H