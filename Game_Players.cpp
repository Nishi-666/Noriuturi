/*============================================================

デバッグフォントモジュール[Player.h]                           Author:Kai Yamaya
												   Date:2020/7/09
-------------------------------------------------------

==============================================================*/

#include "Debug_Font.h"
#include "TexMan.h"
#include "Player.h"
#include <string.h>
#include "Sprite.h"
#include "Game_Barret.h"
#include "Game_GND.h"
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "mouse.h"
#include "Game_Effect.h"

#define DEBUG_FONT_WIDTH (140)
#define DEBUG_FONT_HEIGHT (200)
#define TART_CHAR_CODE (32)
#define END_CHAR_CODE (126)
#define LINE_CHAR_WIDTH (5)
#define LINE_CHAR_HEIGHT (2)

#define Player_WHIDTH (140)//弾幅
#define Player_HEIGHT (200)//弾高さ

static int Work_texture = TEXTURE_INVALID_ID;
int  DrawPosX = 320- (DEBUG_FONT_WIDTH / 2), DrawPosY = (SCREEN_HEIGHT/4)- (DEBUG_FONT_HEIGHT / 2), DataRotNum;
float Woak = 1;
static D3DXVECTOR2 g_PlayerPosition(0.0f, 0.0f);//プレイヤー座標
static D3DXVECTOR2 g_PlayerDirection(0.0f, 0.0f);//プレイヤー進行方向
static float g_PlayerSpeed = 0.0f;				//プレイヤー速度
static float g_PlayerBaseVelocity =0.0f;			//プレイヤー加速度s
///int PosX = 0, PosY = 0;//DrawPosはただ単にゲーム上の描画用でここが現位置
static int g_GNDYpos =300;//現在のｙ位置
float Rot = 0;
int MouseXPos,MouseYPos;
bool g_PlayerEnable = true;
clock_t start, Nou;
double Radian;
int DeadCoolTimes = 0;
bool Deaddrawbool = false;
int ShotLag =0;
void GamePlayer_initialize(void)
{

	g_PlayerEnable = true;
	g_PlayerPosition = D3DXVECTOR2(32.0f, 520.0f);
	g_PlayerDirection = D3DXVECTOR2(0, 0);
	g_PlayerBaseVelocity = 14.0f;
	g_PlayerSpeed = 4.0f;
	LPDIRECT3DDEVICE9 g_pDevice = MyDirect3D_GetDevice();
	if (!g_pDevice)
	{
		return;
	}
	//テクスチャの読み込み予約//DirectX勉強用\DX-04 テクスチャマネージャ\DX-02 MessageBox\Asset
	if (Work_texture == TEXTURE_INVALID_ID)
	{
		Work_texture = Texture_SetTextureLoadFile("Asset\\runningman100.png");
		if (Texture_Load() > 0)
		{
			MessageBox(NULL, "アプリケーション終了します", "テクスチャの読み込みが失敗しましたのでDA", MB_OK);//OKを押されるまでプログラムがとまる
			return;
		}
	}



	//g_TextureID = Texture_SetTextureLoadFile("Asset\\debug_font_32x64.png");
	//if (Texture_Load() > 0)
	//{
	//	MessageBox(NULL, "アプリケーション終了します", "テクスチャの読み込みが失敗しましたので", MB_OK);//OKを押されるまでプログラムがとまる
	//}
	start = clock();
}

void GamePlayer_Reset(void)
{
	start = clock();
	g_PlayerPosition = D3DXVECTOR2(32.0f, 520.0f);
	g_PlayerDirection = D3DXVECTOR2(0, 0);
	g_PlayerBaseVelocity = 14.0f;
	g_PlayerSpeed = 4.0f;

}
void GamePlayer_Finalize(void)
{
	Texture_Release(&Work_texture, 1);
}
void GamePlayer_Update(void)
{
	ShotLag--;
	//進行方向を長さ１にする//正規化する
	D3DXVec2Normalize(&g_PlayerDirection, &g_PlayerDirection);
	Woak += 0.3f;
	//プレイヤー座標の更新(進行方向×速度)
	g_PlayerPosition += g_PlayerDirection * g_PlayerSpeed;
	g_PlayerSpeed *= 0.85f;
	g_GNDYpos = GameGND_GetY(g_PlayerPosition.x) - 100;
	MouseXPos = RetMouseX() - g_PlayerPosition.x + 70;
	MouseYPos = RetMouseY() - g_PlayerPosition.y + 100;
	Radian = atan2(MouseYPos - (g_PlayerPosition.y + 100), MouseXPos - (g_PlayerPosition.x + 70));
	if (g_PlayerPosition.y > g_GNDYpos)
	{
		g_PlayerPosition.y = g_GNDYpos;
	}
	else
	{
		g_PlayerPosition.y += 0.98f;
	}
	if (DeadCoolTimes != 0)
	{
		DeadCoolTimes--;
		if (DeadCoolTimes % 10)
		{
			Deaddrawbool = !Deaddrawbool;
		}
	}
}
	//デバッグフォントの表示
	//Dx/Dyデバッグ座標への描画座標
	//引数:pString:デバッグ文字列へのポインタ
void GamePlayer_Draw(void)
{//32から126番までのフォント(スペースから"~"まで)//1行16
	//for (int i = 0; i < strlen(pString); i++)
	{
		//dx,dy =描画座標
		//dw ポリゴンサイズ幅
		//ctx.cty= テクスチャ切り抜き座標
		//ctw,cth= テクスチャの切り取り高さ
		//void SpriteDraw(int TextureId, float DX, float DY, float DW, float DH, int ctx, int cty, int ctw, int cth);
		/*バックグラウンド用*/
	//	PolygonDraw(0, 0, SCREEN_WHIDTH, SCREEN_HEIGHT, 0, 0, 255, 255);
	//	PolygonDraw(0, (SCREEN_HEIGHT/2)+PosY, SCREEN_WHIDTH, SCREEN_HEIGHT, 0, 255,0, 255);

		if (g_PlayerEnable)
		{
			int tcx = (int)Woak % 5 * DEBUG_FONT_WIDTH;
			int tcy = (int)Woak / 2 * DEBUG_FONT_HEIGHT;

			///Y44X80
//			SpriteDraw(Work_texture, g_PlayerPosition.x, g_PlayerPosition.y, tcx, tcy, DEBUG_FONT_WIDTH, DEBUG_FONT_HEIGHT, DrawPosX + (DEBUG_FONT_WIDTH / 2), DrawPosY + (DEBUG_FONT_HEIGHT / 2), Rot, 1.0f);
			if (DeadCoolTimes == 0 || DeadCoolTimes != 0 && Deaddrawbool)
			{
				SpriteDraw(Work_texture, g_PlayerPosition.x, g_PlayerPosition.y, tcx, tcy, DEBUG_FONT_WIDTH, DEBUG_FONT_HEIGHT);
			}
			if (g_PlayerSpeed > 0.0001f)
			{
				GameEffect_Spawn(g_PlayerPosition.x, g_PlayerPosition.y);
			}
		}

	}
}
void GamePlayer_MoveUp(void)
{
	g_PlayerDirection.y = -1.0f;
	g_PlayerSpeed = g_PlayerBaseVelocity;
}
void GamePlayer_MoveDown(void)
{
	g_PlayerDirection.y = 1.0f;
	g_PlayerSpeed = g_PlayerBaseVelocity;
}
void GamePlayer_MoveLeft(void)
{

	g_PlayerDirection.x = -1.0f;
	g_PlayerSpeed = g_PlayerBaseVelocity;
}
void GamePlayer_MoveRight(void)
{

	g_PlayerDirection.x = 1.0f;
	g_PlayerSpeed = g_PlayerBaseVelocity;
}


void GamePlayer_Shot(void)
{
	if (g_PlayerEnable && ShotLag<1)
	{
		GameBarret_Create((g_PlayerPosition.x/2)+(Player_WHIDTH/4), (g_PlayerPosition.y/2) + (Player_HEIGHT / 4), cosf(Radian) * 5/*SPD*/, sinf(Radian) * 5/*SPD*/, Radian);
		ShotLag = 20;
	}
}

void GamePlayer_Despawn(void)
{
	g_PlayerEnable = false;
}

bool GamePlayer_IsEnable(void)
{
	return g_PlayerEnable;
}
CircleCollision GamePlayer_GetCollision(void)
{
	CircleCollision C = { {g_PlayerPosition.x + Player_WHIDTH * 0.5f,g_PlayerPosition.y + Player_HEIGHT * 0.5f},Player_WHIDTH*0.5f };
	//	C.ceneter = g_EnemyPosition;
	//	C.radus = 34;
	return C;
}
void SetDeadCoolTimes(void)
{
	DeadCoolTimes = 60 * 5;
}
bool GeTDeadCoolTimes(void)
{
	return (bool)DeadCoolTimes;//これでFalseの時にのみ実行する塩梅とする
}