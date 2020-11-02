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
		MessageBox(NULL, "アプリケーション終了します", "Aテクスチャの読み込みが失敗しましたのでDA", MB_OK);//OKを押されるまでプログラムがとまる
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

	//dx,dy =描画座標
	//dw ポリゴンサイズ幅
	//ctx.cty= テクスチャ切り抜き座標
	//ctw,cth= テクスチャの切り取り高さ

	SpriteDraw(g_NexStageTextureID, -390, -160, 0, 0, 1980, 1080);

}