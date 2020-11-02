/*============================================================

デバッグフォントモジュール[Debug_Font.h]                           Author:Kai Yamaya
												   Date:2020/7/13
-------------------------------------------------------

==============================================================
*/#ifndef DEBUG_FONT_H
#define DEBUG_FONT_H
//デバッグフォントモジュールの初期化
void DebugFont_initialize(void);
//デバッグフォントモジュールの終了処理
void DebugFont_finalize(void);
//デバッグフォントの表示
//引数:pString:デバッグ文字列へのポインタ
//Dx/Dyデバッグ座標への描画座標
void DebugFont_Draw(float Dx, float Dy, const char* pString, int FontNum);
#endif//DEBUG_FONT_H
void DebugFont_Draw(float Dx, float Dy, const char* pString, int FontNum, float FontSize);