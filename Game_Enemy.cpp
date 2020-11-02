/*============================================================

�Q�[���̓G����[Game_Enemy.cpp]                           Author:Kai Yamaya
												   Date:2020/7/21
-------------------------------------------------------

==============================================================*/
#include "Game_Enemy.h"
#include "TexMan.h"
#include <string.h>
#include "Sprite.h"
#include "GameEnemy_Barret.h"
#include "Game_GND.h"
#include "DebugPrimitiv.h"

#define ENEEMY_WHIDTH (94)//�X�N���[����
#define ENEMY_HEIGHT (34)//�X�N���[������
#define ENEMY MAX(2048)
//#include "Collision.h"
//�Q�[���v���C���[�̏�����
typedef struct
{
	D3DXVECTOR2 Position;
	D3DXVECTOR2 MovePos;
	int type;
	bool Enable; 
	CircleCollision C;
}EneData;
EneData ED[30];

static int g_EnemyTextureID = TEXTURE_INVALID_ID;
//static D3DXVECTOR2 g_EnemyPosition = D3DXVECTOR2(0.0f, 0.0f);
//static bool g_EnemyEnable = false;

void GameEnemy_initialize(void)
{

	if (g_EnemyTextureID == TEXTURE_INVALID_ID)
	{
		g_EnemyTextureID = Texture_SetTextureLoadFile("Asset\\Enemy.png");
	}
	if (Texture_Load() > 0)
	{
		MessageBox(NULL, "�A�v���P�[�V�����I�����܂�", "A�e�N�X�`���̓ǂݍ��݂����s���܂����̂�DA", MB_OK);//OK���������܂Ńv���O�������Ƃ܂�
		return;
	}
	else
	{
		//MessageBox(NULL, "OK", "�e�N�X�`���ǂݍ���", MB_OK);//OK���������܂Ńv���O�������Ƃ܂�
	}
	for (int i = 0; i < 30; i++)
	{
		ED[i].Position = D3DXVECTOR2(0.0f, 0.0f);
		ED[i].MovePos = D3DXVECTOR2(0.0f, 0.0f);
		ED[i].Enable = false;
		ED[i].type = 0;
	}
}
void GameEnemy_Reset(void)
{
	for (int i = 0; i < 30; i++)
	{
		ED[i].Position = D3DXVECTOR2(0.0f, 0.0f);
		ED[i].MovePos = D3DXVECTOR2(0.0f, 0.0f);
		ED[i].Enable = false;
		ED[i].type = 0;
	}
}

//�I��
void GameEnemy_Finalize(void)
{

	Texture_Release(&g_EnemyTextureID, 1);

	for (int i = 0; i < 30; i++)
	{
		ED[i].Position = D3DXVECTOR2(0.0f, 0.0f);
		ED[i].MovePos = D3DXVECTOR2(-10.0f, 0.0f);
		ED[i].Enable = false;
		ED[i].type = 0;
	}
	
}
void GameEnemy_Despawn(int i)
{
	ED[i].Enable = false;
}

//�X�V
void GameEnemy_Update(void)
{

	for (int i = 0; i < 30; i++)
	{
		//�e���L�������ׂ�
		if (ED[i].Enable)
		{
			ED[i].Position.x += ED[i].MovePos.x;
			ED[i].Position.y += ED[i].MovePos.y;
			int USDData = GameGND_GetSPR(ED[i].Position.x);
			int SPRData = GameGND_GetHeightPos(ED[i].Position.x);
			(ED+i)->C= { {ED[i].Position.x /*+ ENEEMY_WHIDTH*0.5f*/,ED[i].Position.y + ENEMY_HEIGHT * 0.5f},ENEEMY_WHIDTH*0.5f };
			(ED + i)->C.radus = ENEEMY_WHIDTH * 0.5f;
			/*��
			�G�l�~�[�̊m����W�̃|�C���^�ƁA			��������̍������R���W�����Ɏ�������̂�����ł�			�e�N�X�`���̂悤�ɁA�|�C���^�ƃJ�E���^�ŊǗ��ł���Ɗy����

			�R���W������n������DebugPrimitive�����Ă����֐������Ƃ悢����
			�I�u���[�g�ł����Ȃ��̂ŁADebugPrimitive�̒��ɍ���Ă��ǂ��̂ł͂Ǝv���Ă܂��� >> �R���W������DebugPrimitive			�R���W�����̌v�Z�̓R���W�����ł�点����			�f�[�^�Ɣ{���ŊǗ�����Ɗy����

			*/


			if (!USDData)// || ED[i].Position.y < SPRData);
			{
				continue;
			}
			//0:�܂ȔARJ,�瑁 -1:���~ +1:�㏸
			if (ED[i].Position.y > SPRData) {
				if (USDData == 1)
				{
					ED[i].Position.y += ED[i].MovePos.x;
				}
				else if (USDData == -1)
				{
					//	ED[i].Position.y-= ED[i].MovePos.x;
				}
			}
			//�e���W�X�V
			if ((ED[i].Position.x > SCREEN_WHIDTH+200 && ED->MovePos.x>0) || (ED[i].Position.x < -100 && ED->MovePos.x < 0))
			{
				ED[i].Enable = false;
			}
			int r = rand() % 10;
			if (!r)
			{
				if (ED[i].type == 0)
				{
					GameEnemyBarret_Create((float)ED[i].Position.x + 20, (float)ED[i].Position.y + 17,-11,0);
				}
				else if (ED[i].type == 1)
				{
					GameEnemyBarret_Create((float)ED[i].Position.x + 20, (float)ED[i].Position.y + 17,0,+11);
				}
			}
		}
	}
	//�����̏����Œe�𖳌��ɂ���
}

//�`��
void GameEnemy_Draw(void)
{
	for (int i = 0; i < 30; i++)
	{

		if (ED[i].Enable)
		{
			//�e��`�悷��

			int EnemyTypeX = 0;
			int EnemyTypeY = 0;

			//SpriteDraw(Work_texture, PosX, PosY, tcx, tcy, DEBUG_FONT_WIDTH, DEBUG_FONT_HEIGHT);
			//SpriteDraw(g_textureID, 400, 320.0f, 32.0f, 32.0f, tcx, 0, 32, 32, 16, 16, f);
			SpriteDraw(g_EnemyTextureID, ED[i].Position.x, ED[i].Position.y, EnemyTypeX * 94, ED[i].type * 34, 94, 34);;// DrawPosX + (DEBUG_FONT_WIDTH / 2), DrawPosY + (DEBUG_FONT_HEIGHT / 2), Rot);
			DebugPrimitiv_BatchDrawCircle(ED[i].Position.x*ENEEMY_WHIDTH*0.5f,
				ED[i].Position.y*ENEMY_HEIGHT*0.5f, ENEMY_HEIGHT*0.5f);
		}
	}

}
//�G�o��
void GameEnemy_Spawn(float x, float y)
{

	
	for (int i = 0; i < 30; i++)
	{
		if (!ED[i].Enable)
		{//�e��ǉ�
			ED[i].Position.x = x;
			ED[i].MovePos.x = -10;
			ED[i].Position.y = y;
			ED[i].Enable = true;
			ED[i].type = rand()%2;
			break;
		}
	}
}
bool GameEnemy_IsEnable(int i)
{
	return ED[i].Enable;
}
D3DXVECTOR2 GetEneemy_thisPos(int i)
{
	return ED[i].Position;
}

CircleCollision GameEnemy_GetCollision(int i)
{

	//	CircleCollision C = { {ED[i].Position.x /*+ ENEEMY_WHIDTH*0.5f*/,ED[i].Position.y + ENEMY_HEIGHT * 0.5f},ENEEMY_WHIDTH*0.5f };
		//	C.ceneter = g_EnemyPosition;
		//	C.radus = 34;
		return (ED + i)->C;
	
}