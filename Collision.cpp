#include "Collision.h"

bool Collision_CircleAndCircleHie(const CircleCollision* pA, const CircleCollision* pB )
{
	D3DXVECTOR2 Vec = pA->ceneter - pB->ceneter;
	return D3DXVec2LengthSq(&Vec) < (pA->radus + pB->radus)*(pA->radus + pB->radus);
}