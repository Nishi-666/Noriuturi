/*
xz平面グリット描画(DebugLattice.h)
	2020年10月13日
	山谷開偉
*/
#include <d3d9.h>
#ifndef LATTICE_H_
#define LATTICE_H_
//size =グリットのサイズ
//Count=一遍のグリット数
//Collar=グリットカラー
void LatticeInit(float size, float count, D3DCOLOR Collar);
void LatticeFnalize(void);
void LatticeDraw(void);

#endif // LATTICE_H_
