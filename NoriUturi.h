/*============================================================

乗り移り対象[NoriUturi.h]                           Author:Kai Yamaya
												   Date:2020/7/13
-------------------------------------------------------

==============================================================
*/#ifndef NORIUTURI_H
#define NORIUTURI_H
#include "CharOBJ.h"
//デバッグフォントモジュールの初期化
void NoriuturiInitialize(OBJData* Pj);
//デバッグフォントモジュールの終了処理
void NoriuturiFinalize(OBJData* Pj);
void NoriuturiUpdate(OBJData* Pj);

void NoriuturiDraw(OBJData* Pj);

#endif//NORIUTURI_H