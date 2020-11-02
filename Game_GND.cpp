#pragma once
#include "Game.h"
#include "Score.h"
#include "Debug_Font.h"
#include "TexMan.h"
#include <string.h>
#include "Sprite.h"
#include "Game_Barret.h"
#include "Game_Enemy.h"
#include "Game_BOSS.h"
#include <stdio.h>
#include <time.h>
#define MaxGND (30)
int NowSPRData = 0;//現在いくつまで描画しているのか
int FastSPRData = 0;//最初位置
int LASTSPRData = 0;//最終位置(ボス部屋到達1つ前のデータ
int MAXHeightData = 4;//最大階
float WalkData = 0;
typedef struct
{
	int SPRData;//0:まな板、RJ,千早 -1:下降 +1:上昇
	int Height;//何階か
}GNDData;
GNDData GD[MaxGND];
static int GND_texture = TEXTURE_INVALID_ID;
static int GND_UP_texture = TEXTURE_INVALID_ID;
static int GND_DOWN_texture = TEXTURE_INVALID_ID;
bool BossRis = false;
void GameGND_initialize(void)
{
	WalkData = 0;
	LPDIRECT3DDEVICE9 g_pDevice = MyDirect3D_GetDevice();
	if (!g_pDevice)
	{
		return;
	}
	if (GND_texture == TEXTURE_INVALID_ID)
	{
		GND_texture = Texture_SetTextureLoadFile("Asset\\GND.png");
		GND_UP_texture = Texture_SetTextureLoadFile("Asset\\UTriangle.png");
		GND_DOWN_texture = Texture_SetTextureLoadFile("Asset\\LTriangle.png");
		if (Texture_Load() > 0)
		{
			MessageBox(NULL, "アプリケーション終了します", "テクスチャの読み込みが失敗しましたのでDA", MB_OK);//OKを押されるまでプログラムがとまる
			return;
		}
	}

	GD[0].SPRData = 0;
	GD[0].Height = 1;
	GD[1].SPRData = 0;
	GD[1].Height = 1;
	//横幅1280なので１ブロック100として運用して現段階で16回(0:左画面外,13:右端+画面一部外,14:画面外移動時の予備、15:0の画面外が消えた後のバッファ
	for (int i = 2; i < MaxGND-16; i++)
	{
		
		int r = (rand() % 3+1)-1;

		if (GD[i - 1].Height + r >= MAXHeightData)
		{
			r = (rand() % 3) - 1;
		}
		GD[i].SPRData = r;
		GD[i].Height = GD[i - 1].Height + r;
		if (r != 0)
		{
			for (int s = 1; s < rand() % 12; s++)
			{
				GD[i + s].SPRData = 0;
				GD[i + s].Height = GD[i].Height;
			}
		}
		else
		{
			GD[i].SPRData = r;
			GD[i].Height = GD[i - 1].Height + r;
		}
		for (int i = MaxGND-16; i < MaxGND ; i++)
		{
			GD[i].SPRData = 0;
			GD[i].Height = 1;


		}

		/*
		if (GD[i - 1].Height + r == 0)
		{
			r += 1;
		}
		if (GD[i - 1].Height +r > MAXHeightData)
		{
			r = (rand() % 3) - 1;
		}
		GD[i].SPRData = r;
		GD[i].Height = GD[i - 1].Height + r;*/
	}
}

//終了
void GameGND_Finalize(void)
{

}

//更新
void GameGND_Update(void)
{
	if (((int)WalkData) < MaxGND - 16)
	{
		WalkData += 0.01;//強制スクロールシューティングゲーム(ボス戦除く
	}
	else
	{
		if (!BossRis)
		{
			GameBoss_Spawn(SCREEN_WHIDTH-100,0);
			BossRis = true;
		}
	}
	//敵リスポン命令(ここで発令する意味としてはWalkData値が小数点０の場合にランダムで発令しその他位置などGNDが広くかかわっているためである)
	if (((int)(WalkData*100))%100 ==0)
	{
		if (rand() % 2 == 0 &&!BossRis)
		{//発動
			int r = 1+rand() % 6;
			int my = (rand() % 3) * 100;
			for (int i = 0; i < r; i++)
			{
				GameEnemy_Spawn(SCREEN_WHIDTH + 100+(i*150), 620 - ((GD[(int)WalkData + 14].Height) * 100)-my);
			}
		}else if (rand() % 50 == 0 && BossRis)
		{
			int r = 1 + rand() %2;
			int my = (rand() % 3) * 100;
			for (int i = 0; i < r; i++)
			{
				GameEnemy_Spawn(SCREEN_WHIDTH + 100 + (i * 150), 620 - ((GD[(int)WalkData + 14].Height) * 100) - my);
			}
		}
	}
	

}

//描画-
void GameGND_Draw(void)
{
	for (int i = (int)WalkData; i < 16 + (int)WalkData; i++)
	{//ここをどうやって運用するか
		if ((GD[i].Height - 1) != 0)
		{
			for (int s = 0; s < GD[i].Height - 1; s++)
			{
				SpriteDraw(GND_texture, -100 + (i * 100)-((int)(WalkData*100)), 620 - (s * 100), 0, 0, 100, 100);
			}
		}
		if (!GD[i].SPRData)
		{
			SpriteDraw(GND_texture, -100 + (i * 100) - ((int)(WalkData * 100)), 620-((GD[i].Height-1)*100), 0, 0, 100, 100);
		}
		else if (GD[i].SPRData==-1)
		{
			SpriteDraw(GND_DOWN_texture, -100 + (i * 100) - ((int)(WalkData * 100)), 620 - ((GD[i].Height - 1) * 100), 0, 0, 100, 100);
		}
		else// if (GD[i].SPRData == 1)
		{
			SpriteDraw(GND_UP_texture, -100 + (i * 100) - ((int)(WalkData * 100)), 620 - ((GD[i].Height - 1) * 100), 0, 0, 255, 255,0.39f);
		}
	}
	
}
float GameGND_GetY(float Pos)
{
	//Pos = (Pos+100) / 100;//1ブロックが100であるからこれを利用
	float Ws = ((Pos + 100) / 100) + WalkData;
	int SPRWs = GD[(int)Ws].SPRData;
	int HeightWs = (620-(GD[(int)Ws].Height*100));
	if (SPRWs == 1)
	{//階段などの段差であれば
		HeightWs += (fmod(Pos, 1) * 100);
	}else if (SPRWs == -1)
	{//階段などの段差であれば
		HeightWs -= (fmod(Pos, 1) * 100);
	}
	return HeightWs;
}

int GameGND_GetSPR(float PosX)
{
	return	GD[(int)(WalkData + (PosX / 100)) - 2].SPRData;
}
int GameGND_GetHeightSPR(float PosX)
{
	return	GD[(int)(WalkData + (PosX / 100)) - 2].SPRData;
}
int GameGND_GetHeightPos(float PosX)
{
	return	620-((GD[(int)(WalkData + (PosX / 100)) - 1].Height)*100);
}