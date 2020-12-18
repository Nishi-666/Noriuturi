/*============================================================

プレイヤー[MoveGimmick.h]                           Author:Kai Yamaya
												   Date:2020/10/31
-------------------------------------------------------

==============================================================
*/#ifndef MOVEGIMMICK_H
#define MOVEGIMMICK_H
#include "CharOBJ.h"
//デバッグフォントモジュールの初期化
void MoveGimmickInitialize(OBJData* Pj);
//デバッグフォントモジュールの終了処理
void MoveGimmickFinalize(OBJData* Pj);
void MoveGimmickUpdate(OBJData* Pj);

void MoveGimmickDraw(OBJData* Pj);

#endif//MOVEGIMMICK_H