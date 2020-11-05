/*============================================================

Wall.h[Wall.h]                           Author:Kai Yamaya
												   Date:2020/11/05_72
-------------------------------------------------------

==============================================================
*/
#ifndef WALL_H
#define WALL_H
#include "CharOBJ.h"
//デバッグフォントモジュールの初期化
void WallInitialize(OBJData* Pj);
//デバッグフォントモジュールの終了処理
void WallFinalize(OBJData* Pj);
void WallUpdate(OBJData* Pj);

void WallDraw(OBJData* Pj);

#endif//WALL_H