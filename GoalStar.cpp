#pragma once
#include <d3dx9.h>
#include "CharOBJ.h"
#include "Transform.h"
#include "Cube.h"
#include "GoalStar.h"
D3DXVECTOR3 GoalStarPos[4] = {};
int g_BoxTextureId[4]={ TEXTURE_INVALID_ID , TEXTURE_INVALID_ID , TEXTURE_INVALID_ID , TEXTURE_INVALID_ID };
__int8 StarDifficulty[3] = {};
bool GoalStarGet[4] = {};
bool GoalStarExistence[4];
void SetTex(void)
{
	g_BoxTextureId[0] = Texture_SetTextureLoadFile("Asset\\Goal.png"); 
	if (Texture_Load() > 0)
	{
		MessageBox(NULL, "アプリケーション終了します", "テクスチャの読み込みが失敗しましたので", MB_OK);//OKを押されるまでプログラムがとまる
	}
	g_BoxTextureId[1] = Texture_SetTextureLoadFile("Asset\\Star01.png");
	if (Texture_Load() > 0)
	{
		MessageBox(NULL, "アプリケーション終了します", "テクスチャの読み込みが失敗しましたので", MB_OK);//OKを押されるまでプログラムがとまる
	}
	g_BoxTextureId[2] = Texture_SetTextureLoadFile("Asset\\Star02.png");
	if (Texture_Load() > 0)
	{
		MessageBox(NULL, "アプリケーション終了します", "テクスチャの読み込みが失敗しましたので", MB_OK);//OKを押されるまでプログラムがとまる
	}
	g_BoxTextureId[3] = Texture_SetTextureLoadFile("Asset\\Star03.png");
	if (Texture_Load() > 0)
	{
		MessageBox(NULL, "アプリケーション終了します", "テクスチャの読み込みが失敗しましたので", MB_OK);//OKを押されるまでプログラムがとまる
	}
}
void SetPos(bool GoalorStar, int Num, D3DXVECTOR3 Pos, __int8 Difficulty)
{
	GoalStarPos[GoalorStar + (GoalorStar*Num)] = Pos;
	GoalStarExistence[GoalorStar + (GoalorStar*Num)] = true;
	if (GoalorStar)
	{
		StarDifficulty[Num] = Difficulty;
	}
}
void GoalStarDraw(void)
{
	for (int i = 0; i < 4; i++)
	{
		if (GoalStarExistence[i])
		{
			Cube_Draw(&SetTransform(GoalStarPos[i].x, GoalStarPos[i].y, GoalStarPos[i].z, 0, 0, 0, 0.5f, 0.5f, 0.5f), g_BoxTextureId[i]);
		}
	}
}
int GoalStarJudgment(D3DXVECTOR3 pos)
{	//ゴール=戻り値0,スター=戻り値1~3までの設定したposの位置
	//該当なし=-1
	for (int i = 0; i < 4; i++)
	{
		if (GoalStarPos[i].x == pos.x && GoalStarPos[i].y == pos.y)
		{
			GoalStarGet[i]=true;
			GoalStarExistence[i] = false;
			return i;
		}
	}
	return -1;
}