/*
xz���ʃO���b�g�`��(DebugLattice.h)
	2020�N10��13��
	�R�J�J��
*/
#include "MyDirect3D.h"
#include <d3d9.h>
#include "CharOBJ.h"
#ifndef CAMERA_H_
#define CAMERA_H_
//size =�O���b�g�̃T�C�Y
//Count=��Ղ̃O���b�g��
//Collar=�O���b�g�J���[
void CameraInit(void);
void CameraUpDate(OBJData* Pj, int State);
void CameraSetting(void);
const D3DXVECTOR3& camera_GetFlontVector(void);
const D3DXVECTOR3& camera_GetPos(void);
D3DXVECTOR3 GetEye();
#endif // CAMERA_H_
