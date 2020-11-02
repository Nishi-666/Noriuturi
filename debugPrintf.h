/*=================================
  DebugPrintfをつかって使おう(debugPrintf.h)
                             Author:Kai Yamaya 
                             Date  :2018/05/16
=================================
*/
#ifndef _DEBUG_PRINTF_H_
#define _DEBUG_PRINTF_H_
//x86からx64にするとメモリがポインタが２倍になり容量も食うが早くなる
#include <windows.h>
#include <stdio.h>

//debug用printf、VSの出力ウィンドウに出力される
inline void DebugPrintf(const char* pFormat, ...)
{
	//こんな風に書くとreleaseビルド時はビルドされない範囲を指定できる
#if defined(_DEBUG) || defined(DEBUG)//#if defined(_DEBUG) || defined(DEBUG),#endif,#endifがプリプロセッサという１つの命令分になってる
	va_list argp;
	char buf[256];//バッファ大きめに
	va_start(argp, pFormat);
	vsprintf_s(buf, 256, pFormat, argp);
	va_end(argp);
	OutputDebugStringA(buf);
#endif//_debug||debug
}
#endif // _DEBUG_PRINTF_H?
