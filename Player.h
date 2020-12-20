/*============================================================

プレイヤー[Player.h]                           Author:Kai Yamaya
												   Date:2020/10/31
-------------------------------------------------------

==============================================================
*/#ifndef Player_H
#define Player_H
#include "CharOBJ.h"
//デバッグフォントモジュールの初期化
void PlayerInitialize(OBJData* Pj);
//デバッグフォントモジュールの終了処理
void PlayerFinalize(OBJData* Pj);
void PlayerUpdate(OBJData* Pj);

void PlayerDraw(OBJData* Pj);
void SetLife(OBJData* Pj, int Life);

void MinasNowOLDNum(void);
void PorYChange(void);
bool GetYChange(void);
void SetAutomatic(OBJData* Pj,D3DXVECTOR3 MovePos);
D3DXVECTOR3 RetOldPos(void);
#endif//Player_H