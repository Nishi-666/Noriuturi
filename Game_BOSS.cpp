/*============================================================

ゲームの敵処理[Game_Boss.cpp]                           Author:Kai Yamaya
												   Date:2020/7/21
-------------------------------------------------------

==============================================================*/
#include "Game_BOSS.h"
#include "TexMan.h"
#include <string.h>
#include "Sprite.h"
#include "GameEnemy_Barret.h"
#include "Game_GND.h"

#define BOSS_WHIDTH (94)//スクリーン幅
#define BOSS_HEIGHT (34)//スクリーン高さ
#define BOSS_MAX (2048)
//#include "Collision.h"
//ゲームプレイヤーの初期化
typedef struct
{
	D3DXVECTOR2 Position;
	D3DXVECTOR2 MovePos;
	bool Enable;
	int HP;
	bool reverse;
}BOSSData;
BOSSData BD;
int StageBossData = 1;
static int g_BossTextureID = TEXTURE_INVALID_ID;
//static D3DXVECTOR2 g_BossPosition = D3DXVECTOR2(0.0f, 0.0f);
//static bool g_BossEnable = false;

void GameBoss_initialize(void)
{
	if (g_BossTextureID == TEXTURE_INVALID_ID)
	{
		g_BossTextureID = Texture_SetTextureLoadFile("Asset\\Boss.png");

		if (Texture_Load() > 0)
		{
			MessageBox(NULL, "アプリケーション終了します", "Aテクスチャの読み込みが失敗しましたのでDA", MB_OK);//OKを押されるまでプログラムがとまる
			return;
		}
	}
		BD.Position = D3DXVECTOR2(0.0f, 0.0f);
		BD.MovePos = D3DXVECTOR2(0.0f, 0.0f);
		BD.Enable = false;
		BD.HP = 30;
		BD.reverse = false;
	
}

//終了
void GameBoss_Finalize(void)
{
	Texture_Release(&g_BossTextureID, 1);
	BD.Position = D3DXVECTOR2(0.0f, 0.0f);
	BD.MovePos = D3DXVECTOR2(-10.0f, 0.0f);
	BD.Enable = false;
}
void GameBoss_Damage(int i)
{
	BD.HP -= i;
	if (BD.HP <= 0)
	{
		BD.Enable = false;
		StageAdd();
	}
}
void GameBoss_Reset(void)
{
	BD.Position = D3DXVECTOR2(0.0f, 0.0f);
	BD.MovePos = D3DXVECTOR2(0.0f, 0.0f);
	BD.Enable = false;
	BD.HP = 30;
	BD.reverse = false;
}
//更新
void GameBoss_Update(void)
{

	if (BD.Enable)
	{
		BD.Position.x += BD.MovePos.x;
		
		BD.Position.y += BD.MovePos.y;
		if (BD.Position.y > 520 && BD.reverse)
		{
			BD.MovePos.y = -BD.MovePos.y;
			BD.reverse = false;
		}if (BD.Position.y <100 && !BD.reverse)
		{
			BD.MovePos.y = -BD.MovePos.y;
			BD.reverse = true;
		}
		if ((BD.Position.x > SCREEN_WHIDTH + 200 && BD.MovePos.x > 0) || (BD.Position.x < -100 && BD.MovePos.x < 0))
		{
			BD.Enable = false;
		}
		int r = rand() % 60-(StageBossData*5);
		if (!r)
		{
			GameEnemyBarret_Create((float)BD.Position.x + 20, (float)BD.Position.y + 17,-11,0);
		}
	}	
}

//描画
void GameBoss_Draw(void)
{
	if (BD.Enable)
	{
		//弾を描画する

		int BossTypeX = 0;
		int BossTypeY = 0;

		//SpriteDraw(Work_texture, PosX, PosY, tcx, tcy, DEBUG_FONT_WIDTH, DEBUG_FONT_HEIGHT);
		//SpriteDraw(g_textureID, 400, 320.0f, 32.0f, 32.0f, tcx, 0, 32, 32, 16, 16, f);
		SpriteDraw(g_BossTextureID, BD.Position.x, BD.Position.y, BossTypeX * 94, (StageBossData%5) * 68, 94, 68);;// DrawPosX + (DEBUG_FONT_WIDTH / 2), DrawPosY + (DEBUG_FONT_HEIGHT / 2), Rot);
	}
}
//敵出現
void GameBoss_Spawn(float x, float y)
{
	if (!BD.Enable)
	{//ボス追加
		BD.Position.x = x;
		BD.Position.y = y;
		BD.MovePos.y =10;
		BD.Enable = true;
		BD.reverse = true;
		StageBossData = GetStage()-1;
	}
}
bool GameBoss_IsEnable(void)
{
	return BD.Enable;
}
D3DXVECTOR2 GetBoss_thisPos(void)
{
	return BD.Position;
}

CircleCollision GameBoss_GetCollision(void)
{

	CircleCollision C = { {BD.Position.x /*+ ENEEMY_WHIDTH*0.5f*/,BD.Position.y + BOSS_HEIGHT * 0.5f},BOSS_WHIDTH*0.5f };
	//	C.ceneter = g_BossPosition;
	//	C.radus = 34;
	return C;

}