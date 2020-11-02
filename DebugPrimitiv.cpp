
#if defined(_DEBUG) || defined(DEBUG)
#include "DebugPrimitiv.h"
#include <d3dx9.h>
#include <math.h>
#include "MyDirect3D.h"

//�萔�錾
#define CIRCLE_VERTEX_COUNT (64)
#define CIRCLE_DRAW_MAX (2048)
//
typedef struct DebugVertex_tag
{
	D3DXVECTOR4 pos;
	D3DCOLOR Collar;

}DebugVertex;
#define FVF_DEBUG_VERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)
//�O���[�o���ϐ���
static LPDIRECT3DVERTEXBUFFER9 g_p_VertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 g_p_IndexBuffer = NULL;

static int g_CircleCount = 0;
static DebugVertex* g_pDebugVertex = NULL;
static WORD* g_pDebugVertexIndex = NULL;
void DebugPrimitiv_Init(void)
{
#if defined(_DEBUG) || defined(DEBUG)
	g_CircleCount = 0;//������

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
	//���_�o�b�t�@�ƒ��_�C���f�b�N�X�o�b�t�@��ۯ�����
#if defined(_DEBUG) || defined(DEBUG)
	g_p_VertexBuffer->Lock(0, 0, (void**)&g_pDebugVertex,0);
	g_p_IndexBuffer->Lock(0, 0, (void**)&g_pDebugVertexIndex, 0);

	//�ۂ̕`�施�ߐ���������	
	g_CircleCount = 0;

#endif
}

void DebugPrimitiv_BatchDrawCircle(float x, float y, float radius)
{
#if defined(_DEBUG) || defined(DEBUG)
	//�w����W���~�̒��S�Ƃ����ۂ̒��_���W���v�Z���Ē��_�o�b�t�@�ƒ��_�C���f�b�N�X�o�b�t�@�ɏ��������

	//�z��̂ǂ����珑������邩�H
	WORD n = WORD(CIRCLE_VERTEX_COUNT * g_CircleCount);
	//�O�p�`�H1���̊p�x(���W�A���p)
	float s = D3DX_PI*2.0f/ CIRCLE_VERTEX_COUNT;
	//���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�֏�񏑂�����
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
	//���_�o�b�t�@�ƒ��_�C���f�b�N�X�o�b�t�@���A�����b�N����

	g_p_VertexBuffer->Unlock();
	g_p_IndexBuffer->Unlock();
	//�ۂ̕`�施�ߕ��̊ۂ�����
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