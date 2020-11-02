/*============================================================

ÉQÅ[ÉÄÇÃè’ìÀïî[Game_Barret.h]                            Author:Kai Yamaya
												   Date:2020/7/17
-------------------------------------------------------

==============================================================
*/
#pragma once
#ifndef GAME_COLLISION_H
#define GAME_COLLISION_H

#include <d3dx9.h>
typedef struct CircleCollision_tag
{
	//D3DVECTOR2 
	D3DXVECTOR2 ceneter;
	float  radus;
} CircleCollision;

bool Collision_CircleAndCircleHie(const CircleCollision* pA, const CircleCollision* pB);
#endif // GAME_COLLISION_H
