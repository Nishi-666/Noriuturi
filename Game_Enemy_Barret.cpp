#include "Game_Player.h"
#include "TexMan.h"
#include "Sprite.h"
#include "Collision.h"
#include "sound.h"
static int g_EnemyBarretTextureID = TEXTURE_INVALID_ID;

typedef struct
{
	D3DXVECTOR2 Position;
	D3DXVECTOR2 MovePos;
	bool Enable;
}EneBarret;
EneBarret EB[60];
//static D3DXVECTOR2 g_EnemyBarretPosition = D3DXVECTOR2(0.0f, 0.0f);
//static bool g_EnemyBarretEnable = false;

#define ENEMYBarret_WHIDTH (42)//�e��
#define ENEMYBarret_HEIGHT (11)//�e����

//�e�̏�����
void GameEnemyBarret_initialize(void)
{
	if (g_EnemyBarretTextureID == TEXTURE_INVALID_ID)
	{
		g_EnemyBarretTextureID = Texture_SetTextureLoadFile("Asset\\stg0722.png");

		if (Texture_Load() > 0)
		{
			MessageBox(NULL, "�A�v���P�[�V�����I�����܂�", "A�e�N�X�`���̓ǂݍ��݂����s���܂����̂�DA", MB_OK);//OK���������܂Ńv���O�������Ƃ܂�
			return;
		}
	}

	for (int i = 0; i < 30; i++)
	{
		EB[i].Position = D3DXVECTOR2(0.0f, 0.0f);
		EB[i].MovePos = D3DXVECTOR2(0.0f, 0.0f);
		EB[i].Enable = false;
	}
}
void GameEnemyBarret_Reset(void)
{
	for (int i = 0; i < 30; i++)
	{
		EB[i].Position = D3DXVECTOR2(0.0f, 0.0f);
		EB[i].MovePos = D3DXVECTOR2(0.0f, 0.0f);
		EB[i].Enable = false;
	}
}

//�e�̏I��
void GameEnemyBarret_Finalize(void)
{
	Texture_Release(&g_EnemyBarretTextureID, 1);
	for (int i = 0; i < 30; i++)
	{
		EB[i].Position = D3DXVECTOR2(0.0f, 0.0f);
		EB[i].MovePos = D3DXVECTOR2(0.0f, 0.0f);
		EB[i].Enable = false;
	}

}

//�e�̍X�V
void GameEnemyBarret_Update(void)
{
	for (int i = 0; i < 30; i++)
	{
		//�e���L�������ׂ�
		if (EB[i].Enable)
		{
			EB[i].Position.x += EB[i].MovePos.x;
			EB[i].Position.y += EB[i].MovePos.y;
			//�e���W�X�V
			if (EB[i].Position.x > SCREEN_WHIDTH || EB[i].Position.x < -100)
			{
				EB[i].Enable = false;
			}
		}
	}
	//�����̏����Œe�𖳌��ɂ���
}

//�e�̕`��
void GameEnemyBarret_Draw(void)
{


	for (int i = 0; i < 30; i++)
	{
		//�e���L�������ׂ�
		if (EB[i].Enable)
		{//�e��`�悷��

			int EnemyBarretTypeX = 0;
			int EnemyBarretTypeY = 0;

			//SpriteDraw(Work_texture, PosX, PosY, tcx, tcy, DEBUG_FONT_WIDTH, DEBUG_FONT_HEIGHT);
			//SpriteDraw(g_textureID, 400, 320.0f, 32.0f, 32.0f, tcx, 0, 32, 32, 16, 16, f);
			SpriteDraw(g_EnemyBarretTextureID, EB[i].Position.x, EB[i].Position.y, EnemyBarretTypeX * 42, EnemyBarretTypeX * 11, 42, 11);;// DrawPosX + (DEBUG_FONT_WIDTH / 2), DrawPosY + (DEBUG_FONT_HEIGHT / 2), Rot);

		}
	}
}

//�e�̐���
void GameEnemyBarret_Create(float x, float y, float mx, float my)
{
	for (int i = 0; i < 30; i++)
	{
		if (!EB[i].Enable)
		{//�e��ǉ�
			EB[i].Position.x = x;
			EB[i].Position.y = y;
			EB[i].MovePos.x = mx;
			EB[i].MovePos.y = my;
			EB[i].Enable = true;
			PlaySound(SOUND_LABEL_SE_SHOT);
			break;
		}
	}
}
CircleCollision GameEnemyBarret_GetCollision(int i)
{
	CircleCollision C = { {EB[i].Position.x + ENEMYBarret_WHIDTH * 0.5f,EB[i].Position.y + ENEMYBarret_HEIGHT * 0.5f},
		ENEMYBarret_WHIDTH*0.5f };
	return C;
}

void GameEnemyBarret_Despawn(int i )
{
	EB[i].Enable = false;
}
bool GameEnemyBarret_IsEnable(int i)
{
	return EB[i].Enable;
}