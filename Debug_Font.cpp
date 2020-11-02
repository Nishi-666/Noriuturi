/*============================================================

デバッグフォントモジュール[Debug_Font.h]                           Author:Kai Yamaya
												   Date:2020/7/13
-------------------------------------------------------

==============================================================*/

#include "Debug_Font.h"
#include "TexMan.h"
#include <string.h>
#include "Sprite.h"

#define DEBUG_FONT_WIDTH (32)
#define DEBUG_FONT_RETOROT_WIDTH (32)
#define DEBUG_FONT_HEIGHT (64)
#define DEBUG_FONT_RETORO_HEIGHT (62)
#define TART_CHAR_CODE (32)
#define END_CHAR_CODE (126)
#define LINE_CHAR_COUNT (16)


static int g_TextureID = TEXTURE_INVALID_ID;
static int g_TextureRETROID = TEXTURE_INVALID_ID;

void DebugFont_initialize(void)
{

	LPDIRECT3DDEVICE9 g_pDevice = MyDirect3D_GetDevice();
	if (!g_pDevice)
	{
		return ;
	}
	//テクスチャの読み込み予約//DirectX勉強用\DX-04 テクスチャマネージャ\DX-02 MessageBox\Asset
	g_TextureID = Texture_SetTextureLoadFile("Asset\\debug_font_32x64.png");
	g_TextureRETROID = Texture_SetTextureLoadFile("Asset\\Debug_Font_RETRO2.png");
	if (Texture_Load() > 0)
	{
		MessageBox(NULL, "アプリケーション終了します", "テクスチャの読み込みが失敗しましたのでDA", MB_OK);//OKを押されるまでプログラムがとまる
		return ;
	}
	else
	{
	//	MessageBox(NULL, "OK", "テクスチャ読み込み", MB_OK);//OKを押されるまでプログラムがとまる
	}



	//g_TextureID = Texture_SetTextureLoadFile("Asset\\debug_font_32x64.png");
	//if (Texture_Load() > 0)
	//{
	//	MessageBox(NULL, "アプリケーション終了します", "テクスチャの読み込みが失敗しましたので", MB_OK);//OKを押されるまでプログラムがとまる
	//}
}
void DebugFont_finalize(void)
{
	Texture_Release(&g_TextureID, 1);
}
//デバッグフォントの表示
//Dx/Dyデバッグ座標への描画座標
//引数:pString:デバッグ文字列へのポインタ
void DebugFont_Draw(float Dx, float Dy, const char* pString, int FontNum)
{//32から126番までのフォント(スペースから"~"まで)//1行16
	for (int i = 0; i < strlen(pString); i++)
	{
		//dx,dy =描画座標
		//dw ポリゴンサイズ幅
		//ctx.cty= テクスチャ切り抜き座標
		//ctw,cth= テクスチャの切り取り高さ
		//void SpriteDraw(int TextureId, float DX, float DY, float DW, float DH, int ctx, int cty, int ctw, int cth);
		int offset = pString[i] - ' ';
		//	int tcx = offset % LINE_CHAR_COUNT*DEBUG_FONT_WIDTH;
		if (FontNum == 0) {
			int tcx = offset % LINE_CHAR_COUNT*DEBUG_FONT_WIDTH;
			int tcy = offset / LINE_CHAR_COUNT * DEBUG_FONT_HEIGHT;
			SpriteDraw(g_TextureID, Dx + (i* DEBUG_FONT_WIDTH), Dy, tcx, tcy, DEBUG_FONT_WIDTH, DEBUG_FONT_HEIGHT);
		}
		if (FontNum == 1) {
			int tcx = offset % LINE_CHAR_COUNT*DEBUG_FONT_RETOROT_WIDTH;
			int tcy = offset / LINE_CHAR_COUNT * DEBUG_FONT_RETORO_HEIGHT;
			SpriteDraw(g_TextureRETROID, Dx + (i* DEBUG_FONT_RETOROT_WIDTH), Dy, tcx, tcy, DEBUG_FONT_RETOROT_WIDTH, DEBUG_FONT_RETORO_HEIGHT);
		}
	}
}
void DebugFont_Draw(float Dx, float Dy, const char* pString, int FontNum, float FontSize)
{//32から126番までのフォント(スペースから"~"まで)//1行16
	for (int i = 0; i < strlen(pString); i++)
	{
		//dx,dy =描画座標
		//dw ポリゴンサイズ幅
		//ctx.cty= テクスチャ切り抜き座標
		//ctw,cth= テクスチャの切り取り高さ
		//void SpriteDraw(int TextureId, float DX, float DY, float DW, float DH, int ctx, int cty, int ctw, int cth);
		int offset = pString[i] - ' ';
		//	int tcx = offset % LINE_CHAR_COUNT*DEBUG_FONT_WIDTH;
		if (FontNum == 0) {
			int tcx = offset % LINE_CHAR_COUNT*DEBUG_FONT_WIDTH;
			int tcy = offset / LINE_CHAR_COUNT * DEBUG_FONT_HEIGHT;
			SpriteDraw(g_TextureID, Dx + (i* (DEBUG_FONT_RETOROT_WIDTH*FontSize)), Dy, tcx, tcy, DEBUG_FONT_WIDTH, DEBUG_FONT_HEIGHT,FontSize);
		}
		if (FontNum == 1) {
			int tcx = offset % LINE_CHAR_COUNT*DEBUG_FONT_RETOROT_WIDTH;
			int tcy = offset / LINE_CHAR_COUNT * DEBUG_FONT_RETORO_HEIGHT;
			SpriteDraw(g_TextureRETROID, Dx + (i* (DEBUG_FONT_RETOROT_WIDTH*FontSize)), Dy, tcx, tcy, DEBUG_FONT_RETOROT_WIDTH, DEBUG_FONT_RETORO_HEIGHT,FontSize);
		}
	}
}