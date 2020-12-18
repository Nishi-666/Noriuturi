/*///////////
	3Dキユーブ描画(Cube.h)
							2020年10月9日
							山谷 開偉

*///////////
#ifdef CUBE_H_
#define CUBE_H_

#endif //CUBE_H_

#include <d3d9.h>
#include<d3dx9math.h>

void Cube_initialize(void);
void Cube_Update(void);
void Cube_Draw(D3DXMATRIX* pMtxWorld, int RBoxTextureId);
void Cube_DrawALL(D3DXMATRIX* pMtxWorld, int RBoxTextureId);
void Cube_DrawSetSys(D3DXMATRIX* pMtxWorld, int RBoxTextureId, int Num);
void Cube_Finalize(void);