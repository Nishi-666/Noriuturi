


#define _CRT_SECURE_NO_WARNINGS

// ���E�����t�H���g�\���T���v���v���O����

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include "Font.h"
#include "MyDirect3D.h"
#include <windows.h>
#include <tchar.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

//TCHAR gName[100] = _T("���E�����t�H���g�\���T���v���v���O����");

LPDIRECT3DDEVICE9 g_pD3DDev;
LPDIRECT3D9 g_pD3D;

IDirect3DTexture9 *pTexs[5][255] = {};
int TexSize[5] = {};

UINT code[5][51] = {};
int fontWidth;
int fontHeight;
TEXTMETRIC tm;///�g�p�����t�H���g�̑傫���E���E�����E�����Ȃǂ����\���̂ł��F
GLYPHMETRICS gm[5];
bool bShowTextMetrics = true;

struct Vtx {
	float x, y, z;
	float u, v;
};
Vtx vtxs[4];


struct LineVtx {
	float x, y, z;
	DWORD color;
};

void drawLineW(IDirect3DDevice9* dev, float sx, float sy, float sz, float ex, float ey, float ez, DWORD color) {
	LineVtx p[2] = {
			{sx, sy, sz, color},
			{ex, ey, ez, color}
	};
	dev->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
	dev->DrawPrimitiveUP(D3DPT_LINELIST, 1, &p, sizeof(LineVtx));
}

void drawRectW(IDirect3DDevice9* dev, float l, float t, float w, float h, DWORD color) {
	drawLineW(dev, l, t, 0.0f, l + w, t, 0.0f, color);
	drawLineW(dev, l + w, t, 0.0f, l + w, t - h, 0.0f, color);
	drawLineW(dev, l + w, t - h, 0.0f, l, t - h, 0.0f, color);
	drawLineW(dev, l, t - h, 0.0f, l, t, 0.0f, color);
}

void drawTextMetrics(IDirect3DDevice9 *dev, TEXTMETRIC tm, GLYPHMETRICS gm, int ox, int oy) {
	D3DXMATRIX idn;
	D3DXMatrixIdentity(&idn);
	dev->SetTransform(D3DTS_WORLD, &idn);
	dev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	// Base Line
	D3DVIEWPORT9 vp;
	dev->GetViewport(&vp);
//	drawLineW(dev, (float)vp.Width / -2.0f, (float)oy, 0.0f, (float)vp.Width / 2, (float)oy, 0.0f, 0xffff0000);

	// Ascent Line
//	drawLineW(dev, (float)vp.Width / -2.0f, (float)(oy + tm.tmAscent), 0.0f, (float)vp.Width / 2, (float)(oy + tm.tmAscent), 0.0f, 0xffff0000);
	// Descent Line
//	drawLineW(dev, (float)vp.Width / -2.0f, (float)(oy - tm.tmDescent), 0.0f, (float)vp.Width / 2, (float)(oy - tm.tmDescent), 0.0f, 0xffff0000);

	// Origin
//	drawRectW(dev, (float)ox - 2.0f, (float)oy + 2.0f, 4.0f, 4.0f, 0xff00ff00);

	// Next Origin
//	drawRectW(dev, (float)(ox + gm.gmCellIncX) - 2.0f, (float)oy + 2.0f, 4.0f, 4.0f, 0xffffff00);

	// BlackBox
//	drawRectW(dev, (float)(ox + gm.gmptGlyphOrigin.x), (float)(oy + gm.gmptGlyphOrigin.y), (float)gm.gmBlackBoxX, (float)gm.gmBlackBoxY, 0x00ff0000ff);
};
/*
LRESULT CALLBACK WndProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam) {
	switch (mes) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CHAR:
		if (wParam == 's')
			bShowTextMetrics = !bShowTextMetrics;
		break;
	}
	return DefWindowProc(hWnd, mes, wParam, lParam);
}
*/


void FontSet(const wchar_t Words[],int SetNum)
{
	 g_pD3DDev = MyDirect3D_GetDevice();
	 g_pD3D = MyDirect3D_GetLPDIRECT3D9();
	// �t�H���g�r�b�g�}�b�v�擾
	 wchar_t c[] = L"_____________________________________________";
	 
	 TexSize[SetNum] = wcslen(Words);
	wcsncpy(c, Words, TexSize[SetNum]);
	// wcscpy_s(c, 60, Words);
//	wcscpy(c, Words);
	
	int i = 0;
	//�ł���
		for (int i = 0; i < TexSize[SetNum]; i++)
		{
			// �t�H���g�̐���
			int fontSize = 260;
			int fontWeight = 500;
			LOGFONT lf = { fontSize, 0, 0, 0, fontWeight, 0, 0, 0, SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("�l�r �o����") };
			//      LOGFONT lf = {fontSize, 0, 0, 0, fontWeight, 0, 0, 0, SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("�l�r �o�S�V�b�N")};
			HFONT hFont = CreateFontIndirect(&lf);
			if (hFont == NULL) {
				g_pD3DDev->Release(); g_pD3D->Release();
				return;
			}
			// �f�o�C�X�Ƀt�H���g���������Ȃ���GetGlyphOutline�֐��̓G���[�ƂȂ�
			HDC hdc = GetDC(NULL);
			HFONT oldFont = (HFONT)SelectObject(hdc, hFont);


			GetTextMetrics(hdc, &tm);
			code[SetNum][i] = (UINT)c[i];

			const int gradFlag = GGO_GRAY4_BITMAP; // GGO_GRAY2_BITMAP or GGO_GRAY4_BITMAP or GGO_GRAY8_BITMAP
			int grad = 0; // �K���̍ő�l
			switch (gradFlag) {
			case GGO_GRAY2_BITMAP: grad = 4; break;
			case GGO_GRAY4_BITMAP: grad = 16; break;
			case GGO_GRAY8_BITMAP: grad = 64; break;
			}
			if (grad == 0) {
				g_pD3DDev->Release(); g_pD3D->Release();
				return;
			}



			CONST MAT2 mat = { {0,1},{0,0},{0,0},{0,1} };
			DWORD size = GetGlyphOutlineW(hdc, code[SetNum][i], gradFlag, &gm[SetNum], 0, NULL, &mat);
			BYTE *pMono = new BYTE[size];
			GetGlyphOutlineW(hdc, code[SetNum][i], gradFlag, &gm[SetNum], size, pMono, &mat);

			// �f�o�C�X�R���e�L�X�g�ƃt�H���g�n���h���͂�������Ȃ��̂ŉ��
			SelectObject(hdc, oldFont);
			ReleaseDC(NULL, hdc);
			// �e�N�X�`���쐬
			//IDirect3DTexture9 *pTex = 0;
			DWORD alpha;

			fontWidth = (gm[SetNum].gmBlackBoxX + 3) / 4 * 4;
			fontHeight = gm[SetNum].gmBlackBoxY;
			g_pD3DDev->CreateTexture(fontWidth, fontHeight, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &pTexs[SetNum][i], NULL);

			// �e�N�X�`���Ƀt�H���g�r�b�g�}�b�v������������
			D3DLOCKED_RECT lockedRect;
			pTexs[SetNum][i]->LockRect(0, &lockedRect, NULL, 0);  // ���b�N
			DWORD *pTexBuf = (DWORD*)lockedRect.pBits;   // �e�N�X�`���������ւ̃|�C���^


			//�����ŏ�������ł�@//alpha�ɕ������P�h�b�g���J���[�R�[�h�炵�����̂œ��ꂽ�̂��ɂ��������Ă���H
			for (int y = 0; y < fontHeight; y++) {
				for (int x = 0; x < fontWidth; x++) {
					alpha = pMono[y * fontWidth + x] * 255 / grad;
					pTexBuf[y * fontWidth + x] = (alpha << 24) | 0x00ffffff;
				}
			}

			pTexs[SetNum][i]->UnlockRect(0);  // �A�����b�N
			delete[] pMono;
		}
	

	vtxs[0] ={0.0f, -1.0f, 1.0f, 0.0f, 1.0f};
	vtxs[1] = {0.0f, 0.0f, 1.0f, 0.0f, 0.0f};
	vtxs[2] = { 1.0f, -1.0f, 1.0f,1.0f, 1.0f };
	vtxs[3] = { 1.0f,  0.0f, 1.0f,1.0f, 0.0f };
	
	return;
}
void FontDRAW(int ox, int oy,float Size,int SetNum)
{
	
	// �P�ʃt�H���g�|���S���쐬
	Vtx *p = 0;
	IDirect3DVertexBuffer9 *pVertexBuffer = 0;
	g_pD3DDev->CreateVertexBuffer(sizeof(vtxs), 0, 0, D3DPOOL_MANAGED, &pVertexBuffer, 0);
	pVertexBuffer->Lock(0, 0, (void**)&p, 0);
	memcpy(p, vtxs, sizeof(vtxs));
	pVertexBuffer->Unlock();

	// �e��s��Size
	D3DXMATRIX localScale;
	D3DXMatrixScaling(&localScale, (float)fontWidth, (float)fontHeight, 1.0f);
	D3DXMATRIX localOffset;
	D3DXMatrixTranslation(&localOffset, (float)gm[SetNum].gmptGlyphOrigin.x, (float)gm[SetNum].gmptGlyphOrigin.y, 0.0f);
	D3DXMATRIX localMat = (localScale * localOffset);
	
	D3DXMATRIX world;
	D3DXMATRIX worldOffset;
	//���]���Ƃ邩��Ή�
	D3DXMatrixTranslation(&worldOffset, (float)-ox - 0.5f, (float)-oy + 0.5f, 0.0f);
	world = localMat * worldOffset;
	D3DXMATRIX ortho;
	D3DXMatrixOrthoLH(&ortho, (float)screenW/Size, (float)screenH/ Size, 0.0f, 1000.0f);
	g_pD3DDev->SetTransform(D3DTS_PROJECTION, &ortho);

	
	// ���b�Z�[�W ���[�v
	{
		{
			// Direct3D�̏���

			// ���C�g�̓I�t��
			g_pD3DDev->SetRenderState(D3DRS_LIGHTING, FALSE);
			g_pD3DDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			g_pD3DDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			g_pD3DDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
//
			// ���u�����h�ݒ� 


			for (int i = 0; i < TexSize[SetNum]; i++)
			{
				D3DXMatrixTranslation(&worldOffset, (float)-ox + (300 * i) - 0.5f, (float)-oy + 0.5f, 0.0f);
				world = localMat * worldOffset;
				// �`��
				g_pD3DDev->SetTransform(D3DTS_WORLD, &world);
				g_pD3DDev->SetStreamSource(0, pVertexBuffer, 0, sizeof(Vtx));
				g_pD3DDev->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);

				//�ǂ����}���`�o�C�g�����Z�b�g��Shift_JIS �ۂ����Ƃ͔c���������A���Ă��̕����Z�b�g�A�ǂ����p���Ă��ׂ����A
				//�Ⴆ�Ζ��񓖊Y������� const wchar_t c[] = L"��������(ry �Ɣ�r���Ă����Ƃ����肪���邪�A���ׂ̖ʂ�����b�ɂȂ�Ȃ�
				//���̓_�A�P������Shift_JIS�R�[�h�ŔF�����Ă��̔ԍ������Ƃɂ����V�X�e���Ȃ�g�݂₷���H
				//��������Shift_JIS�R�[�h�͐F�X�Ɠ�A�I���^�l�C�g������
				//�\��1.�A�X�L�[�R�[�h�݂̂ɂ���:�Ԃ����Ⴏ��ԊȒP
				//�\��2.�ǂ����ɂ���Ђ炪�ȃJ�^�J�i�ꕔ�����ő���255�ȉ��A�����Ă�1000�͒����Ȃ��̂łP�����P�����ɕS���̔ԍ��U���Ă���ɊY���������l���Ԗڂ�text��`�悷��
				//�\��3.
				g_pD3DDev->SetTexture(0, pTexs[SetNum][i]);
				g_pD3DDev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

				
			}
			// �A���C�����`��
		}
	} //while (msg.message != WM_QUIT);


	return;
}

void FontFinalize()
{
	if (g_pD3DDev)
	{
		g_pD3DDev->Release();//����������Ńo�C�o�C����
		g_pD3DDev = NULL;//�g���܂킹��ɂ͎g���܂킹�邪�A�Ǘ����郂�W���[�����o����܂ł͂�߂Ƃ����ق�������
	}if (g_pD3D)
	{
		g_pD3D->Release();//����������Ńo�C�o�C����
		g_pD3D = NULL;//�g���܂킹��ɂ͎g���܂킹�邪�A�Ǘ����郂�W���[�����o����܂ł͂�߂Ƃ����ق�������
	}
}