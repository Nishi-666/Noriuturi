#pragma once
#include "CharOBJ.h"
D3DXVECTOR3 CharOBJGetPos(OBJData* Pj, int Num)//���Y����pos���m��
{
	return (Pj +Num)->Pos;
}
D3DXVECTOR3 CharOBJGetPos(OBJData* Pj, char Type[2], int Num)//���YType��Num�Ԗڂ�pos���m��
{
	int s=0;
	for (int i = 0; i < 100; i++)
	{
		if (strcmp((Pj+Num)->Type, Type))
		{
			if (s == Num)
			{
				break;
			}
				s++;
		}
	}
	return (Pj + s)->Pos;

}
D3DXVECTOR3 CharOBJGetRot(OBJData* Pj, int Num)//���Y����pos���m��
{

	return (Pj + Num)->Rot;
}
D3DXVECTOR3 CharOBJGetRot(OBJData* Pj, char Type[2], int Num)//���YType��Num�Ԗڂ�pos���m��
{

	int s = 0;
	for (int i = 0; i < 100; i++)
	{
		if (strcmp((Pj + Num)->Type, Type))
		{
			if (s == Num)
			{
				break;
			}
			s++;
		}
	}
	return (Pj + s)->Rot;
}
D3DXVECTOR3 CharOBJGetSize(OBJData* Pj, int Num)//���Y����pos���m��
{
	return (Pj + Num)->Size;

}
D3DXVECTOR3 CharOBJGetSize(OBJData* Pj, char Type[2], int Num)//���YType��Num�Ԗڂ�pos���m��
{

	int s = 0;
	for (int i = 0; i < 100; i++)
	{
		if (strcmp((Pj + Num)->Type, Type))
		{
			if (s == Num)
			{
				break;
			}
			s++;
		}
	}
	return (Pj + s)->Size;
}