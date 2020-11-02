#include "Game_Player.h"
#include "Debug_Font.h"
#include "TexMan.h"
#include "Player.h"
#include <string.h>
#include "Sprite.h"
#include <stdio.h>
#include <time.h>

#define DEBUG_FONT_WIDTH (140)
#define DEBUG_FONT_HEIGHT (200)
#define TART_CHAR_CODE (32)
#define END_CHAR_CODE (126)
#define LINE_CHAR_WIDTH (5)
#define LINE_CHAR_HEIGHT (2)



static int Work_texture = TEXTURE_INVALID_ID;
int Woak = 1, DrawPosX = 320 - (DEBUG_FONT_WIDTH / 2), DrawPosY = (SCREEN_HEIGHT / 4) - (DEBUG_FONT_HEIGHT / 2), DataRotNum;
int PosX = 0, PosY = 0;//DrawPos�͂����P�ɃQ�[����̕`��p�ł��������ʒu
float Rot = 0;
float DataPow = 0, DataRot = 0;
clock_t start, Nou;

//�Q�[���v���C���[�̏�����
void GamePlayer_initialize(void)
{

	
	LPDIRECT3DDEVICE9 g_pDevice = MyDirect3D_GetDevice();
	if (!g_pDevice)
	{
		return;
	}
	//�e�N�X�`���̓ǂݍ��ݗ\��//DirectX�׋��p\DX-04 �e�N�X�`���}�l�[�W��\DX-02 MessageBox\Asset
	Work_texture = Texture_SetTextureLoadFile("Asset\\runningman100.png");
	if (Texture_Load() > 0)
	{
		MessageBox(NULL, "�A�v���P�[�V�����I�����܂�", "�e�N�X�`���̓ǂݍ��݂����s���܂����̂�DA", MB_OK);//OK���������܂Ńv���O�������Ƃ܂�
		return;
	}
	else
	{
		//MessageBox(NULL, "OK", "�e�N�X�`���ǂݍ���", MB_OK);//OK���������܂Ńv���O�������Ƃ܂�
	}
}

//�I��
void GamePlayer_Finalize(void)
{
	Texture_Release(&Work_texture, 1);
}

//�X�V
void GamePlayer_Update(void)
{
	Nou = clock();
}

//�`��
void GamePlayer_Draw(void)
{
	//dx,dy =�`����W
	//dw �|���S���T�C�Y��
	//ctx.cty= �e�N�X�`���؂蔲�����W
	//ctw,cth= �e�N�X�`���̐؂��荂��
	//void SpriteDraw(int TextureId, float DX, float DY, float DW, float DH, int ctx, int cty, int ctw, int cth);
	/*�o�b�N�O���E���h�p*/
	//PolygonDraw(0, 0, SCREEN_WHIDTH, SCREEN_HEIGHT, 0, 0, 255, 255);
	//PolygonDraw(0, (SCREEN_HEIGHT / 2) + PosY, SCREEN_WHIDTH, SCREEN_HEIGHT, 0, 255, 0, 255);


	int tcx = Woak % LINE_CHAR_WIDTH*DEBUG_FONT_WIDTH;
	int tcy = Woak / LINE_CHAR_HEIGHT * DEBUG_FONT_HEIGHT;
	SpriteDraw(Work_texture, PosX, PosY, tcx, tcy, DEBUG_FONT_WIDTH, DEBUG_FONT_HEIGHT);
	//SpriteDraw(g_textureID, 400, 320.0f, 32.0f, 32.0f, tcx, 0, 32, 32, 16, 16, f);
	SpriteDraw(Work_texture, DrawPosX, DrawPosY, tcx, tcy, DEBUG_FONT_WIDTH, DEBUG_FONT_HEIGHT, DrawPosX + (DEBUG_FONT_WIDTH / 2), DrawPosY + (DEBUG_FONT_HEIGHT / 2), Rot);

}

//�Q�[���v���C���[�ړ�
void GamePlayer_MoveUp(void)
{

}
void GamePlayer_MoveDown(void)
{

}
void GamePlayer_MoveLeft(void) 
{

}
void GamePlayer_MoveRight(void)
{

}
