/*============================================================

アイス[ICE.h]                           Author:Kai Yamaya
												   Date:2020/11/30
-------------------------------------------------------

==============================================================
*/#ifndef ICE_H
#define ICE_H
#include "CharOBJ.h"
//デバッグフォントモジュールの初期化
void ICEInitialize(OBJData* Pj);
//デバッグフォントモジュールの終了処理
void ICEFinalize(OBJData* Pj);
void ICEUpdate(OBJData* Pj);
void ICESetICE(OBJData* Pj);
void ICECollision(OBJData* Pj);
int IECJudgement(void);
void ICEDraw(OBJData* Pj);
void ICESetLife(OBJData* Pj, int Life);
void ICESetPos(OBJData* Pj, D3DXVECTOR2 Pos);
#endif//ICE_H