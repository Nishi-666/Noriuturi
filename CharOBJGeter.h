#pragma once
#include "CharOBJ.h"
D3DXVECTOR3 CharOBJGetPos(OBJData* Pj,int Num);//当該数のposを確保
D3DXVECTOR3 CharOBJGetPos(OBJData* Pj, char Type[2], int Num);//当該TypeのNum番目のposを確保
D3DXVECTOR3 CharOBJGetRot(OBJData* Pj, int Num);//当該数のposを確保
D3DXVECTOR3 CharOBJGetRot(OBJData* Pj, char Type[2], int Num);//当該TypeのNum番目のposを確保
D3DXVECTOR3 CharOBJGetSize(OBJData* Pj, int Num);//当該数のposを確保
D3DXVECTOR3 CharOBJGetSize(OBJData* Pj, char Type[2], int Num);//当該TypeのNum番目のposを確保
//
//int  CharOBJGetType(OBJData* Pj, int Num);//当該数のTypeを確保