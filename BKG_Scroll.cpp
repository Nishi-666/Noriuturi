#include "BKG_Scroll.h"
#include "TexMan.h"
#include "Sprite.h"
float BKGSCL[4];
float BKG02SCL;
static int g_BKG_SCL_01ID = TEXTURE_INVALID_ID;
static int g_BKG_SCL_02ID = TEXTURE_INVALID_ID;
bool BKG_SCR_initialize(void)
{

	g_BKG_SCL_01ID = Texture_SetTextureLoadFile("Asset\\BKG01.png");
	g_BKG_SCL_02ID = Texture_SetTextureLoadFile("Asset\\BKG02.png");
	for (int i = 0; i < 4; i++)
	{
		BKGSCL[i] = i * 0.3f;
	}

	 BKG02SCL = 0.5f;
	 return true;
}
void BKG_SCR_Update(void)
{
	for (int i = 0; i < 4; i++)
	{
		BKGSCL[i] += ((i+1) * 0.3f);
	}

}
void BKG_SCR_Draw(void)
{
	SpriteDraw(g_BKG_SCL_01ID, 0, 0, 0 + BKGSCL[0], 0, 1980 + BKGSCL[0], 1080);;// DrawPosX + (DEBUG_FONT_WIDTH / 2), DrawPosY + (DEBUG_FONT_HEIGHT / 2), Rot);

	for (int i = 1; i < 4; i++)
	{// DrawPosX + (DEBUG_FONT_WIDTH / 2), DrawPosY + (DEBUG_FONT_HEIGHT / 2), Rot);
		SpriteDraw(g_BKG_SCL_02ID, 0, 0, 0 + BKGSCL[i], 0, 1980 + BKGSCL[i], 1080);;// DrawPosX + (DEBUG_FONT_WIDTH / 2), DrawPosY + (DEBUG_FONT_HEIGHT / 2), Rot);
	}
	

}
void BKG_SCR_Finalize(void)
{

	Texture_Release(&g_BKG_SCL_01ID, 1);
	Texture_Release(&g_BKG_SCL_02ID, 1);
}