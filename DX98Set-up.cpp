
#include "Debug_Font.h"
#include "TexMan.h"
#include <string.h>
#include "Sprite.h"
#include "DX98Set-up.h"
#include <stdio.h>
#define RagTImes (120)
//描画についてはDebugFontを呼び出す扱いで

int ConventionalMemory = 640, ADDMemory = 800, M1 = 0, M2 = 0;//M1M2は描画用
int Rag = 0;//m1,m2が予定値になった後のラグタイム
bool CPUMODE=true;//CPUモードハイロー(high:true, low:false);
bool BeepSE = false;
bool END=false;
void DX98Initialize(void)
{
	M1 = 0;
	M2 = 0;
	BeepSE = false;
}
void DX98Finalize(void)
{
	M1 = 0;
	M2 = 0;
	BeepSE = false;
}
void DX98Update(void)
{
	if (!BeepSE)
	{
		Beep(2000, 300);
		Beep(1000, 150);
		//StartUpの後のメモリーチェック再現用
		Sleep(1000);
		BeepSE = true;
	}
	if (ConventionalMemory > M1)
	{
		int R = rand() % 20;
		M1+= R;
		if (M1 > ConventionalMemory)
		{
			M1 = ConventionalMemory;
		}
	}
	if (ADDMemory > M2)
	{
		int R = rand() % 20;
		M2+= R;
		if (M2 > ADDMemory)
		{
			M2 = ADDMemory;
		}
	}
	if (M2 == ADDMemory &&M1 == ConventionalMemory )
	{
		Rag++;	
		if (Rag > RagTImes)
		{
			Rag = RagTImes;
			END = true;
		}
	}
//	Sleep(20);
}
void DX98Roop(void)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice)
	{
		MessageBox(NULL, "アプリケーション終了します", "テクスチャの読み込みが失敗しましたのでDA", MB_OK);//OKを押されるまでプログラムがとまる
		return;
	}
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);
	pDevice->BeginScene();
//	bool END = false;
	while (true)
		{
		DX98Draw();
		DX98Update();
		if (ConventionalMemory == M1 && ADDMemory == M2)
		{
			break;
		}
	}
//	Sleep(3000);

	pDevice->EndScene();
	pDevice->Present(NULL, NULL, NULL, NULL);
	DX98Finalize();
}

int DX98Draw(void)
{
	if (CPUMODE)
	{
		DebugFont_Draw(0, 0, "CPU MODE  High", 1, 0.5f);
	}else
	{
		DebugFont_Draw(0, 0, "CPU MODE  Low", 1, 0.5f);
	}
	char ws[10] = {};
	char ws2[10] = {};
	char ws3[30] = {};
	strcat(ws3,"MEMORY ");
	snprintf(ws, sizeof(int), "%d", M1);
	strcat(ws3, strcat(ws, "KB + "));
	snprintf(ws2, sizeof(int), "%d", M2);
	strcat(ws3, strcat(ws2, "KB OK "));
	DebugFont_Draw(0, 60, ws3, 1, 0.5f);
	

	return END;
}