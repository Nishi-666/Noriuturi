#include "Player.h"
#include "Cube.h"
#include "KeyLoggerr.h"
#include "Transform.h"
#include "NoriUturi.h"
#define MOVE_SPD (1.0f)
bool NoriPorY = false;//falseがプレイヤー
int NoriMoveF = 0;
void NoriuturiInitialize(OBJData* Pj)
{

	for (int i = 1; i < 2; i++)
	{
		NoriMoveF = 0;
		(Pj + i)->Pos = D3DXVECTOR3(1, 0, 0);
		(Pj + i)->Rot = D3DXVECTOR3(0, 0, 0);
		(Pj + i)->Size = D3DXVECTOR3(1, 1, 1);
		(Pj + i)->MovePos = D3DXVECTOR3(0, 0, 0);
		(Pj + i)->Life = 5;
		(Pj + i)->Type = 'M';
		(Pj + i)->Existence = 1;
		(Pj + i)->TextureID = Texture_SetTextureLoadFile("Asset\\spice_and_wolf.png");
	}
}

//デバッグフォントモジュールの終了処理
void NoriuturiFinalize(OBJData* Pj)
{
	for (int i = 1; i < 2; i++)
	{
		(Pj + i)->Pos = D3DXVECTOR3(0, 0, 0);
		(Pj + i)->MovePos = D3DXVECTOR3(0, 0, 0);
		(Pj + i)->Life = 1;
		(Pj + i)->Type = ' ';
		(Pj + i)->Existence = 1;
		Texture_Release(&(Pj + i)->TextureID, 1);
	}
}
void NoriuturiUpdate(OBJData* Pj)
{
	for (int i = 1; i < 2; i++)
	{
	/*	if ((Pj + i)->MovePos.x == 0 && (Pj + i)->MovePos.y == 0 && (Pj + i)->Life > 0)
		{
			if (KeyLogger_Press(KL_UP))
			{
				(Pj + i)->MovePos.y = -0.01666666666;

			}
			if (KeyLogger_Press(KL_DOWN))
			{
				(Pj + i)->MovePos.y = 0.01666666666;
			}
			if (KeyLogger_Press(KL_LEFT))
			{
				(Pj + i)->MovePos.x = -0.01666666666;
				Beep(10, 100);

			}
			if (KeyLogger_Press(KL_RIGHT))
			{
				(Pj + i)->MovePos.x = 0.01666666666;
				Beep(10, 100);
			}
		}
		else
		{
			(Pj + i)->Pos += (Pj + i)->MovePos;
			NoriMoveF++;
			if (NoriMoveF > 60)
			{
				Beep(1000, 100);
				(Pj + i)->MovePos.x = 0;
				(Pj + i)->MovePos.y = 0;
				(Pj + i)->Life = (Pj + i)->Life - 1;
				NoriMoveF = 0;
			}
		}*/
	}
	//(Pj+i)->MovePos *= 0.5f;
	
}

void NoriuturiDraw(OBJData* Pj)
{
	for (int i = 1; i < 2; i++)
	{
		if ((Pj+i)->Existence)
		{
			Cube_Draw(&SetTransform((Pj + i)->Pos.x, (Pj + i)->Pos.y, (Pj + i)->Pos.z, (Pj + i)->Rot.x, (Pj + i)->Rot.y, (Pj + i)->Rot.z, (Pj + i)->Size.x, (Pj + i)->Size.y, (Pj + i)->Size.z));
		}
	}
}
void SetLife(OBJData* Pj, int Life,int i)
{
	(Pj+i)->Life = Life;
}