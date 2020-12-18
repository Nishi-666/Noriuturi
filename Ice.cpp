/*============================================================

アイス[ICE.cpp]                           Author:Kai Yamaya
												   Date:2020/11/30
-------------------------------------------------------

==============================================================
*/
#include "TexMan.h"
#include "Cube.h"
#include "Transform.h"
#include "Ice.h"
#include "CharOBJ.h"
#define NONE_ICE (-1)//NONE_ICE=何も取っていない場合用

int ICESubTypeSample[3] = { 1,2,3 };//取る目的のアイス(この順番でだせば加点)
int ICESubType[3] = { NONE_ICE,NONE_ICE,NONE_ICE };//とりあえず確保した場合、ここに追加(↑と照合する
int ICELife[3] = { NONE_ICE,NONE_ICE,NONE_ICE };//↑の当該アイスのライフ用
//デバッグフォントモジュールの初期化
void ICEInitialize(OBJData* Pj)
{
	
	for (int i = 1; i < 1024; i++)
	{
		if ((Pj + i)->Type == 4)
		{
			//とりあえず4を仮定でアイスにするものとする
			//(Pj + i)->Pos = D3DXVECTOR3(1, 0, 0);
			(Pj + i)->Rot = D3DXVECTOR3(0, 0, 0);
			(Pj + i)->Size = D3DXVECTOR3(1, 1, 1);
			(Pj + i)->MovePos = D3DXVECTOR3(0, 0, 0);
			(Pj + i)->Existence = true;
			(Pj + i)->Life = 1;
			//	(Pj + i)->Life = 5;		//(Pj + i)->Existence = 1;
			(Pj + i)->TextureID = Texture_SetTextureLoadFile("Asset\\NoriNum.png");
			(Pj + i)->SubType = NONE_ICE;
		}
	}
}
//デバッグフォントモジュールの終了処理
void ICEFinalize(OBJData* Pj)
{
	for (int i = 0; i < 3; i++)
	{
		ICESubTypeSample[i] = NONE_ICE;//取る目的のアイス(この順番でだせば加点)
		ICESubType[i] = NONE_ICE;//とりあえず確保した場合、ここに追加(↑と照合する
		ICELife[i] = NONE_ICE;//↑の当該アイスのライフ用
		
	}
	for (int i = 1; i < 1024; i++)
	{
		if ((Pj + i)->Type == 4)
		{
			(Pj + i)->SubType = NONE_ICE;
		}
	}
}
void ICEUpdate(OBJData* Pj)
{
	

}
void ICECollision(OBJData* Pj)
{
	for (int i = 1; i < 1024; i++)
	{
		if (Pj->Pos.x == (Pj + i)->Pos.x&&Pj->Pos.y == (Pj + i)->Pos.y && (Pj + i)->Existence && (Pj + i)->Type == 4 && (Pj + i)->SubType!= NONE_ICE)
		{
			for (int s = 0; s < 3; s++)
			{
				if (ICESubType[s] == NONE_ICE)
				{
					ICESubType[s] = (Pj + i)->SubType;
					ICELife[s] = (Pj + i)->Life;
					(Pj + i)->Existence = false;
					(Pj + i)->SubType = NONE_ICE;
					break;
				}
			}

			//Beep(1000, 100);
		}
	}
}

void ICEDraw(OBJData* Pj)
{
	for (int i = 1; i < 1024; i++)
	{
		if ((Pj + i)->Existence == true && (Pj + i)->Type == 4 && (Pj + i)->SubType != NONE_ICE)
		{
			Cube_DrawSetSys(&SetTransform((Pj + i)->Pos.x, (Pj + i)->Pos.y, (Pj + i)->Pos.z, (Pj + i)->Rot.x, (Pj + i)->Rot.y, (Pj + i)->Rot.z, (Pj + i)->Size.x, (Pj + i)->Size.y, (Pj + i)->Size.z), (Pj + i)->TextureID, (Pj + i)->SubType);
		}
	}
}
int IECJudgement(void)
{
	for (int i = 0; i < 3; i++)
	{
		if (ICESubTypeSample[i] != ICESubType[i])
		{
			return 0;
		}
	}
	return 1;
}
void ICESetICE(OBJData* Pj)
{
	for (int i = 1; i < 1024; i++)
	{
		if ((Pj + i)->Type == 4 && (Pj + i)->SubType == NONE_ICE)
		{
			if (rand() % 2 == 0)
			{//2分の１でサブタイプ変更(アイスの種類変更)
				(Pj + i)->SubType = rand() % 4;
				(Pj + i)->Life = 5;
			}
		}
	}
}
void ICESetLife(OBJData* Pj, int Life)
{

}
void ICESetPos(OBJData* Pj, D3DXVECTOR2 Pos)
{

}
void ICELifeMinus()
{
	for (int s = 0; s < 3; s++)
	{
		if (ICELife[s] == NONE_ICE)
		{
			ICELife[s]--;

			if (ICELife[s] == 0)
			{
				ICELife[s] = NONE_ICE;
			}
		}
	}
}