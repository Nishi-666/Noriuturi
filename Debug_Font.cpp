/*============================================================

�f�o�b�O�t�H���g���W���[��[Debug_Font.h]                           Author:Kai Yamaya
												   Date:2020/7/13
-------------------------------------------------------

==============================================================*/

#include "Debug_Font.h"
#include "TexMan.h"
#include <string.h>
#include "Sprite.h"

#define DEBUG_FONT_WIDTH (32)
#define DEBUG_FONT_RETOROT_WIDTH (32)
#define DEBUG_FONT_HEIGHT (64)
#define DEBUG_FONT_RETORO_HEIGHT (62)
#define TART_CHAR_CODE (32)
#define END_CHAR_CODE (126)
#define LINE_CHAR_COUNT (16)


static int g_TextureID = TEXTURE_INVALID_ID;
static int g_TextureRETROID = TEXTURE_INVALID_ID;

void DebugFont_initialize(void)
{

	LPDIRECT3DDEVICE9 g_pDevice = MyDirect3D_GetDevice();
	if (!g_pDevice)
	{
		return ;
	}
	//�e�N�X�`���̓ǂݍ��ݗ\��//DirectX�׋��p\DX-04 �e�N�X�`���}�l�[�W��\DX-02 MessageBox\Asset
	g_TextureID = Texture_SetTextureLoadFile("Asset\\debug_font_32x64.png");
	g_TextureRETROID = Texture_SetTextureLoadFile("Asset\\Debug_Font_RETRO2.png");
	if (Texture_Load() > 0)
	{
		MessageBox(NULL, "�A�v���P�[�V�����I�����܂�", "�e�N�X�`���̓ǂݍ��݂����s���܂����̂�DA", MB_OK);//OK���������܂Ńv���O�������Ƃ܂�
		return ;
	}
	else
	{
	//	MessageBox(NULL, "OK", "�e�N�X�`���ǂݍ���", MB_OK);//OK���������܂Ńv���O�������Ƃ܂�
	}



	//g_TextureID = Texture_SetTextureLoadFile("Asset\\debug_font_32x64.png");
	//if (Texture_Load() > 0)
	//{
	//	MessageBox(NULL, "�A�v���P�[�V�����I�����܂�", "�e�N�X�`���̓ǂݍ��݂����s���܂����̂�", MB_OK);//OK���������܂Ńv���O�������Ƃ܂�
	//}
}
void DebugFont_finalize(void)
{
	Texture_Release(&g_TextureID, 1);
}
//�f�o�b�O�t�H���g�̕\��
//Dx/Dy�f�o�b�O���W�ւ̕`����W
//����:pString:�f�o�b�O������ւ̃|�C���^
void DebugFont_Draw(float Dx, float Dy, const char* pString, int FontNum)
{//32����126�Ԃ܂ł̃t�H���g(�X�y�[�X����"~"�܂�)//1�s16
	for (int i = 0; i < strlen(pString); i++)
	{
		//dx,dy =�`����W
		//dw �|���S���T�C�Y��
		//ctx.cty= �e�N�X�`���؂蔲�����W
		//ctw,cth= �e�N�X�`���̐؂��荂��
		//void SpriteDraw(int TextureId, float DX, float DY, float DW, float DH, int ctx, int cty, int ctw, int cth);
		int offset = pString[i] - ' ';
		//	int tcx = offset % LINE_CHAR_COUNT*DEBUG_FONT_WIDTH;
		if (FontNum == 0) {
			int tcx = offset % LINE_CHAR_COUNT*DEBUG_FONT_WIDTH;
			int tcy = offset / LINE_CHAR_COUNT * DEBUG_FONT_HEIGHT;
			SpriteDraw(g_TextureID, Dx + (i* DEBUG_FONT_WIDTH), Dy, tcx, tcy, DEBUG_FONT_WIDTH, DEBUG_FONT_HEIGHT);
		}
		if (FontNum == 1) {
			int tcx = offset % LINE_CHAR_COUNT*DEBUG_FONT_RETOROT_WIDTH;
			int tcy = offset / LINE_CHAR_COUNT * DEBUG_FONT_RETORO_HEIGHT;
			SpriteDraw(g_TextureRETROID, Dx + (i* DEBUG_FONT_RETOROT_WIDTH), Dy, tcx, tcy, DEBUG_FONT_RETOROT_WIDTH, DEBUG_FONT_RETORO_HEIGHT);
		}
	}
}
void DebugFont_Draw(float Dx, float Dy, const char* pString, int FontNum, float FontSize)
{//32����126�Ԃ܂ł̃t�H���g(�X�y�[�X����"~"�܂�)//1�s16
	for (int i = 0; i < strlen(pString); i++)
	{
		//dx,dy =�`����W
		//dw �|���S���T�C�Y��
		//ctx.cty= �e�N�X�`���؂蔲�����W
		//ctw,cth= �e�N�X�`���̐؂��荂��
		//void SpriteDraw(int TextureId, float DX, float DY, float DW, float DH, int ctx, int cty, int ctw, int cth);
		int offset = pString[i] - ' ';
		//	int tcx = offset % LINE_CHAR_COUNT*DEBUG_FONT_WIDTH;
		if (FontNum == 0) {
			int tcx = offset % LINE_CHAR_COUNT*DEBUG_FONT_WIDTH;
			int tcy = offset / LINE_CHAR_COUNT * DEBUG_FONT_HEIGHT;
			SpriteDraw(g_TextureID, Dx + (i* (DEBUG_FONT_RETOROT_WIDTH*FontSize)), Dy, tcx, tcy, DEBUG_FONT_WIDTH, DEBUG_FONT_HEIGHT,FontSize);
		}
		if (FontNum == 1) {
			int tcx = offset % LINE_CHAR_COUNT*DEBUG_FONT_RETOROT_WIDTH;
			int tcy = offset / LINE_CHAR_COUNT * DEBUG_FONT_RETORO_HEIGHT;
			SpriteDraw(g_TextureRETROID, Dx + (i* (DEBUG_FONT_RETOROT_WIDTH*FontSize)), Dy, tcx, tcy, DEBUG_FONT_RETOROT_WIDTH, DEBUG_FONT_RETORO_HEIGHT,FontSize);
		}
	}
}