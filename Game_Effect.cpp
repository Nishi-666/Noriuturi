#pragma once
#include "TexMan.h"
#include "Game.h"
#include "TexMan.h"
#include "Sprite.h"
#include<d3dx9.h>
#include "MyDirect3D.h"

#define EFFECT_MAX (2048)

//エフェクト構造体
typedef struct Effect_Tag
{
	D3DXVECTOR2 Pos;
	int BirthFrame;
	bool Enale;
}Effect;


static int Effect_texture = TEXTURE_INVALID_ID;
static Effect g_Effect[EFFECT_MAX];
static int g_FrameCount;
bool GameEffect_initialize(void)
{
	if (Effect_texture == TEXTURE_INVALID_ID)
	{
		Effect_texture = Texture_SetTextureLoadFile("Asset\\Efect.png");
	}
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		g_Effect[i].Enale = false;//未使用化
		g_Effect[i].BirthFrame = 0;
	}
	g_FrameCount = 0;
	return 1;
}
void GameEffect_Reset(void)
{
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		g_Effect[i].Enale = false;//未使用化
		g_Effect[i].BirthFrame = 0;
	}
	g_FrameCount = 0;

}
void GameEffect_Update(void)
{
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (!g_Effect[i].Enale)continue;
			
		int age =g_FrameCount-g_Effect[i].BirthFrame;

		if (age >= 60)
		{
			g_Effect[i].Enale = false;
		}
		
	}
	g_FrameCount++;
}
void GameEffect_Draw(void)
{

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

//	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	////pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	//加算合成の設定
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (!g_Effect[i].Enale)continue;

		int age = g_FrameCount - g_Effect[i].BirthFrame;
		float a = (1.0f-(1.0f / 60.0f) * age);
		D3DXCOLOR collar(1.0f, 1.0f, 1.0f, a);
		//↑加算合成の場合、R*a G*a B*aされる
		SpriteSetCollar(collar);
		SpriteDraw(Effect_texture, g_Effect[i].Pos.x, g_Effect[i].Pos.y, 0, 0, 64, 64);
	}
	SpriteSetCollar(D3DCOLOR_RGBA(255, 255, 255, 255));//元のブレンドに戻す
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
void GameEffect_Finalize(void)
{
	Texture_Release(&Effect_texture, 1);

}
void GameEffect_Spawn(float x, float y)
{
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (g_Effect[i].Enale)continue;
		g_Effect[i].Pos = D3DXVECTOR2(x, y);
		g_Effect[i].BirthFrame = g_FrameCount;
		g_Effect[i].Enale = true;
		break;
	}
}