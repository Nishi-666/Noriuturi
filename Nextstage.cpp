#include "NextStage.h"
#include "Game.h"
#include "keyboard.h"
#include "KeyLoggerr.h"
#include "TexMan.h"
#include "Sprite.h"

static int g_NexStageTextureID = TEXTURE_INVALID_ID;
void NexStageInitialize(void)
{
	g_NexStageTextureID = Texture_SetTextureLoadFile("Asset\\NextStage.png");
	if (Texture_Load() > 0)
	{
		MessageBox(NULL, "�A�v���P�[�V�����I�����܂�", "A�e�N�X�`���̓ǂݍ��݂����s���܂����̂�DA", MB_OK);//OK���������܂Ńv���O�������Ƃ܂�
		return;
	}
}
void NexStageFinalize(void)
{
	Texture_Release(&g_NexStageTextureID, 1);
}
bool NexStageUpdate(void)
{

	return 0;
}
void NexStageDraw(void)
{
	PolygonDraw(0, 0, 1980, 1080, 255, 0, 0, 255);

	//dx,dy =�`����W
	//dw �|���S���T�C�Y��
	//ctx.cty= �e�N�X�`���؂蔲�����W
	//ctw,cth= �e�N�X�`���̐؂��荂��

	SpriteDraw(g_NexStageTextureID, -390, -160, 0, 0, 1980, 1080);

}