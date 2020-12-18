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
#include "GoalStar.h"
#include "Wall.h"
#include "StartClearOverScreen.h"
#include "Enemy.h"
#include "GoalStar.h"
#include "Ice.h"
#include"MoveGimmick.h"
static float f=0;
static int frame=0;
int Life = 3;
int Stage = 1;
LPDIRECT3DDEVICE9 g_pDevice;

 OBJData OJ[1025];
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

 int State = 0;
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
	SetTex();
	SetStage(pOJ, "Asset\\Stage_01.csv",12,12);
	LatticeInit(1.0f, 11, D3DCOLOR_RGBA(255, 255, 255, 255));
	ICEInitialize(pOJ);
			//NoriuturiInitialize(pOJ);

	MoveGimmickInitialize(pOJ);
	SCOInit(pOJ);
	 WallInitialize(pOJ);
	 PlayerInitialize(pOJ);
	 EnemyInitialize(pOJ);
	 SetLife(pOJ, 5);
	 g_pDevice = MyDirect3D_GetDevice();
	 return true;
}
void Game_Update(void)
{
	CameraUpDate(pOJ, State);
	KeyLogger_Update();
	if (State == 1)
	{

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
		EnemyUpdate(pOJ);
		PlayerUpdate(pOJ);
		WallUpdate(pOJ);
		//NoriuturiUpdate(pOJ);
		ICEUpdate(pOJ);
		MoveGimmickUpdate(pOJ);
		Triangle_Update();
	}
	else
	{
		SCOUpDate(State);
	}
}
void Game_Draw(void)
{
		int rt = 0, tcx = 0;
		D3DXMATRIX MtxT, MtxR, MtxS;
		CameraSetting();
		
		if (State == 1)
		{

			LatticeDraw();
			GoalStarDraw();
			ICEDraw(pOJ);
			//NoriuturiDraw(pOJ);
			WallDraw(pOJ);
			EnemyDraw(pOJ);
			PlayerDraw(pOJ);
			MoveGimmickDraw(pOJ);
			D3DXMatrixTranslation(&MtxT, g_Value + 3, 0.5f, g_Value2);
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
		else
		{
			SCODraw(State,pOJ);
		}


}
void Game_Finalize(void)
{
	KeyLogger_Finalize(); 
	PlayerFinalize(pOJ);
	EnemyFinalize(pOJ);
	ICEFinalize(pOJ);
	//NoriuturiFinalize(pOJ);
	WallFinalize(pOJ);
	MoveGimmickFinalize(pOJ);
	 Cube_Finalize();
	LatticeFnalize();
	SCOUnInit();
}

int GetStage()
{//外部からステートの変更を行うため
	return Stage;
}

void StateChange(int st)
{
	State = st;
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
void Game_Reset(void)
{

	SetStage(pOJ, "Asset\\Stage_01.csv", 12, 12);
	NoriuturiInitialize(pOJ);

	WallInitialize(pOJ);
	PlayerInitialize(pOJ);
	EnemyInitialize(pOJ);
	SetLife(pOJ,5);
}