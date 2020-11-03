#pragma once
/*============================================================

幽霊[Yuley.h]                           Author:Kai Yamaya
												   Date:2020/7/13
-------------------------------------------------------

==============================================================
*/#ifndef YULEY_H
#define YULEY_H
#include "CharOBJ.h"
//デバッグフォントモジュールの初期化
void YuleyInitialize(OBJData* Pj);
//デバッグフォントモジュールの終了処理
void YuleyFinalize(OBJData* Pj);
void YuleyUpdate(OBJData* Pj);
void YuleyControl(OBJData* Pj);
void YuleyDraw(OBJData* Pj);
void YuleyPosChange(OBJData* Pj);
#endif//Yuley_H