#pragma once
#include "Player.h"
#include "Cube.h"
#include "KeyLoggerr.h"
#include "Transform.h"
#include "NoriUturi.h"
bool NoriPorY = false;//falseがプレイヤー
int NoriMoveF = 0;
void NoriuturiInitialize(OBJData* Pj)
{
	for (int i = 1; i < 1024; i++)
	{
		if ((Pj + i)->Type == 1)
		{
			NoriMoveF = 0;
			//(Pj + i)->Pos = D3DXVECTOR3(1, 0, 0);
			(Pj + i)->Rot = D3DXVECTOR3(0, 0, 0);
			(Pj + i)->Size = D3DXVECTOR3(1, 1, 1);
			(Pj + i)->MovePos = D3DXVECTOR3(0, 0, 0);
			//	(Pj + i)->Life = 5;		//(Pj + i)->Existence = 1;
			(Pj + i)->TextureID = Texture_SetTextureLoadFile("Asset\\NoriNum.png");
		}
	}
}

//デバッグフォントモジュールの終了処理
void NoriuturiFinalize(OBJData* Pj)
{
	for (int i = 1; i < 1024; i++)
	{
		if ((Pj + i)->Type == 1)
		{
			(Pj + i)->Pos = D3DXVECTOR3(0, 0, 0);
			(Pj + i)->MovePos = D3DXVECTOR3(0, 0, 0);
			(Pj + i)->Life = 1;
			(Pj + i)->Existence = 1;
			Texture_Release(&(Pj + i)->TextureID, 1);
		}
	}
}
void NoriuturiUpdate(OBJData* Pj)
{
	//for (int i = 1; i < 1024; i++)
	{
	//	if ((Pj + i)->Type == 'N')
		{

		}
	}
	
}

void NoriuturiDraw(OBJData* Pj)
{
	for (int i = 1; i < 1024; i++)
	{
		if ((Pj + i)->Existence == true && (Pj + i)->Type == 1)
		{
			Cube_DrawSetSys(&SetTransform((Pj + i)->Pos.x, (Pj + i)->Pos.y, (Pj + i)->Pos.z, (Pj + i)->Rot.x, (Pj + i)->Rot.y, (Pj + i)->Rot.z, (Pj + i)->Size.x, (Pj + i)->Size.y, (Pj + i)->Size.z), (Pj + i)->TextureID, (Pj + i)->Life);
		}

	}
}
void SetLife(OBJData* Pj, int Life,int i)
{
	(Pj+i)->Life = Life;
}