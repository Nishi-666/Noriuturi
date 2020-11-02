/*============================================================

windows�̕\��[main.cpp]                            Author:Kai Yamaya
                                                   Date:2020/5/18
-------------------------------------------------------
												  
==============================================================
*/

//#define _CRT_SECURE_NO_WARNINGS
#include "DX98Set-up.h"
#include <Windows.h>
#include <d3d9.h>
#include<d3d9.h>
#include "mouse.h"
#include <stdio.h>//�v���W�F�N�g�̃v���p�e�B�[��VC++�f�B���N�g���ɂ���z��<>�ɂȂ��Ă�
#include "debugPrintf.h"//��ł�����͓��f�B���N�g���t�@�C�����̓z
#include <d3dx9.h>//�u�����������Ƃ������Ă��邪DX11�ɂ͓����ĂȂ����A11�͊O�����玝���Ă����悤�Ȋ���
#include"Config.h"
#include "MyDirect3D.h"
#include <stdio.h>
#include "Game.h"
#include "Debug_Font.h"
#include "DebugPrimitiv.h"
#include "system_timer.h"
#include "Sprite.h"
#include "keyboard.h"
#include "TexMan.h"
#include "KeyLoggerr.h"
//�萔��`
#define CLASS_NAME  "GameWindow"//�E�B���h�E�N���X�̖��O
#define WINDOW_CAPTION "Game"//�E�B���h�E�̖��O

//�v���g�^�C�v�錾
//�E�B���h�E�v���V�[�W��(�R�[���o�b�N�֐�)
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lPraam);
//�Q�[��������
//�߂�l�A�������Ɏ��s������false
static bool INitialize(HWND hw);
//�Q�[���X�V
static void Update(void);
//�Q�[���`��֐�
static void Draw(void);
//�Q�[���I��
static void Finalize(void);
////�O���[�o���ϐ��錾
//static LPDIRECT3D9 g_pD3D =NULL;//Direct3D�C���^�t�F�[�X
//static LPDIRECT3DDEVICE9 g_pDevice = NULL;//Direct3D�f�o�C�X�C���^�t�F�[�X

static float f = 0;
//�\���̐錾
static int g_FrameCount = 0;
static int g_BaseFrame = 0;
static double g_BaseTime = 0;
static double g_FPS = 0;
static double g_ReservaeTime = 0.0;

//���_�\����
typedef struct Vertex2D_tag
{
	D3DXVECTOR4 Position;
	D3DCOLOR Collar;
	D3DXVECTOR2 TexCoord;
}Vertex2D;
#define FVF_VERTEX3D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
//���W�ϊ��ςݒ��_ RHW =1
//����Vertex2D_tag�Ƒ΂̐��ɂȂ��ĂȂ��ƃ_��
//FVF�Ƃ̓t���L�V�u�����@�[�e�b�N�X�t�H�[�}�b�g�̗��ADirect3d�̎d�l�@
//������n�����͂ǂ��������̂ł�����Ďo����ɓ`����
//���C��
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR ipCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);//�g�p���Ȃ���ʕϐ�
	UNREFERENCED_PARAMETER(ipCmdLine);
	//�E�B���h�E�N���X�\���̂̐ݒ�//�\���̗̂v�f��������WNDCLASSEX�Ƃ������̂�����
	WNDCLASS  wc = {};//�I���W�i���̃E�B���h�E�p�[�c�����(��U�V�X�e���ɓo�^���Ă���Ăяo��)
	//�K��WNDCLASS�� hoge;�ł͕ςȕ����ꏏ�ɐ��������̂� hoge ={}��K���g������
	//�Œ���K�v�Ȃ��//�A�C�R���Ƃ��������œo�^�ł���
	wc.lpfnWndProc = WndProc;//�E�B���h�E�v���V�[�W�����Ă����֐��̐ݒ�
	wc.lpszClassName = CLASS_NAME;//�N���X���̐ݒ�//�Ԃ����Ⴏ�Ȃ�ł�����
	wc.hInstance = hInstance;//�C���X�^���g�n���h���̐ݒ�//��̃C���X�^���X�n���h��������
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);//�}�E�X�J�[�\�����w��//
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);//�E�B���h�E�̃N���C�A���g�̈�̔w�i�F���w��
	//class�o�^//������Ȃ��Ǝg���Ȃ��̂Œ���
	RegisterClass(&wc);
	DWORD style = WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX;//�_�u�����[�h�^32bit
	//^(xor(�r�b�g����))�̒��ӎ���:���Ӓl�̉�������Bit���m���ɗ����Ă��邱�Ƃ�����
	//(�����킩��Ȃ�������t�ɗ������Ⴄ�A���̂��߂��̎���&~���g���Ƃ���
	// �s���̂����E�B���h�E�T�C�Y���Z�o
	//RECT Window_rect = { 0,0,SCREEN_WHIDTH ,SCREEN_HEIGHT }; //�E�B���h�E�X�ɓ��ڂ��ꂽ�\���̂�left�ATop�Aright,bottom�Ƃ���LONG�^�������Ă���
	//AdjustWindowRect(&Window_rect, style, false);
	//
	//int window_width = Window_rect.right - Window_rect.left;//��
	//int window_height = Window_rect.bottom - Window_rect.top;//����
	//���s���ʂ͍���-8,����-31�������đ��g���c�����Ă��傤�ǂ����悤�ɂȂ�
	//�\������E�C���h�E�̏ꏊ���Z�o����
	//�f�o�C�X(�V�X�e��)���烂�j�^�𑜓x�擾
	//�v���C�}�����j�^�[�̉𑜓x�擾
	int window_width =GetSystemMetrics(SM_CXSCREEN);//��
	int window_height = GetSystemMetrics(SM_CYSCREEN);//����
	
	//������ʂ̉𑜓x�擾//�f�B�A�����j�^�[�p��
	int  virtual_desktop_width = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	int  virtual_desktop_height = GetSystemMetrics(SM_CYVIRTUALSCREEN);
	//������ʂ̍���[���W//�f�B�A�����j�^�[�p��
	int  virtual_desktop_x = GetSystemMetrics(SM_XVIRTUALSCREEN);
	int  virtual_desktop_y = GetSystemMetrics(SM_XVIRTUALSCREEN);

	int winwow_x =virtual_desktop_x +max((virtual_desktop_width- window_width) / 2, 0);
	//max(x,y)��x,y�̂ǂ��炩�傫���l���o��
	int winwow_y = virtual_desktop_y + max((virtual_desktop_height - window_height) / 2, 0);
	//������������f�X�N�g�b�v���E�B���h�E���傫���ꍇ�͍���ɕ\��
//	int winwow_x = max((window_width - window_width) / 2, 0);
//	int winwow_y = max((window_height - window_height) / 2, 0);
	//�f�X�N�g�b�v(�N���C�A���g�̈�)�̃T�C�Y

	//API��p�����f�X�N�g�b�v�������擾
	//�f�X�N�g�b�v�̒Z�^���擾
	RECT Desktop_rect;
	GetWindowRect(GetDesktopWindow(), &Desktop_rect);
	//�f�X�N�g�b�v�̕��ƍ������Z�o
	int desktop_whidth = Desktop_rect.right - Desktop_rect.left;
	int desktop_height = Desktop_rect.bottom - Desktop_rect.top;
	//�E�B���h�E����
	//!CreateWindow�o�߂��Ă���̂�HWND
	//������HWND�ɂ̓��j�[�N��ID���A���Ă���I!(�|�C���^��
	HWND hWnd = CreateWindow(//CreateWindow�֐�//�t�@�C���̃h���b�N�A���h�h���b�v���o����CreateWindowex�Ƃ������̂�����
		CLASS_NAME,//�E�B���h�E�N���X
		WINDOW_CAPTION,//�E�B���h�E�e�L�X�g//�N�������Ƃ��̍���̕���
		//���ʂ�"hogehoge"�ł��o����
		style,//�E�B���h�E�X�^�C��(�r�b�g�t���O)
		//^ (XOR)
		//�T�C�Y�ƈʒu
		CW_USEDEFAULT,//��ʂ̈�ԍ��ォ��E�B���h�E����܂ł̋���(x)
		CW_USEDEFAULT,//��ʂ̈�ԍ��ォ��E�B���h�E����܂ł̋���(y)
		//������x/y���������łȂ���ΕςɂȂ�̂Œ��ӁI�I
		//CW_USEDEFAULT��OS�C�����ĈӖ�
		window_width,//��ʃT�C�YX//�t���[�����܂񂾃T�C�Y
		window_height,//��ʃT�C�YY//�t���[�����܂񂾃T�C�Y
		NULL,//�e�E�B���h�E�n���h��//�����ɐe������Ɛe�q�֌W�ƂȂ�
		//�e�E�B���h�E���ړ�������Ǝq�E�B���h�E���ړ�����
		NULL,//���j���[�n���h��//����̕��̃t�@�C��(F)�Ƃ����̗�
		hInstance,//�C���X�^���X�n���h��
		NULL//�ǉ��̃A�v���P�[�V�����f�[�^
		//�Ȃɂ��̈���...���ĂƂ��͊�{�I��NULL������Ƃ���ǁ[�ɂ��Ȃ�
	);
	if (hWnd == NULL)
	{//�E�B���h�E�n���h�������炩�̗��R�Ő���ł��Ȃ������ꍇ
		return 0;
	}

	//�w�肵���E�B���h�E�n���h���̃E�B���h�E���w��̕��@�ŕ\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);//�E�B���h�E�̋@�\���X�V

	g_ReservaeTime = g_BaseTime = SystemTimer_GetTime();
	g_FrameCount = g_BaseFrame = 0;
	g_FPS = 0.0;

	Mouse_Initialize(hWnd);
	//InitSound(hWnd);
	if (!INitialize(hWnd))//�ŏ��̕��ɉ񂷕��@�����邪�A���[�U�r���e�B�I�ɂ̓E�B���h�E������
	//�o���ق������肪����
	{//���b�Z�[�W�{�b�N�X�ŃQ�[���̏��������s�������߃A�v���P�[�V�����I�����銴����

		MessageBox(NULL, "�A�v���P�[�V�����I�����܂�", "�Q�[���̏����������s�����̂�", MB_OK);//OK���������܂Ńv���O�������Ƃ܂�
		return 0;//����return�����������ɂ��̂܂܎E��
		
	}
#if defined(_DEBUG) || defined(DEBUG)
	
	//DebugPrimitiv_Init();
#endif
	//MyDirect3D_initialize(hWnd);
	//�E�B���h�E���b�Z�[�W�̎擾(���b�Z�[�W���[�v)
	MSG msg = {};
	//�Q�[�����[�v...�ɂ��������AGetMessage�̓��b�Z�[�W�����Ȃ��Ƒʖڂ�scanf�Ȃ̂�....
	//PeekMessage�Ƃ������b�Z�[�W�����Ȃ��Ă��i�s������̂��g���ׂ��I
	//while (GetMessage(&msg, NULL, 0, 0))
//�Q�[��������
	//DX�X����ۼު�Ă����Ȃ����������X����A
	//���̎��p����
	//�v���W�F�N�g�̃v���p�e�B//�\���͑S�Ă̍\���A���ׂẴv���b�g�t�H�[��
	//��I��
	//VC++�f�B���N�g���̃C���N���[�h�f�B���N�g��
	//�e�܂��͎q�̋K��l����p���Ƀ`�F�b�N�������Ă�
	//���Ƃ��m�F��$(DXSDK_DIR)include�Ɠ��͂���
	//���ׂẴv���b�g�t�H�[����߂�win32��I��
	//���C�u�����f�B���N�g��lib��x86��������$(DXSDK_DIR)lib|x86
	//���win32����x64�ɕύX�A�����J�̑S�ʂ̕��ł�����
	//�O���̃��C�u�������g���Ƃ��̓\�[�X�R�[�h�ɏ������@��
	//�v���p�e�B�ɏ������@�\����debug�A�v���b�g�t�H�[�������ׂẴv���b�g�t�H�[���ɁA�����J�̓��͂̒ǉ��̈ˑ��t�@�C����I�����āA
	//d3d9.lib
	//d3dx9d.lib
	//���release��I��Œǉ��̈ˑ��t�@�C���A��
	//d3d9.lib
	//d3dx9.lib
//�߂�l�A�������Ɏ��s������false

	while (WM_QUIT != msg.message)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			// message������ꍇ�̓��b�Z�[�W���������s
			TranslateMessage(&msg);
			DispatchMessage(&msg);//���b�Z�[�W���Ă΂��Ɓ���WndProc���Ă΂��
			int test;
		}
		else
		{//�����ɃQ�[���{��
			/*
			double Time= SystemTimer_GetTime();
			if ((Time + -g_ReservaeTime) < 1.0f / 60.0f)
			{
				Sleep(0);
				continue;
			}
			g_ReservaeTime = Time;
			*/
			//�Q�[���X�V
			  Update();
			//�Q�[���`��֐�
			  Draw();
		}
	}
	Finalize();
	return (int)msg.wParam;

}
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lPraam)
{//�t�b�N�Ƃ���

	switch (uMsg)
	{



	case WM_ACTIVATEAPP:
		if (wParam == VK_ESCAPE)//�G�X�P�[�v�L�[������������ꍇ
		{
			SendMessage(hwnd, WM_CLOSE, 0, 0);//WM_CLOSE���b�Z�[�W�̑��M
			UpdateWindow(hwnd);
		}
	case WM_INPUT:
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEWHEEL:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_MOUSEHOVER:
		Mouse_ProcessMessage(uMsg, wParam, lPraam);
		break;
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		Keyboard_ProcessMessage(uMsg, wParam, lPraam);
		break;
	}
	switch (uMsg)//��������̃��b�Z�[�W�������ɔ��ł���
	{
	case WM_KEYDOWN:
		break;//������break�͂�����switch���E���ĉ���return�ɉ�

	case WM_CLOSE://Window�́~�{�^��
		if (MessageBox(hwnd, "�{���ɏI�����Ă�낵���ł��傤���H", "�m�F", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK)
		{
			DestroyWindow(hwnd);//hwnd��j��
		}
		return 0;//����return�����������ɂ��̂܂܎E��
		
	case WM_DESTROY://�E�B���h�E�j�����b�Z�[�W
		PostQuitMessage(0);//WM_QUIT���b�Z�[�W�̑��M//�Ȃ����������邩�Ƃ����Ό둀��h�~
		return 0;;
	}

	//�����P�P���̂͂߂�ǂ��̂ŏ�ȊO�̒ʏ탁�b�Z�[�W�����͂��̊֐��ɔC����
	//�ǂ��Ɍv����Ă����A�q�̏ꍇ��ɂ���z�������ďI���������Ă��^�X�N��͏I���Ȃ��̂�
	//�Œ�ł��I�������́��ɏ����Ă�������
	return DefWindowProc(hwnd, uMsg, wParam, lPraam);
}
//�Q�[��������
//�߂�l�A�������Ɏ��s������false
bool INitialize(HWND hw)
{
	Keyboard_Initialize();
	KeyLogger_initialize();

	SpriteInitialize();
	Texture_initialize();
	if (!MyDirect3D_initialize(hw))
	{
		MessageBox(NULL, "�A�v���P�[�V�����I�����܂�", "D3D�̏������Ɏ��s���܂����̂�", MB_OK);//OK���������܂Ńv���O�������Ƃ܂�
     return 0;
	}
	Game_initialize(0);
	//DebugFont_initialize();
	SystemTimer_Initialize();
	DX98Initialize();

	return 1;
}


//�Q�[���X�V
void Update(void)
{
	KeyLogger_Update();
	Game_Update();
	//�v��
	double time = SystemTimer_GetTime();
		if (time - g_BaseTime > 1.0)
		{
			g_FPS = (g_FrameCount - g_BaseFrame) / (time - g_BaseTime);
			g_BaseTime = time;
			g_BaseFrame = g_FrameCount;
		}
		g_FrameCount++;
}
//�Q�[���`��֐�
void Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice)
	{
		return;
	}
	
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 200, 255), 1.0f, 0);//�w�i�F
	pDevice->BeginScene();
//	DebugPrimitiv_BatchBegin();
	Game_Draw();
//
	char buf[64];
	sprintf(buf, "FPS =%.2f", g_FPS);
	//DebugFont_Draw(0.0f, 0.0f, buf,1);

	//DebugPrimitiv_BatchRun();
	pDevice->EndScene();
	pDevice->Present(NULL, NULL, NULL, NULL);

}//�Q�[���I��
void Finalize(void)
{

//	DebugPrimitiv_Finalize();
	KeyLogger_Finalize();
	SpriteFinalaise();
	//DebugFont_finalize();
	//���Еt���̂�����:�e�N�o�̓f�o�o�ɋ����Ă�����Ă��Ă�A�e�N�X�`������Ȃ��Ȃ��ĂȂ�����e�N�o�̓o�C�o�C���Ȃ��Ƃ����Ȃ�
	Game_Finalize();
	MyDirect3D_Finalize();
}