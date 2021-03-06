#pragma once
#include "CharOBJ.h"
D3DXVECTOR3 CharOBJGetPos(OBJData* Pj, int Num)//当該数のposを確保
{
	return (Pj +Num)->Pos;
}
D3DXVECTOR3 CharOBJGetPos(OBJData* Pj, int Type, int Num)//当該TypeのNum番目のposを確保
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
D3DXVECTOR3 CharOBJGetRot(OBJData* Pj, int Num)//当該数のposを確保
{

	return (Pj + Num)->Rot;
}
D3DXVECTOR3 CharOBJGetRot(OBJData* Pj, int Type, int Num)//当該TypeのNum番目のposを確保
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
D3DXVECTOR3 CharOBJGetSize(OBJData* Pj, int Num)//当該数のposを確保
{
	return (Pj + Num)->Size;

}
D3DXVECTOR3 CharOBJGetSize(OBJData* Pj, int Type, int Num)//当該TypeのNum番目のposを確保
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

int CharOBJGetType(OBJData* Pj, int x, int z)//当該TypeのNum番目のposを確保
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
