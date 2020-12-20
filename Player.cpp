#include "Player.h"
#include "Cube.h"
#include "KeyLoggerr.h"
#include "YULEY.h"
#include "Transform.h"
#include <stdlib.h>
#include "GoalStar.h"
#include "Font.h"
#include <string.h>
#include "CharOBJGeter.h"
#include "Debug_Font.h"
#include "Enemy.h"
#include "Ice.h"
#include <time.h>
#define MOVE_SPD (1.0f)
bool PorY = false;//falseがプレイヤー
int MoveF =0;
char Lws[30] = {};
bool WASDLoc[4];

float Tims;

int MoveSetRhythm = 0;
int RhythmWASD=0;
bool ButtonPush = false;
int WTextureID = TEXTURE_INVALID_ID;
int ATextureID = TEXTURE_INVALID_ID;
int STextureID = TEXTURE_INVALID_ID;
int DTextureID = TEXTURE_INVALID_ID;
int WASDTextureID = TEXTURE_INVALID_ID;
D3DXVECTOR3 OldPos = {-1,-1,-1};
D3DXVECTOR2 ws;
int MoveNum = 0;//いくつ移動したか
int Move4;
int Ms = 0;
D3DXVECTOR3 NowOLDPos[4] = {};//ここに現在+3個前の位置を書く
int NowOLDNum = 3;
void PlayerInitialize(OBJData* Pj)
{
	 NowOLDNum = 3;
	 for (int i = 0; i < 4;i++)
	 {
		 NowOLDPos[i] = Pj->Pos;
	 }

	MoveNum = 0;
	Tims = 120;//とりあえず2分を仮定
	Move4 = 0;
	MoveF = 0;
	Ms = 60;
	OldPos = { -0,-0,0};
	//	Pj->Pos = D3DXVECTOR3(0, 0, 0);
		Pj->Rot = D3DXVECTOR3(0, 0, 0);
		Pj->Size = D3DXVECTOR3(1, 1, 1);
		Pj->MovePos = D3DXVECTOR3(0, 0, 0);
		Pj->Life =5;
		Pj->Existence = 1;
		WASDTextureID = Texture_SetTextureLoadFile("Asset\\W.png");
		WTextureID = Texture_SetTextureLoadFile("Asset\\W.png");
		ATextureID = Texture_SetTextureLoadFile("Asset\\A.png");
		STextureID = Texture_SetTextureLoadFile("Asset\\S.png");
		DTextureID = Texture_SetTextureLoadFile("Asset\\D.png");
		Pj->TextureID = Texture_SetTextureLoadFile("Asset\\Player.png");
		//FontSet(L"残り移動可能回数", 0);
	///	wchar_t wc[2] = {};
		//_itow_s(Pj->Life, wc, 10);
		//FontSet(wc, 1);
	
}

//デバッグフォントモジュールの終了処理
void PlayerFinalize(OBJData* Pj)
{
	//Pj->Pos = D3DXVECTOR3(0, 0, 0);
	Pj->MovePos = D3DXVECTOR3(0, 0, 0);
	Pj->Life = 1;
	Pj->Existence = 1;
	Texture_Release(&Pj->TextureID, 1);
	Texture_Release(&WTextureID, 1);
	Texture_Release(&ATextureID, 1);
	Texture_Release(&STextureID, 1);
	Texture_Release(&DTextureID, 1);
}
void PlayerUpdate(OBJData* Pj)
{
	if (CharOBJGetType(Pj, Pj->Pos.x, Pj->Pos.z + 1) == 2)
	{
		WASDLoc[0] = true;
	}
	else
	{
		WASDLoc[0] = false;
	}
	if (CharOBJGetType(Pj, Pj->Pos.x - 1, Pj->Pos.z) == 2)
	{
		WASDLoc[1] = true;
	}
	else
	{
		WASDLoc[1] = false;
	}
	if (CharOBJGetType(Pj, Pj->Pos.x, Pj->Pos.z - 1) == 2)
	{
		WASDLoc[2] = true;
	}
	else
	{
		WASDLoc[2] = false;
	}
	if (CharOBJGetType(Pj, Pj->Pos.x + 1, Pj->Pos.z) == 2)
	{
		WASDLoc[3] = true;
	}
	else
	{
		WASDLoc[3] = false;
	}

	Tims -= 0.0166666667f;//所謂1秒60Fでの1フレーム秒
	if (Tims <= 0)
	{
		StateChange(2);
	}

	if (PorY)
	{
		//YuleyControl(Pj);
		//return;
	}
	if (Pj->MovePos.x == 0 && Pj->MovePos.z == 0&& Pj->Life>=0)
	{
		MoveSetRhythm++;
		
		if (KeyLogger_Press(KL_ATTACK) && !ButtonPush)
		{
			MoveNum++;
			OldPos.x = Pj->Pos.x;
			OldPos.y = Pj->Pos.z;
			D3DXVECTOR3 D3DV3WS = NowOLDPos[1];
			for (int i = 3; i > 0; i--)
			{
				NowOLDPos[i] = NowOLDPos[i - 1];//-1
			}
			NowOLDPos[0] = Pj->Pos;
			if (NowOLDNum > -1 && NowOLDNum < 4)
			{
				NowOLDNum++;
			}
			if (RhythmWASD == 2 && WASDLoc[2] == false)
			{

				Pj->MovePos.z = -0.01666666666;
				ws.y = Pj->Pos.z - 1; ws.x = Pj->Pos.x;

				//OldPos = {0,-1};
			}
			else if (RhythmWASD == 0 && WASDLoc[0] == false)
			{
				Pj->MovePos.z = 0.01666666666;
				ws.y = Pj->Pos.z + 1; ws.x = Pj->Pos.x;
				//OldPos = {0, + 1 };
			}
			else if (RhythmWASD == 3 && WASDLoc[1] == false)
			{
				Pj->MovePos.x = -0.01666666666;
				ws.y = Pj->Pos.z; ws.x = Pj->Pos.x - 1;
				//OldPos = { -1,0 };

			}
			else if (RhythmWASD == 1 && WASDLoc[3] == false)
			{
				Pj->MovePos.x = 0.01666666666;
				ws.y = Pj->Pos.z; ws.x = Pj->Pos.x + 1;
				//OldPos = {+1 ,0};
			}
			ButtonPush = true;
			//if (Ms > 10)
			{
			//	Ms -= 10;
			}
		}
		if (MoveSetRhythm >= Ms)
		{
			ButtonPush = false;
			RhythmWASD++;
			Move4++;
			
			if (RhythmWASD == 4)
			{
				RhythmWASD = 0;
			}
			if (RhythmWASD==0 && MoveNum >= 3)
			{
				//Beep(1000, 1000);
				MoveStr();
				Move4 = 0;
			}
			MoveSetRhythm = 0;
		}
	}
	else if (Pj->Life < 0)
	{
		StateChange(3);
	}
	else
	{
		Pj->Pos += Pj->MovePos;
		MoveF++;
		if (MoveF > 60)
		{
			Move4 = 0;
			//Pj->Life = Pj->Life - 1;
			Pj->Pos.x = ws.x;
			Pj->Pos.z = ws.y;
			int r = GoalStarJudgment(Pj->Pos);
			//ここにスターやゴールの設定を記述
			if (r == 0)//ゴール
			{
				//Beep(1000, 1000);

				//ここを書き換え
				int c =IECJudgement();
				if (c == 1)
				{
					//Point += 300;//とりあえず仮で300投入
				}
			//	StateChange(2);
				return;
			}
			if (r == 1)//星(難しい
			{

				//Beep(100, 100);
				//return;

			}
			if (r == 2)//星(ふつう
			{

				//Beep(100, 100);
				//return;

			}if (r == 3)//星(簡単
			{


				//Beep(100, 100);
				//return;
			}

			ICECollision(Pj);
			ICESetICE(Pj);
		

			if (CharOBJGetType(Pj, Pj->Pos.x, Pj->Pos.z + 1) == 2)
			{
				WASDLoc[0] = true;
			}
			else
			{
				WASDLoc[0] = false;
			}
			if (CharOBJGetType(Pj, Pj->Pos.x - 1, Pj->Pos.z) == 2)
			{
				WASDLoc[1] = true;
			}
			else
			{
				WASDLoc[1] = false;
			}
			if (CharOBJGetType(Pj, Pj->Pos.x, Pj->Pos.z - 1) == 2)
			{
				WASDLoc[2] = true;
			}
			else
			{
				WASDLoc[2] = false;
			}
			if (CharOBJGetType(Pj, Pj->Pos.x + 1, Pj->Pos.z) == 2)
			{
				WASDLoc[3] = true;
			}
			else
			{
				WASDLoc[3] = false;
			}
			MoveF = 0;
			Pj->MovePos.x = 0;
			Pj->MovePos.z = 0;
			for (int i = 1; i < 1024; i++)
			{
				if (Pj->Pos.x == (Pj + i)->Pos.x&&Pj->Pos.z == (Pj + i)->Pos.z && (Pj + i)->Existence)
				{
					if ((Pj + i)->Type == 1)
					{
						Pj->Life = (Pj + i)->Life;
						(Pj + i)->Existence = false;
						//Beep(1000, 100);
					}
					if ((Pj + i)->Type == 5)
					{//上
						SetAutomatic(Pj, { 0,0,1 });
					}
					if ((Pj + i)->Type == 6)
					{//下
						SetAutomatic(Pj, { 0,0,-1 });
					}
					if ((Pj + i)->Type == 7)
					{//右
						SetAutomatic(Pj, { 1,0,0 });
					}
					if ((Pj + i)->Type == 8)
					{//左

						SetAutomatic(Pj, { -1,0,0 });
					}
				}
			}
		}
		Lws[0] = '\0';
		if (Pj->Life >= 0)
		{
			wchar_t wc[2] = {};
			_itow_s(Pj->Life, wc, 10);
			///FontSet(wc, 1);
		}
	}
	//Pj->MovePos *= 0.5f;
}

void PlayerDraw(OBJData* Pj)
{
	if (Pj->Existence==true)
	{
		if (!RhythmWASD)
		{
			Cube_Draw(&SetTransform(Pj->Pos.x, Pj->Pos.y, Pj->Pos.z+1,0,0,0, Pj->Size.x, 0.1f, Pj->Size.y), WTextureID);

		}
		else if (RhythmWASD==1&&Pj->TextureID != DTextureID)
		{
			Cube_Draw(&SetTransform(Pj->Pos.x+1, Pj->Pos.y , Pj->Pos.z,0,0 ,0, Pj->Size.x, 0.1f, Pj->Size.y), DTextureID);
		}
		else if (RhythmWASD==2&&Pj->TextureID != STextureID)
		{
			Cube_Draw(&SetTransform(Pj->Pos.x, Pj->Pos.y, Pj->Pos.z - 1, 0, 0, 0, Pj->Size.x, 0.1f, Pj->Size.y), STextureID);
		}
		if (RhythmWASD==3 &&Pj->TextureID != ATextureID)
		{
			Cube_Draw(&SetTransform(Pj->Pos.x-1, Pj->Pos.y , Pj->Pos.z, 0, 0, 0, Pj->Size.x, 0.1f, Pj->Size.y), ATextureID);
		}


		Cube_Draw(&SetTransform(Pj->Pos.x, Pj->Pos.y, Pj->Pos.z, Pj->Rot.x, Pj->Rot.y, Pj->Rot.z, Pj->Size.x, Pj->Size.y, Pj->Size.z), Pj->TextureID);

		//FontDRAW(Pj->Pos.x + SCREEN_WHIDTH + 800, Pj->Pos.z + SCREEN_HEIGHT * 1.9, 0, 0.15f, 0);
		///FontDRAW(Pj->Pos.x + SCREEN_WHIDTH - 1600, Pj->Pos.z + SCREEN_HEIGHT * 2.64, 0, 0.1f, 1);
		//DebugFont_Draw(200.0f, 200.0f, Lws, 1);
	}
}
void PorYChange(void)
{
	PorY = !PorY;
}
bool GetYChange(void)
{
	return PorY;
}
void SetLife(OBJData* Pj,int Life)
{
	Pj->Life = Life;
}
D3DXVECTOR3 RetOldPos(void)
{
	return NowOLDPos[NowOLDNum];
}
void MinasNowOLDNum(void)
{
	NowOLDNum--;
}

void SetAutomatic(OBJData* Pj,D3DXVECTOR3 MovePos)
{
	
	MoveF = 0;
	Pj->MovePos.x = 0;
	Pj->MovePos.z = 0;
			MoveNum++;
			OldPos.x = Pj->Pos.x;
			OldPos.y = Pj->Pos.z;
			D3DXVECTOR3 D3DV3WS = NowOLDPos[1];
			for (int i = 3; i > 0; i--)
			{
				NowOLDPos[i] = NowOLDPos[i - 1];//-1
			}
			NowOLDPos[0] = Pj->Pos;
			if (NowOLDNum > -1 && NowOLDNum < 4)
			{
				NowOLDNum++;
			}

			Pj->MovePos.z = 0.01666666666f*MovePos.z;
			Pj->MovePos.x = 0.01666666666f*MovePos.x;
			
				ws.y = Pj->Pos.z +MovePos.z; ws.x = Pj->Pos.x + MovePos.x;
			ButtonPush = true;


}