/*============================================================

プレイヤー[Enemy.h]                           Author:Kai Yamaya
												   Date:2020/10/31
-------------------------------------------------------

==============================================================
*/#ifndef Enemy_H
#define Enemy_H
#include "CharOBJ.h"
//デバッグフォントモジュールの初期化
void EnemyInitialize(OBJData* Pj);
//デバッグフォントモジュールの終了処理
void EnemyFinalize(OBJData* Pj);
void EnemyUpdate(OBJData* Pj);

void EnemyDraw(OBJData* Pj);
void MoveStr();
#endif//Enemy_H