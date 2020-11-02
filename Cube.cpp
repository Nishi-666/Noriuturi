#include "Cube.h"
//#include "Config.h"
#include "Sprite.h"
#include"MyDirect3D.h"
#include <d3d9.h>
#include <d3d9.h>
#include "TexMan.h"
#include <memory.h>

typedef struct Vertex3D_tag
{
	D3DXVECTOR3 Position;
	D3DCOLOR Collar;
	D3DXVECTOR2 TexCoord;
}Vertex3D;
#define FVF_VERTEX3D (D3DFVF_XYZ| D3DFVF_DIFFUSE|D3DFVF_TEX1)//|D3DFVF_TEX1)//game.hにcofig.hあるから除かす
////グローバル変数宣言////
//頂点データ配列(3DCube)
static  Vertex3D g_CubeVerttex[] =
{
	//手前
	{D3DXVECTOR3(-0.5f , 0.5f ,-0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0,0)},//赤
	{D3DXVECTOR3(0.5f , 0.5f ,-0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0.25f,0)},
	{D3DXVECTOR3(-0.5f , -0.5f ,-0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0,0.25f)},
	{D3DXVECTOR3(0.5f , 0.5f ,-0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0.25f,0)},
	{D3DXVECTOR3(0.5f , -0.5f ,-0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0.25f,0.25f)},
	{D3DXVECTOR3(-0.5f , -0.5f ,-0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0,0.25f)},
	//右
	{D3DXVECTOR3(0.5f , 0.5f ,-0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0,0)},//青
	{D3DXVECTOR3(0.5f , 0.5f ,0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0.25f,0)} ,
	{D3DXVECTOR3(0.5f , -0.5f ,-0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0,0.25f)},
	{D3DXVECTOR3(0.5f , 0.5f ,0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0.25f,0)},
	{D3DXVECTOR3(0.5f , -0.5f ,0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0.25f,0.25f)},
	{D3DXVECTOR3(0.5f , -0.5f ,-0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0,0.25f)},
	//上
	{D3DXVECTOR3(-0.5f , 0.5f ,0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0,0)},//黒
	{D3DXVECTOR3(0.5f , 0.5f ,0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0.25f,0)} ,
	{D3DXVECTOR3(-0.5f , 0.5f ,-0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0,0.25f)},
	{D3DXVECTOR3(0.5f , 0.5f ,0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0.25f,0)},
	{D3DXVECTOR3(0.5f , 0.5f ,-0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0.25f,0.25f)},
	{D3DXVECTOR3(-0.5f , 0.5f ,-0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0,0.25f)},

	//後方
	{D3DXVECTOR3(0.5f , -0.5f ,0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0,0)},//赤
	{D3DXVECTOR3(0.5f , 0.5f ,0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0.25f,0)},
	{D3DXVECTOR3(-0.5f , 0.5f ,0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0,0.25f)},
	{D3DXVECTOR3(-0.5f , 0.5f ,0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0.25f,0)},
	{D3DXVECTOR3(-0.5f , -0.5f ,0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0.25f,0.25f)},
	{D3DXVECTOR3(0.5f , -0.5f ,0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0,0.25f)},
	//左
	{D3DXVECTOR3(-0.5f , 0.5f ,0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0,0)},//白	
	{D3DXVECTOR3(-0.5f , 0.5f ,-0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0.25f,0)} ,
	{D3DXVECTOR3(-0.5f , -0.5f ,0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0,0.25f)},
	{D3DXVECTOR3(-0.5f , 0.5f ,-0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0.25f,0)},
	{D3DXVECTOR3(-0.5f , -0.5f ,-0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0.25f,0.25f)},
	{D3DXVECTOR3(-0.5f , -0.5f ,0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0,0.25f)},
	
	
	//下
	{D3DXVECTOR3(-0.5f , -0.5f ,-0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0,0)},
	{D3DXVECTOR3(0.5f , -0.5f ,-0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0.25f,0)} ,
	{D3DXVECTOR3(-0.5f ,-0.5f ,0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0,0.25f)},
	{D3DXVECTOR3(0.5f , -0.5f ,-0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0.25f,0)},
	{D3DXVECTOR3(0.5f , -0.5f ,0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0.25f,0.25f)},
	{D3DXVECTOR3(-0.5f , -0.5f ,0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0,0.25f)},

};
static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;//頂点バッファインタフェース
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL; //インデックスバッファインタフェース
static D3DCOLOR g_Collar = D3DCOLOR_RGBA(255, 255, 255, 255);//ポリゴンカラー//驚きの白さ
//テクスチャの管理番号

static int g_BoxTextureId =TEXTURE_INVALID_ID;
															 
															 /////////////////////////

void Cube_initialize(void)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	g_BoxTextureId = Texture_SetTextureLoadFile("Asset\\spice_and_wolf.png");
	if (Texture_Load() > 0)
	{
		MessageBox(NULL, "アプリケーション終了します", "Aテクスチャの読み込みが失敗しましたのでDA", MB_OK);//OKを押されるまでプログラムがとまる
		return;
	}
	static const D3DXVECTOR2 uv_offsets[] = {
		D3DXVECTOR2(0,0),D3DXVECTOR2(0.25f,0),D3DXVECTOR2(0.5f,0),D3DXVECTOR2(0.75f,0),
		D3DXVECTOR2(0,0.25f),D3DXVECTOR2(0.25f,0.25f)

	};
	for (int i = 0; i < 6; i++)
	{
		for (int s = 0; s < 6; s++)
		{
			g_CubeVerttex[i * 6 + s].TexCoord += uv_offsets[i];
		}
	}
	Texture_Load();
}
void Cube_Update(void)
{
}
void Cube_Draw( D3DXMATRIX* pMtxWorld)
{

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();


	pDevice->SetTransform(D3DTS_WORLD, pMtxWorld);
	//ビュー変換行列の作成

	pDevice->SetFVF(FVF_VERTEX3D);
	pDevice->SetTexture(0, texture_GetTexture(g_BoxTextureId));
	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//ポリゴンを描画！！
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,12,&g_CubeVerttex,sizeof(Vertex3D));
}
void Cube_Finalize(void)
{
	Texture_Release(&g_BoxTextureId, 1);
}