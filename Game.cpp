#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <time.h>
#include"Game.h"
#include"MyDirect3D.h"
#include "Sprite.h"
#include "TexMan.h"
#include "Cube.h"
#include "DebugLattice.h"
#include "keyboard.h"
#include "KeyLoggerr.h"
#include "camera.h"
#include "Triangle.h"
#include "Transform.h"
#include "CharOBJ.h"
#include "Player.h"
#include "NoriUturi.h"
#include "StageSet.h"
static float f=0;
static int frame=0;
int state=1;
int Life = 3;
int Stage = 1;
LPDIRECT3DDEVICE9 g_pDevice;

 OBJData OJ[101];
 OBJData* pOJ=OJ;
 int OJSize=0;
 char Ld[3] = {};
 char Sd[3] = {};
 int GameNexInt=0;

 float g_angle = 0;
 float g_Value = 0;
 float g_Value2 = 0;

 static D3DXVECTOR3 g_vectorDemo;
 static D3DXVECTOR3 g_dir;

 static bool g_vectorBool;
bool Game_initialize(bool N98)
{
	time_t rt;
	srand(time(&rt));
	Life = 3;
	pOJ =OJ;
	 g_pDevice = MyDirect3D_GetDevice();
	if (!g_pDevice)
	{
		return false;
	}
		//テクスチャの読み込み予約//DirectX勉強用\DX-04 テクスチャマネージャ\DX-02 MessageBox\Asset

	CameraInit();
	Cube_initialize(); 
	Triangle_initialize();
	KeyLogger_initialize();
	Keyboard_Initialize();

	SetStage(pOJ, "Stage1Data.csv");
	PlayerInitialize(pOJ);
	
	NoriuturiInitialize(pOJ);
	 LatticeInit(1.0f, 10, D3DCOLOR_RGBA(255, 255, 255, 255));

	 SetLife(pOJ, 5);
	 g_pDevice = MyDirect3D_GetDevice();
	 return true;
}
void Game_Update(void)
{
	CameraUpDate(pOJ);
	KeyLogger_Update();
	
	if (KeyLogger_Press(KL_CANCEL))
	{
		g_vectorDemo = camera_GetPos();
		g_dir = camera_GetFlontVector();
		g_vectorBool = 1;
	}
	g_angle += 0.01f;

	//g_Value =sinf(g_angle)*5.0f;

	//g_Value2 =cosf(g_angle)*5.0f;

	Cube_Update();
	PlayerUpdate(pOJ);
	NoriuturiUpdate(pOJ);
	Triangle_Update();
}
void Game_Draw(void)
{
	int rt = 0, tcx = 0;
	D3DXMATRIX MtxT, MtxR, MtxS;
		CameraSetting();
		
		LatticeDraw(); 

		NoriuturiDraw(pOJ);
		PlayerDraw(pOJ);
		LatticeDraw();

		D3DXMatrixTranslation(&MtxT, g_Value+3, 0.5f, g_Value2);
		//D3DXMatrixScaling(&MtxS, 10, 10, 10);
	//	D3DXMatrixRotationY(&MtxR, g_angle);
	//	MtxT = MtxT * MtxR;//* MtxT;
	//	Triangle_Draw(&MtxT);
	/*	D3DXMatrixTranslation(&MtxT, g_Value, 1.5f, g_Value2);
		D3DXMatrixScaling(&MtxS, 2, 1, 2);
		D3DXMatrixRotationY(&MtxR, g_angle);
		MtxT = MtxS * MtxR* MtxT;
		Cube_Draw(&MtxT);
		D3DXMatrixTranslation(&MtxT, g_Value, 2.5f, g_Value2);
		D3DXMatrixScaling(&MtxS, 1, 1, 1);
		D3DXMatrixRotationY(&MtxR, g_angle);
		MtxT = MtxS * MtxR* MtxT;
		Cube_Draw(&MtxT);*/



}
void Game_Finalize(void)
{
	KeyLogger_Finalize(); 
	PlayerFinalize(pOJ);
	NoriuturiFinalize(pOJ);
	 Cube_Finalize();
	LatticeFnalize();
}

void StateChange(int CData)
{//外部からステートの変更を行うため
	state = CData;
	if (CData == 2)
	{
		//StopSound(SOUND_LABEL_BGM000);
	}
}

int GetStage()
{//外部からステートの変更を行うため
	return Stage;
}

void LifeMinus()
{
	Life--;
	if (Life <= 0)
	{
	}
}
void StageAdd()
{
	GameNexInt = 60*10;
	Stage++;
	StageNex();
}
void StageNex(void)
{//

}