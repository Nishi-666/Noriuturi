#pragma once
#include "Player.h"
#include "Cube.h"
#include "KeyLoggerr.h"
#include "Transform.h"
#include "Wall.h"
int WallTextureID = TEXTURE_INVALID_ID;
void WallInitialize(OBJData* Pj)
{
	WallTextureID = Texture_SetTextureLoadFile("Asset\\Wall.png"); 
	if (Texture_Load() > 0)
	{
		MessageBox(NULL, "�A�v���P�[�V�����I�����܂�", "�e�N�X�`���̓ǂݍ��݂����s���܂����̂�", MB_OK);//OK���������܂Ńv���O�������Ƃ܂�
	}
	for (int i = 1; i < 1024; i++)
	{
		if ((Pj + i)->Type == 2)
		{
			//(Pj + i)->Pos = D3DXVECTOR3(1, 0, 0);
			(Pj + i)->Rot = D3DXVECTOR3(0, 0, 0);
			(Pj + i)->Size = D3DXVECTOR3(1, 1, 1);
			(Pj + i)->MovePos = D3DXVECTOR3(0, 0, 0);
			//	(Pj + i)->Life = 5;		(Pj + i)->Existence = 1;
		}
	}
}

//�f�o�b�O�t�H���g���W���[���̏I������
void WallFinalize(OBJData* Pj)
{
	for (int i = 1; i < 1024; i++)
	{
		if ((Pj + i)->Type == 2)
		{
			(Pj + i)->Pos = D3DXVECTOR3(0, 0, 0);
			(Pj + i)->MovePos = D3DXVECTOR3(0, 0, 0);
			(Pj + i)->Life = 1;
			(Pj + i)->Existence = 1;
			Texture_Release(&WallTextureID, 1);
		}
	}
}
void WallUpdate(OBJData* Pj)
{
	//for (int i = 1; i < 1024; i++)
	{
		//	if ((Pj + i)->Type == 'N')
		{

		}
	}

}

void WallDraw(OBJData* Pj)
{
	for (int i = 1; i < 1024; i++)
	{
		if ((Pj + i)->Existence == true && (Pj + i)->Type == 2)
		{
			Cube_Draw(&SetTransform((Pj + i)->Pos.x, (Pj + i)->Pos.y, (Pj + i)->Pos.z, (Pj + i)->Rot.x, (Pj + i)->Rot.y, (Pj + i)->Rot.z, (Pj + i)->Size.x, (Pj + i)->Size.y, (Pj + i)->Size.z), WallTextureID);
		}

	}
}