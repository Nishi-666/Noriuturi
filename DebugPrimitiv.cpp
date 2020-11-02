
#if defined(_DEBUG) || defined(DEBUG)
#include "DebugPrimitiv.h"
#include <d3dx9.h>
#include <math.h>
#include "MyDirect3D.h"

//定数宣言
#define CIRCLE_VERTEX_COUNT (64)
#define CIRCLE_DRAW_MAX (2048)
//
typedef struct DebugVertex_tag
{
	D3DXVECTOR4 pos;
	D3DCOLOR Collar;

}DebugVertex;
#define FVF_DEBUG_VERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)
//グローバル変数→
static LPDIRECT3DVERTEXBUFFER9 g_p_VertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 g_p_IndexBuffer = NULL;

static int g_CircleCount = 0;
static DebugVertex* g_pDebugVertex = NULL;
static WORD* g_pDebugVertexIndex = NULL;
void DebugPrimitiv_Init(void)
{
#if defined(_DEBUG) || defined(DEBUG)
	g_CircleCount = 0;//初期化

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice)
	{
		return;
	}
	pDevice->CreateVertexBuffer
	(sizeof(DebugVertex)*CIRCLE_VERTEX_COUNT * CIRCLE_DRAW_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_DEBUG_VERTEX,
		D3DPOOL_MANAGED,
		&g_p_VertexBuffer,
		NULL); 
	pDevice->CreateIndexBuffer
	(sizeof(DebugVertex)*CIRCLE_VERTEX_COUNT*2 * CIRCLE_DRAW_MAX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_p_IndexBuffer,
		NULL);

#endif
}
void DebugPrimitiv_Finalize(void)
{


#if defined(_DEBUG) || defined(DEBUG)
	if (g_p_IndexBuffer) {
		g_p_IndexBuffer->Release();
		g_p_IndexBuffer = NULL;
	}
	if (g_p_VertexBuffer) {
		g_p_VertexBuffer->Release();
		g_p_VertexBuffer = NULL;
	}
#endif
}
void DebugPrimitiv_BatchBegin(void)
{
	//頂点バッファと頂点インデックスバッファをﾛｯｸする
#if defined(_DEBUG) || defined(DEBUG)
	g_p_VertexBuffer->Lock(0, 0, (void**)&g_pDebugVertex,0);
	g_p_IndexBuffer->Lock(0, 0, (void**)&g_pDebugVertexIndex, 0);

	//丸の描画命令数を初期化	
	g_CircleCount = 0;

#endif
}

void DebugPrimitiv_BatchDrawCircle(float x, float y, float radius)
{
#if defined(_DEBUG) || defined(DEBUG)
	//指定座標を円の中心とした丸の頂点座標を計算して頂点バッファと頂点インデックスバッファに書き入れる

	//配列のどこから書き入れるか？
	WORD n = WORD(CIRCLE_VERTEX_COUNT * g_CircleCount);
	//三角形？1個分の角度(ラジアン角)
	float s = D3DX_PI*2.0f/ CIRCLE_VERTEX_COUNT;
	//頂点バッファとインデックスバッファへ情報書き込み
	for (int i = 0; i < CIRCLE_VERTEX_COUNT; i++)
	{
		g_pDebugVertex[n + i].pos.x = cosf(s*i)*radius + x;
		g_pDebugVertex[n + i].pos.y = sinf(s*i)*radius + y;
		g_pDebugVertex[n + i].pos.z = 1.0f;
		g_pDebugVertex[n + i].pos.w = 1.0f;
		g_pDebugVertex[n + i].Collar= D3DCOLOR_RGBA(0, 255, 0, 255);
		g_pDebugVertexIndex[n + 2+i *2] =n + i;

		g_pDebugVertexIndex[n + 2 + i * 2+1] = n + (1+i) % CIRCLE_VERTEX_COUNT;
	}
	g_CircleCount++;
#endif

}
void DebugPrimitiv_BatchRun(void)
{
#if defined(_DEBUG) || defined(DEBUG)
	//頂点バッファと頂点インデックスバッファをアンロックする

	g_p_VertexBuffer->Unlock();
	g_p_IndexBuffer->Unlock();
	//丸の描画命令分の丸を書く
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	int vn = g_CircleCount * CIRCLE_VERTEX_COUNT;

	pDevice->SetFVF(FVF_DEBUG_VERTEX);
	pDevice->SetStreamSource(0, g_p_VertexBuffer, 0, sizeof(DebugVertex));
	pDevice->SetIndices(g_p_IndexBuffer);
	pDevice->SetTexture(0, NULL);
	pDevice->DrawIndexedPrimitive(D3DPT_LINELIST, 0, 0, vn, 0, vn);


#endif
}
#endif