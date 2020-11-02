


#define _CRT_SECURE_NO_WARNINGS

// 改・高速フォント表示サンプルプログラム

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

//TCHAR gName[100] = _T("改・高速フォント表示サンプルプログラム");

LPDIRECT3DDEVICE9 g_pD3DDev;
LPDIRECT3D9 g_pD3D;

IDirect3DTexture9 *pTexs[5][255] = {};
int TexSize[5] = {};

UINT code[5][51] = {};
int fontWidth;
int fontHeight;
TEXTMETRIC tm;///使用文字フォントの大きさ・幅・高さ・太さなどをもつ構造体です：
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
	// フォントビットマップ取得
	 wchar_t c[] = L"_____________________________________________";
	 
	 TexSize[SetNum] = wcslen(Words);
	wcsncpy(c, Words, TexSize[SetNum]);
	// wcscpy_s(c, 60, Words);
//	wcscpy(c, Words);
	
	int i = 0;
	//でけた
		for (int i = 0; i < TexSize[SetNum]; i++)
		{
			// フォントの生成
			int fontSize = 260;
			int fontWeight = 500;
			LOGFONT lf = { fontSize, 0, 0, 0, fontWeight, 0, 0, 0, SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("ＭＳ Ｐ明朝") };
			//      LOGFONT lf = {fontSize, 0, 0, 0, fontWeight, 0, 0, 0, SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("ＭＳ Ｐゴシック")};
			HFONT hFont = CreateFontIndirect(&lf);
			if (hFont == NULL) {
				g_pD3DDev->Release(); g_pD3D->Release();
				return;
			}
			// デバイスにフォントを持たせないとGetGlyphOutline関数はエラーとなる
			HDC hdc = GetDC(NULL);
			HFONT oldFont = (HFONT)SelectObject(hdc, hFont);


			GetTextMetrics(hdc, &tm);
			code[SetNum][i] = (UINT)c[i];

			const int gradFlag = GGO_GRAY4_BITMAP; // GGO_GRAY2_BITMAP or GGO_GRAY4_BITMAP or GGO_GRAY8_BITMAP
			int grad = 0; // 階調の最大値
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

			// デバイスコンテキストとフォントハンドルはもういらないので解放
			SelectObject(hdc, oldFont);
			ReleaseDC(NULL, hdc);
			// テクスチャ作成
			//IDirect3DTexture9 *pTex = 0;
			DWORD alpha;

			fontWidth = (gm[SetNum].gmBlackBoxX + 3) / 4 * 4;
			fontHeight = gm[SetNum].gmBlackBoxY;
			g_pD3DDev->CreateTexture(fontWidth, fontHeight, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &pTexs[SetNum][i], NULL);

			// テクスチャにフォントビットマップ情報を書き込み
			D3DLOCKED_RECT lockedRect;
			pTexs[SetNum][i]->LockRect(0, &lockedRect, NULL, 0);  // ロック
			DWORD *pTexBuf = (DWORD*)lockedRect.pBits;   // テクスチャメモリへのポインタ


			//ここで書き込んでる　//alphaに文字を１ドットずつカラーコードらしきもので入れたのちにこれをやっている？
			for (int y = 0; y < fontHeight; y++) {
				for (int x = 0; x < fontWidth; x++) {
					alpha = pMono[y * fontWidth + x] * 255 / grad;
					pTexBuf[y * fontWidth + x] = (alpha << 24) | 0x00ffffff;
				}
			}

			pTexs[SetNum][i]->UnlockRect(0);  // アンロック
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
	
	// 単位フォントポリゴン作成
	Vtx *p = 0;
	IDirect3DVertexBuffer9 *pVertexBuffer = 0;
	g_pD3DDev->CreateVertexBuffer(sizeof(vtxs), 0, 0, D3DPOOL_MANAGED, &pVertexBuffer, 0);
	pVertexBuffer->Lock(0, 0, (void**)&p, 0);
	memcpy(p, vtxs, sizeof(vtxs));
	pVertexBuffer->Unlock();

	// 各種行列Size
	D3DXMATRIX localScale;
	D3DXMatrixScaling(&localScale, (float)fontWidth, (float)fontHeight, 1.0f);
	D3DXMATRIX localOffset;
	D3DXMatrixTranslation(&localOffset, (float)gm[SetNum].gmptGlyphOrigin.x, (float)gm[SetNum].gmptGlyphOrigin.y, 0.0f);
	D3DXMATRIX localMat = (localScale * localOffset);
	
	D3DXMATRIX world;
	D3DXMATRIX worldOffset;
	//反転しとるから対応
	D3DXMatrixTranslation(&worldOffset, (float)-ox - 0.5f, (float)-oy + 0.5f, 0.0f);
	world = localMat * worldOffset;
	D3DXMATRIX ortho;
	D3DXMatrixOrthoLH(&ortho, (float)screenW/Size, (float)screenH/ Size, 0.0f, 1000.0f);
	g_pD3DDev->SetTransform(D3DTS_PROJECTION, &ortho);

	
	// メッセージ ループ
	{
		{
			// Direct3Dの処理

			// ライトはオフで
			g_pD3DDev->SetRenderState(D3DRS_LIGHTING, FALSE);
			g_pD3DDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			g_pD3DDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			g_pD3DDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
//
			// αブレンド設定 


			for (int i = 0; i < TexSize[SetNum]; i++)
			{
				D3DXMatrixTranslation(&worldOffset, (float)-ox + (300 * i) - 0.5f, (float)-oy + 0.5f, 0.0f);
				world = localMat * worldOffset;
				// 描画
				g_pD3DDev->SetTransform(D3DTS_WORLD, &world);
				g_pD3DDev->SetStreamSource(0, pVertexBuffer, 0, sizeof(Vtx));
				g_pD3DDev->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);

				//どうやらマルチバイト文字セットはShift_JIS ぽいことは把握したが、さてこの文字セット、どう活用してくべきか、
				//例えば毎回当該文字列を const wchar_t c[] = L"あいうえ(ry と比較しておくという手があるが、負荷の面からも話にならない
				//その点、１文字をShift_JISコードで認識してその番号をもとにしたシステムなら組みやすい？
				//だがそのShift_JISコードは色々と謎、オルタネイトを検討
				//可能性1.アスキーコードのみにする:ぶっちゃけ一番簡単
				//可能性2.どっちにしろひらがなカタカナ一部漢字で多分255以下、多くても1000は超えないので１文字１文字に百桁の番号振ってそれに該当した数値ｘ番目のtextを描画する
				//可能性3.
				g_pD3DDev->SetTexture(0, pTexs[SetNum][i]);
				g_pD3DDev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

				
			}
			// アライン情報描画
		}
	} //while (msg.message != WM_QUIT);


	return;
}

void FontFinalize()
{
	if (g_pD3DDev)
	{
		g_pD3DDev->Release();//ここあたりでバイバイする
		g_pD3DDev = NULL;//使いまわせるには使いまわせるが、管理するモジュールが出来るまではやめといたほうがいい
	}if (g_pD3D)
	{
		g_pD3D->Release();//ここあたりでバイバイする
		g_pD3D = NULL;//使いまわせるには使いまわせるが、管理するモジュールが出来るまではやめといたほうがいい
	}
}