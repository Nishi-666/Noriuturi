/*============================================================

�v���C���[[Enemy.h]                           Author:Kai Yamaya
												   Date:2020/10/31
-------------------------------------------------------

==============================================================
*/#ifndef Enemy_H
#define Enemy_H
#include "CharOBJ.h"
//�f�o�b�O�t�H���g���W���[���̏�����
void EnemyInitialize(OBJData* Pj);
//�f�o�b�O�t�H���g���W���[���̏I������
void EnemyFinalize(OBJData* Pj);
void EnemyUpdate(OBJData* Pj);

void EnemyDraw(OBJData* Pj);
void MoveStr();
#endif//Enemy_H