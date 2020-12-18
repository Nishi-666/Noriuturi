#include "MoveGimmick.h"
#include "Transform.h"
#include "TexMan.h"
#include "Cube.h"
void MoveGimmickInitialize(OBJData* Pj)
{
	Beep(1000, 1000);
	for (int i = 1; i < 1024; i++)
	{
		if ((Pj + i)->Type == 5 || (Pj + i)->Type == 6 || (Pj + i)->Type == 7 || (Pj + i)->Type == 8)
		{
			if ((Pj + i)->Type == 5)
			{//ã
				(Pj + i)->TextureID = Texture_SetTextureLoadFile("Asset\\W.png");
			}
			if ((Pj + i)->Type == 6)
			{//‰º
				(Pj + i)->TextureID = Texture_SetTextureLoadFile("Asset\\S.png");
			}
			if ((Pj + i)->Type == 7)
			{//‰E
				(Pj + i)->TextureID = Texture_SetTextureLoadFile("Asset\\D.png");
			}
			if ((Pj + i)->Type == 8)
			{//¶
				(Pj + i)->TextureID = Texture_SetTextureLoadFile("Asset\\A.png");
			}

			(Pj + i)->Rot = D3DXVECTOR3(0, 0, 0);
			(Pj + i)->Size = D3DXVECTOR3(1, 1, 1);
			(Pj + i)->MovePos = D3DXVECTOR3(0, 0, 0);
			(Pj + i)->Existence = true;
			(Pj + i)->Life = 1;
		}
	}
}
void MoveGimmickFinalize(OBJData* Pj)
{
	for (int i = 1; i < 1024; i++)
	{
		if ((Pj + i)->Type == 5 || (Pj + i)->Type == 6 || (Pj + i)->Type == 7 || (Pj + i)->Type == 8)
		{
			(Pj + i)->MovePos = D3DXVECTOR3(0, 0, 0);
			(Pj + i)->Life = 1;
			(Pj + i)->Existence = 1;
			Texture_Release(&(Pj + i)->TextureID, 1);
		}
	}

}
void MoveGimmickUpdate(OBJData* Pj)
{

}

void MoveGimmickDraw(OBJData* Pj)
{
	for (int i = 1; i < 1024; i++)
	{
		if ((Pj + i)->Type == 5 || (Pj + i)->Type == 6 || (Pj + i)->Type == 7 || (Pj + i)->Type == 8)
		{
		//	if ((Pj + i)->Existence)
			{
				Cube_DrawSetSys(&SetTransform((Pj + i)->Pos.x, (Pj + i)->Pos.y, (Pj + i)->Pos.z, (Pj + i)->Rot.x, (Pj + i)->Rot.y, (Pj + i)->Rot.z, (Pj + i)->Size.x, (Pj + i)->Size.y, (Pj + i)->Size.z), (Pj + i)->TextureID, (Pj + i)->Life);


			}
		}

	}
}