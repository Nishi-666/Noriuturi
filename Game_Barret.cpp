#include "Game_Player.h"
#include "TexMan.h"
#include "Sprite.h"
#include "Collision.h"
#include "sound.h"
#define BARRET_MAX (2048)
#define BARRET_W (42)
#define BARRET_H (11)
//構造体宣言
	//Barret構造体
typedef struct Barret_Tag
{
	D3DXVECTOR2 Pos;
	D3DXVECTOR2 MovePos;
	double Angle;
	bool Enable;
}Barret;
//グローバル変数
static int g_BarretTextureID = TEXTURE_INVALID_ID;
static Barret g_Barrets[BARRET_MAX];
#define BARRET_WHIDTH (42)//弾幅
#define BARRET_HEIGHT (11)//弾高さ

//弾の初期化
void GameBarret_initialize(void)
{
	if (g_BarretTextureID == TEXTURE_INVALID_ID)
	{
		g_BarretTextureID = Texture_SetTextureLoadFile("Asset\\stg0722.png");
	}
	if (Texture_Load() > 0)
	{
		MessageBox(NULL, "アプリケーション終了します", "Aテクスチャの読み込みが失敗しましたのでDA", MB_OK);//OKを押されるまでプログラムがとまる
		return;
	}
	else
	{
		//MessageBox(NULL, "OK", "テクスチャ読み込み", MB_OK);//OKを押されるまでプログラムがとまる
	}
	for (int i = 0; i < BARRET_MAX; i++)
	{
		g_Barrets->Enable = D3DXVECTOR2(0.0f, 0.0f);
		g_Barrets->Pos = D3DXVECTOR2(0.0f, 0.0f);
		g_Barrets->Angle = 0;
		g_Barrets->Enable = false;
	}
}

void GameBarret_Reset(void)
{
	for (int i = 0; i < BARRET_MAX; i++)
	{
		g_Barrets->Enable = D3DXVECTOR2(0.0f, 0.0f);
		g_Barrets->Pos = D3DXVECTOR2(0.0f, 0.0f);
		g_Barrets->Angle = 0;
		g_Barrets->Enable = false;
	}

}
//弾の終了
void GameBarret_Finalize(void)
{
	Texture_Release(&g_BarretTextureID, 1); 
	for (int i = 0; i < BARRET_MAX; i++)
	{

		g_Barrets->Pos = D3DXVECTOR2(0.0f, 0.0f);
		g_Barrets->Enable = false;
	}

}

//弾の更新
void GameBarret_Update(void)
{
	for (int i = 0; i < BARRET_MAX; i++)
	{

		//弾が有効か調べる
		if ((g_Barrets+i)->Enable)
		{
			(g_Barrets + i)->Pos.x += (g_Barrets + i)->MovePos.x;
			(g_Barrets + i)->Pos.y += (g_Barrets + i)->MovePos.y;
			
			//弾座標更新
			if ((g_Barrets + i)->Pos.x > SCREEN_WHIDTH || (g_Barrets + i)->Pos.x < -100)
			{
				(g_Barrets + i)->Enable = false;
			}
		}
	}
	//何かの条件で弾を無効にする
}

//弾の描画
void GameBarret_Draw(void)
{


	for (int i = 0; i < BARRET_MAX; i++)
	{

		//弾が有効か調べる
		if ((g_Barrets + i)->Enable)
		{
			//弾を描画する

			int BarretTypeX = 0;
			int BarretTypeY = 0;

			//SpriteDraw(Work_texture, PosX, PosY, tcx, tcy, DEBUG_FONT_WIDTH, DEBUG_FONT_HEIGHT);
			//SpriteDraw(g_textureID, 400, 320.0f, 32.0f, 32.0f, tcx, 0, 32, 32, 16, 16, f);

			//void SpriteDraw(int TextureId, float DX, float DY, float DW, float DH, int ctx, int cty, int ctw, int cth, float cx, float cy, float angle)
			//void SpriteDraw(int TextureId, float DX, float DY, int ctx, int cty, int ctw, int cth, float cx, float cy, float angle)

	//dx,dy =描画座標
	//dw ポリゴンサイズ幅
	//ctx.cty= テクスチャ切り抜き座標
	//ctw,cth= テクスチャの切り取り高さ
	// cx  回転拡大の中心座標x
	// cy  回転拡大の中心座標y
	//angle    :ポリゴンの回転角度(ラジアン)
	//float v4 = 96 / 512.f;
			


			SpriteDraw(g_BarretTextureID, (g_Barrets + i)->Pos.x,
				(g_Barrets + i)->Pos.y, 0 * BARRET_W, 0 * BARRET_H, BARRET_W, BARRET_H, (g_Barrets + i)->Pos.x + (BARRET_W / 2),
				(g_Barrets + i)->Pos.y + (BARRET_H / 2), (g_Barrets + i)->Angle, 1);


			//なんか変なエラー起きてる
		/*	SpriteDraw(g_BarretTextureID, (g_Barrets + i)->Pos.x, 
				(g_Barrets + i)->Pos.y,//dy
				BarretTypeX * 42, //ctx
				BarretTypeX * 11, 
				42//ctw
			, 11,//cth
				((g_Barrets + i)->Pos.x + 21)//cx
				, ((g_Barrets + i)->Pos.y + 5.6f),//cy
				(g_Barrets + i)->Angle);// DrawPosX + (DEBUG_FONT_WIDTH / 2), DrawPosY + (DEBUG_FONT_HEIGHT / 2), Rot);*/
		}
	}
}

//弾の生成
void GameBarret_Create(float x, float y, float MoveX, float MoveY,double angle)
{


	for (int i = 0; i < BARRET_MAX; i++)
	{

		//弾が有効か調べる
		if (!(g_Barrets + i)->Enable)
		{//弾を追加
			(g_Barrets + i)->Pos.x = x;
			(g_Barrets + i)->Pos.y = y;
			(g_Barrets + i)->MovePos.x = MoveX;
			(g_Barrets + i)->MovePos.y = MoveY;
			(g_Barrets + i)->Angle = angle;

			PlaySound(SOUND_LABEL_SE_SHOT);
			(g_Barrets + i)->Enable = true;
			break;
		}
		
	}
}
CircleCollision GameBarret_GetCollision(int Num)
{
	CircleCollision C = { {(g_Barrets + Num)->Pos.x + BARRET_WHIDTH*0.5f,(g_Barrets + Num)->Pos.y +BARRET_HEIGHT*0.5f},
		BARRET_WHIDTH*0.5f };

	return C;
}

void GameBarret_Despawn(int Num)
{
	(g_Barrets + Num)->Enable = false;
}
bool GameBarret_IsEnable(int Num)
{
	return (g_Barrets + Num)->Enable;
}
int GameBarret_GetMax(void)
{
	return BARRET_MAX;
}