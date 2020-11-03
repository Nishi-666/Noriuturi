#include "Yuley.h"
#include "Cube.h"
#include "KeyLoggerr.h"
#include "Transform.h"
#include "CharOBJGeter.h"
#define MOVE_SPD (1.0f)
void YuleyInitialize(OBJData* Pj)
{
	(Pj+1)->Pos = D3DXVECTOR3(0, 0.5f, 0);
	(Pj+1)->Rot = D3DXVECTOR3(0, 0, 0);
	(Pj+1)->Size = D3DXVECTOR3(0.5, 0.5,0.5);
	(Pj+1)->MovePos = D3DXVECTOR3(0, 0, 0);
	(Pj+1)->Life = 1;
	(Pj+1)->Type = 'Y';
	(Pj+1)->Existence = 1;
	(Pj+1)->TextureID = Texture_SetTextureLoadFile("Asset\\spice_and_wolf.png");

}

//デバッグフォントモジュールの終了処理
void YuleyFinalize(OBJData* Pj)
{

	(Pj+1)->Pos = D3DXVECTOR3(0, 0, 0);
	(Pj+1)->MovePos = D3DXVECTOR3(0, 0, 0);
	(Pj+1)->Life = 1;
	(Pj+1)->Type = ' ';
	(Pj+1)->Existence = 1;
	Texture_Release(&(Pj+1)->TextureID, 1);
}
void YuleyUpdate(OBJData* Pj)
{
}
void YuleyControl(OBJData* Pj)
{

	if (KeyLogger_Press(KL_UP))
	{

	}
	if (KeyLogger_Press(KL_DOWN))
	{
	}
	if (KeyLogger_Press(KL_LEFT))
	{
		(Pj + 1)->MovePos.x = -MOVE_SPD;
	}
	if (KeyLogger_Press(KL_RIGHT))
	{
		(Pj + 1)->MovePos.x = MOVE_SPD;
	}
	(Pj + 1)->Pos += (Pj + 1)->MovePos;
	(Pj + 1)->MovePos *= 0.5f;
}

void YuleyDraw(OBJData* Pj)
{
	Cube_Draw(&SetTransform((Pj+1)->Pos.x, (Pj+1)->Pos.y, (Pj+1)->Pos.z, (Pj+1)->Rot.x, (Pj+1)->Rot.y, (Pj+1)->Rot.z, (Pj+1)->Size.x, (Pj+1)->Size.y, (Pj+1)->Size.z));
}
void YuleyPosChange(OBJData* Pj)
{
	D3DXVECTOR3 v3 = CharOBJGetPos(Pj,0);
	(Pj + 1)->Pos = v3;
}