/*
xz平面グリット描画(DebugLattice.h)
	2020年10月13日
	山谷開偉
*/
#include "MyDirect3D.h"
#include <d3d9.h>
#include "CharOBJ.h"
#ifndef CAMERA_H_
#define CAMERA_H_
//size =グリットのサイズ
//Count=一遍のグリット数
//Collar=グリットカラー
void CameraInit(void);
void CameraUpDate(OBJData* Pj, int State);
void CameraSetting(void);
const D3DXVECTOR3& camera_GetFlontVector(void);
const D3DXVECTOR3& camera_GetPos(void);
D3DXVECTOR3 GetEye();
#endif // CAMERA_H_
