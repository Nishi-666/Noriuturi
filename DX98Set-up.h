/*============================================================

DirectX-98(86)起動システム[Player.h]                   Author:Kai Yamaya
												   Date:2020/7/12
-------------------------------------------------------

==============================================================
*/#ifndef DX98_H
#define DX98_H
//デバッグフォントモジュールの初期化
void DX98Initialize(void);
//デバッグフォントモジュールの終了処理
void DX98Finalize(void);
void DX98Update(void);
void DX98Roop(void);

int DX98Draw(void);
#endif//DX98_H