/*///////////
	3D�L���[�u�`��(Cube.h)
							2020�N10��9��
							�R�J �J��

*///////////
#ifdef CUBE_H_
#define CUBE_H_

#endif //CUBE_H_

#include <d3d9.h>
#include<d3dx9math.h>

void Cube_initialize(void);
void Cube_Update(void);
void Cube_Draw(D3DXMATRIX* pMtxWorld);
void Cube_Finalize(void);