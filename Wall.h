/*============================================================

Wall.h[Wall.h]                           Author:Kai Yamaya
												   Date:2020/11/05_72
-------------------------------------------------------

==============================================================
*/
#ifndef WALL_H
#define WALL_H
#include "CharOBJ.h"
//�f�o�b�O�t�H���g���W���[���̏�����
void WallInitialize(OBJData* Pj);
//�f�o�b�O�t�H���g���W���[���̏I������
void WallFinalize(OBJData* Pj);
void WallUpdate(OBJData* Pj);

void WallDraw(OBJData* Pj);

#endif//WALL_H