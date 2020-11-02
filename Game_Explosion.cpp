/*============================================================

ゲームの敵処理[Game_Explosion.cpp]                           Author:Kai Yamaya
												   Date:2020/7/21
-------------------------------------------------------

==============================================================*/
#include "Game_Enemy.h"
#include "TexMan.h"
#include <string.h>
#include "Sprite.h"
#include "GameEnemy_Barret.h"

#include "Game_Explosion.h"

#define ENEEMY_WHIDTH (94)//スクリーン幅
#define Explosion_HEIGHT (34)//スクリーン高さ
//#include "Collision.h"
//ゲームプレイヤーの初期化

static int g_ExplosionTextureID = TEXTURE_INVALID_ID;
//static D3DXVECTOR2 g_ExplosionPosition = D3DXVECTOR2(0.0f, 0.0f);
//static bool g_ExplosionEnable = false;
//static int ExpAnime = 0;

typedef struct EXPData
{
	 D3DXVECTOR2 g_ExplosionPosition = D3DXVECTOR2(0.0f, 0.0f);
	 bool g_ExplosionEnable = false;
	 int ExpAnime = 0;

}EXPData;

EXPData EPD[20];
void GameExplosion_initialize(void)
{
	if (g_ExplosionTextureID == TEXTURE_INVALID_ID)
	{
		g_ExplosionTextureID = Texture_SetTextureLoadFile("Asset\\exp.png");
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
	for (int i = 0; i < 20; i++)
	{
		EPD[i].g_ExplosionPosition = D3DXVECTOR2(0.0f, 0.0f);
		EPD[i].g_ExplosionEnable = false;
		EPD[i].ExpAnime = 0;
	}
}
void GameExplosion_Reset(void)
{

}

//終了
void GameExplosion_Finalize(void)
{

	Texture_Release(&g_ExplosionTextureID, 1);
	for (int i = 0; i < 20; i++)
	{
		EPD[i].g_ExplosionPosition = D3DXVECTOR2(0.0f, 0.0f);
		EPD[i].g_ExplosionEnable = false;
		EPD[i].ExpAnime = 0;
	}

}
void GameExplosion_Despawn(int i)
{
	EPD[i].g_ExplosionEnable = false;
}

//更新
void GameExplosion_Update(void)
{

	for (int i = 0; i < 20; i++)
	{//弾が有効か調べる
		if (EPD[i].g_ExplosionEnable)
		{
			EPD[i].g_ExplosionPosition.x -= 10;
			//弾座標更新
			if (EPD[i].g_ExplosionPosition.x > SCREEN_WHIDTH || EPD[i].g_ExplosionPosition.x < -100)
			{
				EPD[i].g_ExplosionEnable = false;
			}
		}
	}
	//何かの条件で弾を無効にする
}

//描画
void GameExplosion_Draw(void)
{
	for (int i = 0; i < 20; i++)
	{
		if (EPD[i].g_ExplosionEnable)
		{
			//弾を描画する

			int tcx = EPD[i].ExpAnime % 4 * 32;
			int tcy = EPD[i].ExpAnime / 2 * 32;
			//SpriteDraw(Work_texture, PosX, PosY, tcx, tcy, DEBUG_FONT_WIDTH, DEBUG_FONT_HEIGHT);
			//SpriteDraw(g_textureID, 400, 320.0f, 32.0f, 32.0f, tcx, 0, 32, 32, 16, 16, f);
			SpriteDraw(g_ExplosionTextureID, EPD[i].g_ExplosionPosition.x, EPD[i].g_ExplosionPosition.y, tcx, tcy, 32, 32);// , g_ExplosionPosition.x + (32 / 2), g_ExplosionPosition.y + (32 / 2), Rot, 1.0f);

		}
	}
}
//敵出現
void GameExplosion_Spawn(float x, float y)
{
	for (int i = 0; i < 20; i++)
	{
		if (!EPD[i].g_ExplosionEnable)
		{//弾を追加
			EPD[i].g_ExplosionPosition.x = x;
			EPD[i].g_ExplosionPosition.y = y;
			EPD[i].g_ExplosionEnable = true;
		}
	}
}
bool GameExplosion_IsEnable(int i)
{
	return EPD[i].g_ExplosionEnable;
}
CircleCollision GameExplosion_GetCollision(int i)
{
	CircleCollision C = { {EPD[i].g_ExplosionPosition.x /*+ ENEEMY_WHIDTH*0.5f*/,EPD[i].g_ExplosionPosition.y + Explosion_HEIGHT * 0.5f},ENEEMY_WHIDTH*0.5f };
	//	C.ceneter = g_ExplosionPosition;
	//	C.radus = 34;
	return C;
}