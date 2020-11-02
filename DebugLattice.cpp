/*
xz���ʃO���b�g�`��(DebugLattice.cpp)
	2020�N10��13��
	�R�J�J��
*/#include "Cube.h"
	//#include "Config.h"
#include "Sprite.h"
#include"MyDirect3D.h"
#include <d3d9.h>
#include <memory.h>
#include <stdio.h>
#include <malloc.h>
#include "DebugLattice.h"
//�\���̐錾
typedef struct Vertex3D_tag
{
	D3DXVECTOR3 Position;
	D3DCOLOR Collar;
	//D3DXVECTOR2 TexCoord;
}Vertex3D;
#define FVF_VERTEX3D (D3DFVF_XYZ| D3DFVF_DIFFUSE)//|D3DFVF_TEX1)//game.h��cofig.h���邩�珜����
//�O���[�o���ϐ��錾
static Vertex3D* g_pVertex = NULL;
static int g_Vertexcount=0;
static int g_linecount = 0;

//�֐���`
void LatticeInit(float size, float count, D3DCOLOR Collar)
{
	g_linecount= (count + 1) * 2;
	g_Vertexcount = g_linecount*2;

	g_pVertex = (Vertex3D*)malloc(g_Vertexcount * sizeof(Vertex3D));

	float length = size * count;
	float start = -length * 0.5f;
	float end = length * 0.5f;
	for (int i = 0; i < count + 1; i++)
	{
		g_pVertex[i * 2].Position					= D3DXVECTOR3(start + size * i, 0.0f, start);
		g_pVertex[i * 2 + 1].Position				= D3DXVECTOR3(start + size * i, 0.0f, end);
		g_pVertex[g_linecount + i * 2].Position		= D3DXVECTOR3(start, 0.0f, start+size*i);
		g_pVertex[g_linecount + i * 2 + 1].Position = D3DXVECTOR3(end, 0.0f, start+size*i);

	}
	for (int i = 0; i < g_Vertexcount ; i++)
	{
		g_pVertex[i].Collar = Collar;
	}
}
void LatticeFnalize(void)
{
	free(g_pVertex);
}
void LatticeDraw(void)
{

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	D3DXMATRIX MtxWorld;

	D3DXMatrixIdentity(&MtxWorld);/*�P�ʍs��*///MtxWorld =1
	//�f�o�o�Ƀ��[���h�ϊ��s���ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &MtxWorld);
	//�r���[�ϊ��s��̍쐬


	pDevice->SetFVF(FVF_VERTEX3D);
	pDevice->SetTexture(0, NULL);
	//���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//�|���S����`��I�I
	pDevice->DrawPrimitiveUP(D3DPT_LINELIST, g_linecount, g_pVertex, sizeof(Vertex3D));
}
