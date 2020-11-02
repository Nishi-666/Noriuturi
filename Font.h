#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>

#define screenW (640)
#define screenH (480)


void FontSet();
void drawLineW(IDirect3DDevice9* dev, float sx, float sy, float sz, float ex, float ey, float ez, DWORD color);

void drawRectW(IDirect3DDevice9* dev, float l, float t, float w, float h, DWORD color);
void drawTextMetrics(IDirect3DDevice9 *dev, TEXTMETRIC tm, GLYPHMETRICS gm, int ox, int oy);

void FontDRAW(int ox, int oy, float Size, int SetNum);
void FontDRAW(int FontNum);

void FontSet(const wchar_t Words[], int SetNum);
void FontFinalize();

IDirect3DTexture9 *ret(int Num);