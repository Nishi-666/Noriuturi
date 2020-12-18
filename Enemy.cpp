#include "Enemy.h"
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
#include "Player.h"
#define MOVE_SPD (1.0f)
bool ENePorY = false;//falseがプレイヤー
int ENeMoveF =0;
char ENeLws[30] = {};
bool ENeWASDLoc[4];
int ENeMoveSetRhythm = 0;
int ENeRhythmWASD=0;
bool EneButtonPush = false;
bool ENeMoveStart = false;
int ENeMoveStartMinesOne = 0;
D3DXVECTOR3 PlOldPos = {-1,-1,-1};
D3DXVECTOR2 Ews;
int ENeMs = 0;
void EnemyInitialize(OBJData* Pj)
{
	ENeMoveF = 0;

	ENeMoveSetRhythm = 0;
	 ENeRhythmWASD = 0;
	 ENeMoveStart = false;
	 ENeMoveStartMinesOne = 0;
	 PlOldPos = { -1,-1,-1};
	Ews;
	int ENeMs = 0;
	EneButtonPush = false;
	for (int i = 1; i < 1024; i++)
	{
		if ((Pj + i)->Type == 3)
		{
			Ews.x = (Pj + i)->Pos.x;
			Ews.y = (Pj + i)->Pos.z;
			//(Pj + i)->Pos = D3DXVECTOR3(1, 0, 0);
			(Pj + i)->Rot = D3DXVECTOR3(0, 0, 0);
			(Pj + i)->Size = D3DXVECTOR3(1, 1, 1);
			(Pj + i)->MovePos = D3DXVECTOR3(0, 0, 0);
			(Pj + i)->Existence = true;
			(Pj + i)->Life =1;
			//	(Pj + i)->Life = 5;		//(Pj + i)->Existence = 1;
			(Pj + i)->TextureID = Texture_SetTextureLoadFile("Asset\\Enemy.png");
		}
	}
		
}

//デバッグフォントモジュールの終了処理
void EnemyFinalize(OBJData* Pj)
{
	ENeMoveStartMinesOne = 0;
	for (int i = 1; i < 1024; i++)
	{
		if ((Pj + i)->Type == 3)
		{

			//Pj->Pos = D3DXVECTOR3(0, 0, 0);
			(Pj + i)->MovePos = D3DXVECTOR3(0, 0, 0);
			(Pj + i)->Life = 1;
			(Pj + i)->Existence = 1;
			Texture_Release(&(Pj + i)->TextureID, 1);
		}
	}
}
void EnemyUpdate(OBJData* Pj)
{
	//return;
	if (ENePorY)
	{
		//YuleyControl(Pj);
		//return;
	}
	for (int i = 1; i < 1024; i++)
	{
	
		if ((Pj + i)->Type == 3 && (Pj + i)->Existence == true)
		{
			if (Pj->Pos.x == (Pj + i)->Pos.x&&Pj->Pos.z == (Pj + i)->Pos.z&& ENeMoveStartMinesOne == 3)
			{
				StateChange(3);
				break;
			}
			if (CharOBJGetType((Pj + i), (Pj + i)->Pos.x, (Pj + i)->Pos.z + 1) == 2)
			{
				ENeWASDLoc[0] = true;
			}
			else
			{
				ENeWASDLoc[0] = false;
			}
			if (CharOBJGetType((Pj + i), (Pj + i)->Pos.x - 1, (Pj + i)->Pos.z) == 2)
			{
				ENeWASDLoc[1] = true;
			}
			else
			{
				ENeWASDLoc[1] = false;
			}
			if (CharOBJGetType((Pj + i), (Pj + i)->Pos.x, (Pj + i)->Pos.z - 1) == 2)
			{
				ENeWASDLoc[2] = true;
			}
			else
			{
				ENeWASDLoc[2] = false;
			}
			if (CharOBJGetType((Pj + i), (Pj + i)->Pos.x + 1, (Pj + i)->Pos.z) == 2)
			{
				ENeWASDLoc[3] = true;
			}
			else
			{
				ENeWASDLoc[3] = false;
			}
			if ((Pj + i)->MovePos.x == 0 && (Pj + i)->MovePos.z == 0 && (Pj + i)->Life >= 0 && ENeMoveStart)
			{
				ENeMoveSetRhythm++;
				PlOldPos = RetOldPos();
				D3DXVECTOR2 WSpos;
			//	WSpos.x = (int)(Pj->Pos.x - (Pj + i)->Pos.x);
			//	WSpos.y = (int)(Pj->Pos.z - (Pj + i)->Pos.z);//差を取る
				WSpos.x = (int)(PlOldPos.x - (Pj + i)->Pos.x);
				WSpos.y = (int)(PlOldPos.z - (Pj + i)->Pos.z);//差を取る
				short Rb=0;
				if (WSpos.x == WSpos.y)
				{//どちらも同値であった場合、ランダムで上下左右作る
					Rb =1+ rand() % 2;
				}
				if (!EneButtonPush)
				{
					if (WSpos.y <= -1&& ENeWASDLoc[2] == false )
					{
						(Pj + i)->MovePos.z = -0.01666666666;
						Ews.y = (float)((Pj + i)->Pos.z- 1); 
						Ews.x = (Pj + i)->Pos.x;
					}
					else if (WSpos.y >= 1 && ENeWASDLoc[0] == false )
					{
						(Pj + i)->MovePos.z = 0.01666666666;
						Ews.y = (float)((Pj + i)->Pos.z + 1);
						Ews.x = (Pj + i)->Pos.x;
					}
					else if (WSpos.x <= -1 && ENeWASDLoc[1] == false)
					{
						(Pj + i)->MovePos.x = -0.01666666666;
						Ews.y = (Pj + i)->Pos.z; 
						Ews.x = (float)((Pj + i)->Pos.x - 1);

					}
					else if (WSpos.x >= 1 && ENeWASDLoc[3] == false )
					{
						(Pj + i)->MovePos.x = 0.01666666666;
						Ews.y = (Pj + i)->Pos.z; 
						Ews.x = (float)((Pj + i)->Pos.x + 1);
					}
					EneButtonPush = true;
					if (ENeMs > 10)
					{
						//ENeMs -= 10;
					}
				}
			}
			if (Pj->Pos.x == (Pj + i)->Pos.x&&Pj->Pos.z == (Pj + i)->Pos.z&&ENeMoveStart != 0)
			{
				StateChange(1);
			}
			if (ENeMoveSetRhythm >= ENeMs)
			{
				EneButtonPush = false;
				ENeRhythmWASD++;
				if (ENeRhythmWASD == 4)
				{
					ENeRhythmWASD = 0;
				}
				ENeMoveSetRhythm = 0;
			}


			{
				(Pj + i)->Pos += (Pj + i)->MovePos;
				if (Pj->Pos.x == (Pj + i)->Pos.x&&Pj->Pos.z == (Pj + i)->Pos.z&&ENeMoveStartMinesOne != 0)
				{
					StateChange(1);
				}
				ENeMoveF++; 
				if (ENeMoveF > 60)
				{
					(Pj + i)->Pos.x = Ews.x;
					(Pj + i)->Pos.z = Ews.y;
					
					if (Pj->Pos.x == (Pj + i)->Pos.x&&Pj->Pos.z == (Pj + i)->Pos.z )
					{
						StateChange(1);
					}

					ENeMoveF = 0;
					(Pj + i)->MovePos.x = 0;
					(Pj + i)->MovePos.z = 0;
					Ews.x = (Pj + i)->Pos.x;
					Ews.y = (Pj + i)->Pos.z;
					ENeMoveStart = false;
				}
				ENeLws[0] = '\0';
			}
			//Pj->MovePos *= 0.5f;
		}
	}
}

void EnemyDraw(OBJData* Pj)
{
	for (int i = 1; i < 1024; i++)
	{
		if ((Pj + i)->Existence == true && (Pj + i)->Type == 3)
		{
			Cube_DrawSetSys(&SetTransform((Pj + i)->Pos.x, (Pj + i)->Pos.y, (Pj + i)->Pos.z, (Pj + i)->Rot.x, (Pj + i)->Rot.y, (Pj + i)->Rot.z, (Pj + i)->Size.x, (Pj + i)->Size.y, (Pj + i)->Size.z), (Pj + i)->TextureID, (Pj + i)->Life);
			
		}
	}
}
void MoveStr()
{

	if (ENeMoveStartMinesOne==3)
	{

		MinasNowOLDNum();
		ENeMoveStart = true;
	}else
	{
		ENeMoveStartMinesOne++;
	}
}
