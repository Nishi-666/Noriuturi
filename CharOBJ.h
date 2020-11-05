#pragma once
#include <d3dx9.h>
#include "TexMan.h"
typedef struct
{
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 MovePos;
	D3DXVECTOR3 Rot;
	D3DXVECTOR3 Size;
	bool Existence;//���݂��邩
	int Life;
	int Type;//0:player
	int TextureID = TEXTURE_INVALID_ID;
}OBJData;