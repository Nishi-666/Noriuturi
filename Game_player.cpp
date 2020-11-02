#include "Game_Player.h"
#include "Debug_Font.h"
#include "TexMan.h"
#include "Player.h"
#include <string.h>
#include "Sprite.h"
#include <stdio.h>
#include <time.h>

#define DEBUG_FONT_WIDTH (140)
#define DEBUG_FONT_HEIGHT (200)
#define TART_CHAR_CODE (32)
#define END_CHAR_CODE (126)
#define LINE_CHAR_WIDTH (5)
#define LINE_CHAR_HEIGHT (2)



static int Work_texture = TEXTURE_INVALID_ID;
int Woak = 1, DrawPosX = 320 - (DEBUG_FONT_WIDTH / 2), DrawPosY = (SCREEN_HEIGHT / 4) - (DEBUG_FONT_HEIGHT / 2), DataRotNum;
int PosX = 0, PosY = 0;//DrawPosはただ単にゲーム上の描画用でここが現位置
float Rot = 0;
float DataPow = 0, DataRot = 0;
clock_t start, Nou;

//ゲームプレイヤーの初期化
void GamePlayer_initialize(void)
{

	
	LPDIRECT3DDEVICE9 g_pDevice = MyDirect3D_GetDevice();
	if (!g_pDevice)
	{
		return;
	}
	//テクスチャの読み込み予約//DirectX勉強用\DX-04 テクスチャマネージャ\DX-02 MessageBox\Asset
	Work_texture = Texture_SetTextureLoadFile("Asset\\runningman100.png");
	if (Texture_Load() > 0)
	{
		MessageBox(NULL, "アプリケーション終了します", "テクスチャの読み込みが失敗しましたのでDA", MB_OK);//OKを押されるまでプログラムがとまる
		return;
	}
	else
	{
		//MessageBox(NULL, "OK", "テクスチャ読み込み", MB_OK);//OKを押されるまでプログラムがとまる
	}
}

//終了
void GamePlayer_Finalize(void)
{
	Texture_Release(&Work_texture, 1);
}

//更新
void GamePlayer_Update(void)
{
	Nou = clock();
}

//描画
void GamePlayer_Draw(void)
{
	//dx,dy =描画座標
	//dw ポリゴンサイズ幅
	//ctx.cty= テクスチャ切り抜き座標
	//ctw,cth= テクスチャの切り取り高さ
	//void SpriteDraw(int TextureId, float DX, float DY, float DW, float DH, int ctx, int cty, int ctw, int cth);
	/*バックグラウンド用*/
	//PolygonDraw(0, 0, SCREEN_WHIDTH, SCREEN_HEIGHT, 0, 0, 255, 255);
	//PolygonDraw(0, (SCREEN_HEIGHT / 2) + PosY, SCREEN_WHIDTH, SCREEN_HEIGHT, 0, 255, 0, 255);


	int tcx = Woak % LINE_CHAR_WIDTH*DEBUG_FONT_WIDTH;
	int tcy = Woak / LINE_CHAR_HEIGHT * DEBUG_FONT_HEIGHT;
	SpriteDraw(Work_texture, PosX, PosY, tcx, tcy, DEBUG_FONT_WIDTH, DEBUG_FONT_HEIGHT);
	//SpriteDraw(g_textureID, 400, 320.0f, 32.0f, 32.0f, tcx, 0, 32, 32, 16, 16, f);
	SpriteDraw(Work_texture, DrawPosX, DrawPosY, tcx, tcy, DEBUG_FONT_WIDTH, DEBUG_FONT_HEIGHT, DrawPosX + (DEBUG_FONT_WIDTH / 2), DrawPosY + (DEBUG_FONT_HEIGHT / 2), Rot);

}

//ゲームプレイヤー移動
void GamePlayer_MoveUp(void)
{

}
void GamePlayer_MoveDown(void)
{

}
void GamePlayer_MoveLeft(void) 
{

}
void GamePlayer_MoveRight(void)
{

}
