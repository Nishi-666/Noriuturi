#pragma once
#include "CharOBJ.h"
D3DXVECTOR3 CharOBJGetPos(OBJData* Pj,int Num);//���Y����pos���m��
D3DXVECTOR3 CharOBJGetPos(OBJData* Pj, int Type,  int Num);//���YType��Num�Ԗڂ�pos���m��
D3DXVECTOR3 CharOBJGetRot(OBJData* Pj, int Num);//���Y����pos���m��
D3DXVECTOR3 CharOBJGetRot(OBJData* Pj, int Type,  int Num);//���YType��Num�Ԗڂ�pos���m��
D3DXVECTOR3 CharOBJGetSize(OBJData* Pj, int Num);//���Y����pos���m��
D3DXVECTOR3 CharOBJGetSize(OBJData* Pj, int Type, int Num);//���YType��Num�Ԗڂ�pos���m��
int CharOBJGetType(OBJData* Pj,int x,int y);//���YType��Num�Ԗڂ�pos���m��
//
//int  CharOBJGetType(OBJData* Pj, int Num);//���Y����Type���m��