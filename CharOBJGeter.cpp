#pragma once
#include "CharOBJ.h"
D3DXVECTOR3 CharOBJGetPos(OBJData* Pj, int Num)//���Y����pos���m��
{
	return (Pj +Num)->Pos;
}
D3DXVECTOR3 CharOBJGetPos(OBJData* Pj, int Type, int Num)//���YType��Num�Ԗڂ�pos���m��
{
	int s=0;
	for (int i = 0; i < 1024; i++)
	{
		if ((Pj + i)->Type == Type)
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
D3DXVECTOR3 CharOBJGetRot(OBJData* Pj, int Type, int Num)//���YType��Num�Ԗڂ�pos���m��
{

	int s = 0;
	for (int i = 0; i < 1024; i++)
	{
		if ((Pj + i)->Type == Type)
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
D3DXVECTOR3 CharOBJGetSize(OBJData* Pj, int Type, int Num)//���YType��Num�Ԗڂ�pos���m��
{

	int s = 0;
	for (int i = 0; i < 1024; i++)
	{
		if ((Pj + i)->Type == Type)
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

int CharOBJGetType(OBJData* Pj, int x, int z)//���YType��Num�Ԗڂ�pos���m��
{

	for (int i = 1; i < 1024; i++)
	{
		if ((int)(Pj+i)->Pos.x == x && (int)(Pj + i)->Pos.z == z)
		{
			return (Pj + i)->Type;
		}
	}
	return -1;

}
