/*
xz���ʃO���b�g�`��(DebugLattice.h)
	2020�N10��13��
	�R�J�J��
*/
#include <d3d9.h>
#ifndef LATTICE_H_
#define LATTICE_H_
//size =�O���b�g�̃T�C�Y
//Count=��Ղ̃O���b�g��
//Collar=�O���b�g�J���[
void LatticeInit(float size, float count, D3DCOLOR Collar);
void LatticeFnalize(void);
void LatticeDraw(void);

#endif // LATTICE_H_
