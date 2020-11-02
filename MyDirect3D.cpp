
#include <Windows.h>
#include <d3d9.h>
#include <d3d9.h>
#include "Config.h"
//#include <d3dx9.h>//�u�����������Ƃ������Ă��邪DX11�ɂ͓����ĂȂ����A11�͊O�����玝���Ă����悤�Ȋ���

//�O���[�o���ϐ��錾
static LPDIRECT3D9 g_pD3D = NULL;//Direct3D�C���^�t�F�[�X
static LPDIRECT3DDEVICE9 g_pDevice = NULL;//Direct3D�f�o�C�X�C���^�t�F�[�X
//�֐���`



//Direct3D9�̏������A���s����false�𓊉�
bool MyDirect3D_initialize(HWND hw)
{

	//Direct3D�C���^�t�F�[�X�̎擾
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{

		MessageBox(NULL, "�A�v���P�[�V�����I�����܂�", "Direct3D�C���^�t�F�[�X�̍쐬�����s���܂����̂�", MB_OK);//OK���������܂Ńv���O�������Ƃ܂�
		return false;
	}
	//Direct3D�f�o�C�X�̎擾

	//�f�o�C�X�̎擾�ɕK�v�ȏ��\���̂̍쐬
	D3DPRESENT_PARAMETERS d3dpp = {};
	

	d3dpp.BackBufferWidth = 1280;//�o�b�N�o�b�t�@�̃T�C�Y�ݒ�
	d3dpp.BackBufferHeight = 720;//�����T�C�Y���Ⴄ�ƈ������΂����
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;//�o�b�N�o�b�t�@�̃t�H�[�}�b�g//�f�X�N�g�b�v�̃t�H�[�}�b�g�Ɠ���
	d3dpp.BackBufferCount = 1;//�o�b�N�o�b�t�@��1����ă_�u���o�b�t�@�ɂ���
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;//�X���b�v���@�̐ݒ�
	d3dpp.Windowed = TRUE;//�t���X�N���[���ɂ��邩�E�B���h�E�ɂ��邩
	//��������true��C++����A������D3D��windows����̑啶���̕�
	d3dpp.EnableAutoDepthStencil = TRUE;//�[�x�o�b�t�@�A�X�e���V���o�b�t�@�̎g�p���邩
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//�[�x�o�b�t�@�E�X�e���V���o�b�t�@���O�ɂ������ɂ������Ă�����������
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//�t���X�N���[�����̃��t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;//���t���b�V�����[�g��Present�����̊֌W���w�肷��
	//d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;//�����CPU�̏������ԂɈˑ��������\�o���邾���o����(���肵�Ȃ���//���t���b�V�����[�g��Present�����̊֌W���w�肷��
	//����ł��܂����������������x�Ȃ̂ł܂��o���ĂȂ�

	HRESULT hr;
	hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hw, D3DCREATE_HARDWARE_VERTEXPROCESSING/*�n�[�h�E�F�A�Ōv�Z�������ǂ���*/, &d3dpp, &g_pDevice);
	//����Ŕ��������������̂𔭒���ɂ��������Ĕ������Ă��炤//&g_pDevice�ɗǂ����ȓz�̏ꏊ�������Ă���銴��,�����Ă��ꂪ�����ƃ|���S���P���炩���Ȃ�
	//�������̓f�o�C�X�őS�Ă���Ă���邩�A�R���s���[�^�Ōv�Z���邩��I�ׂ�A�����đ�O������//���̎q�ɏ��̎q���Љ�Ă��炤�悤�Ȋ���
	//DX�n�̊֐���HRESULT�Ƃ������ʂ�Ԃ��Ă����
	if (FAILED(hr))
	{//FAILED�ŕ��ł�鎖�ɂ�莸�s�����ׂ邱�Ƃ��o����
	//���s�␬���������肷��ꍇ��FAILED()��SUCCEEDED��()���g���ׂ�
		MessageBox(NULL, "�A�v���P�[�V�����I�����܂�", "Direct3D�f�o�C�X�̎擾�ɂ����s���܂����̂�", MB_OK);//OK���������܂Ńv���O�������Ƃ܂�
		return false;
	}
	//�����Ƀe�N�X�`�����������

	//UV�A�h���b�V���O���[�h�̐ݒ�
	//g_pDevice->SetSamplerState;//�����̓_�u�����b�v(����)���[�h(1�Ŋ��������܂肪�o��(�܂�4�Ƃ����Ă����Ă��Ɖ摜�T�C�Y/4�������̂�4�o��
	//U���c�@�AV����
	
	g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);//���ꂪ�����ݒ�
	//�e�N�X�`���t�B���^�����O�̐ݒ�
	g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
	g_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	g_pDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 16);

	//g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	//g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);//���ꂪCLAMP,�Ō�̃��C���̃s�N�Z�������̂܂܉���

	//g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);//����MIRROR�͂���s��𒼂��̂ɕ֗��ł���
	//g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);//���ꂪMIRROR,���]����(2�ȏ�̏ꍇ�͂܂�����ɔ��]����..���Ċ����́A

	//g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER);//BORDER
	//g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);//���ꂪBORDER,UV�Q�ƒl�O�͉���D3DCOLOR_RGBA�œh��Ԃ�
	//g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DCOLOR_RGBA(255,255,0,255));//����Ȃɏ������������Ă��Ƃ���Ȃ��A���̍s������biginscene�AEndscene�̎��ɌĂяo���Ă���K

	//�ق�Ɠ�
//�A���t�@�u�����h�̐ݒ�
	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);//�A���t�@�u�����h�L���ɂ���
	//������	�`��F=������`�悷��RGB*������`�悷�郿+��ʂ�RGB*(�P-������`�悷�郿)
	g_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//�|���S��RGB * �e�N�X�`��RGB
	//�e�N�X�`���� * �e�N�X�`�����ɂ��鏈��
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	return true;//����������
}
//Direct3D9�̏I�������A���s����0�𓊉�
void MyDirect3D_Finalize(void)
{
	if(g_pDevice==nullptr)
	{
		MessageBox(NULL, "�G���[", "g_pDevice", MB_OK);//OK���������܂Ńv���O�������Ƃ܂�

	}
	if (g_pDevice)
	{
		g_pDevice->Release();
		g_pDevice = NULL;
	}

	if (g_pD3D == nullptr)
	{
		MessageBox(NULL, "�G���[(�ʂ��)", "g_pD3D", MB_OK);//OK���������܂Ńv���O�������Ƃ܂�
	}

	if (g_pD3D)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}
LPDIRECT3DDEVICE9 MyDirect3D_GetDevice(void)
{
	return g_pDevice;
}


LPDIRECT3D9 MyDirect3D_GetLPDIRECT3D9(void)
{
	return g_pD3D;
}