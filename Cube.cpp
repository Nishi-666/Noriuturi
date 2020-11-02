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
#define FVF_VERTEX3D (D3DFVF_XYZ| D3DFVF_DIFFUSE|D3DFVF_TEX1)//|D3DFVF_TEX1)//game.h��cofig.h���邩�珜����
////�O���[�o���ϐ��錾////
//���_�f�[�^�z��(3DCube)
static  Vertex3D g_CubeVerttex[] =
{
	//��O
	{D3DXVECTOR3(-0.5f , 0.5f ,-0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0,0)},//��
	{D3DXVECTOR3(0.5f , 0.5f ,-0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0.25f,0)},
	{D3DXVECTOR3(-0.5f , -0.5f ,-0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0,0.25f)},
	{D3DXVECTOR3(0.5f , 0.5f ,-0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0.25f,0)},
	{D3DXVECTOR3(0.5f , -0.5f ,-0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0.25f,0.25f)},
	{D3DXVECTOR3(-0.5f , -0.5f ,-0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0,0.25f)},
	//�E
	{D3DXVECTOR3(0.5f , 0.5f ,-0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0,0)},//��
	{D3DXVECTOR3(0.5f , 0.5f ,0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0.25f,0)} ,
	{D3DXVECTOR3(0.5f , -0.5f ,-0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0,0.25f)},
	{D3DXVECTOR3(0.5f , 0.5f ,0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0.25f,0)},
	{D3DXVECTOR3(0.5f , -0.5f ,0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0.25f,0.25f)},
	{D3DXVECTOR3(0.5f , -0.5f ,-0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0,0.25f)},
	//��
	{D3DXVECTOR3(-0.5f , 0.5f ,0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0,0)},//��
	{D3DXVECTOR3(0.5f , 0.5f ,0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0.25f,0)} ,
	{D3DXVECTOR3(-0.5f , 0.5f ,-0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0,0.25f)},
	{D3DXVECTOR3(0.5f , 0.5f ,0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0.25f,0)},
	{D3DXVECTOR3(0.5f , 0.5f ,-0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0.25f,0.25f)},
	{D3DXVECTOR3(-0.5f , 0.5f ,-0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0,0.25f)},

	//���
	{D3DXVECTOR3(0.5f , -0.5f ,0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0,0)},//��
	{D3DXVECTOR3(0.5f , 0.5f ,0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0.25f,0)},
	{D3DXVECTOR3(-0.5f , 0.5f ,0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0,0.25f)},
	{D3DXVECTOR3(-0.5f , 0.5f ,0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0.25f,0)},
	{D3DXVECTOR3(-0.5f , -0.5f ,0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0.25f,0.25f)},
	{D3DXVECTOR3(0.5f , -0.5f ,0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0,0.25f)},
	//��
	{D3DXVECTOR3(-0.5f , 0.5f ,0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0,0)},//��	
	{D3DXVECTOR3(-0.5f , 0.5f ,-0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0.25f,0)} ,
	{D3DXVECTOR3(-0.5f , -0.5f ,0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0,0.25f)},
	{D3DXVECTOR3(-0.5f , 0.5f ,-0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0.25f,0)},
	{D3DXVECTOR3(-0.5f , -0.5f ,-0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0.25f,0.25f)},
	{D3DXVECTOR3(-0.5f , -0.5f ,0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0,0.25f)},
	
	
	//��
	{D3DXVECTOR3(-0.5f , -0.5f ,-0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0,0)},
	{D3DXVECTOR3(0.5f , -0.5f ,-0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0.25f,0)} ,
	{D3DXVECTOR3(-0.5f ,-0.5f ,0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0,0.25f)},
	{D3DXVECTOR3(0.5f , -0.5f ,-0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0.25f,0)},
	{D3DXVECTOR3(0.5f , -0.5f ,0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0.25f,0.25f)},
	{D3DXVECTOR3(-0.5f , -0.5f ,0.5f),D3DCOLOR_RGBA(255,255,255,225),D3DXVECTOR2(0,0.25f)},

};
static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;//���_�o�b�t�@�C���^�t�F�[�X
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL; //�C���f�b�N�X�o�b�t�@�C���^�t�F�[�X
static D3DCOLOR g_Collar = D3DCOLOR_RGBA(255, 255, 255, 255);//�|���S���J���[//�����̔���
//�e�N�X�`���̊Ǘ��ԍ�

static int g_BoxTextureId =TEXTURE_INVALID_ID;
															 
															 /////////////////////////

void Cube_initialize(void)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	g_BoxTextureId = Texture_SetTextureLoadFile("Asset\\spice_and_wolf.png");
	if (Texture_Load() > 0)
	{
		MessageBox(NULL, "�A�v���P�[�V�����I�����܂�", "A�e�N�X�`���̓ǂݍ��݂����s���܂����̂�DA", MB_OK);//OK���������܂Ńv���O�������Ƃ܂�
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
	//�r���[�ϊ��s��̍쐬

	pDevice->SetFVF(FVF_VERTEX3D);
	pDevice->SetTexture(0, texture_GetTexture(g_BoxTextureId));
	//���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//�|���S����`��I�I
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,12,&g_CubeVerttex,sizeof(Vertex3D));
}
void Cube_Finalize(void)
{
	Texture_Release(&g_BoxTextureId, 1);
}