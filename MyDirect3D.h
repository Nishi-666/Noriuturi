//
//使い方関係をぶっこむ

#include <d3d9.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "Config.h"
#ifdef  MY_DIRECT3D_H_
#define MY_DIRECT3D_H_


#endif //  MY_DIRECT3D_H_
//Direct3D9の初期化、失敗時は0を投下
bool MyDirect3D_initialize(HWND hw);
//Direct3D9の終了処理、失敗時は0を投下
void MyDirect3D_Finalize(void);
//D3Dデバイスの取得
LPDIRECT3DDEVICE9 MyDirect3D_GetDevice(void);
LPDIRECT3D9 MyDirect3D_GetLPDIRECT3D9(void);


//変数はヘッダに書いちゃダメ