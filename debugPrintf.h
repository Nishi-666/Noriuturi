/*=================================
  DebugPrintf�������Ďg����(debugPrintf.h)
                             Author:Kai Yamaya 
                             Date  :2018/05/16
=================================
*/
#ifndef _DEBUG_PRINTF_H_
#define _DEBUG_PRINTF_H_
//x86����x64�ɂ���ƃ��������|�C���^���Q�{�ɂȂ�e�ʂ��H���������Ȃ�
#include <windows.h>
#include <stdio.h>

//debug�pprintf�AVS�̏o�̓E�B���h�E�ɏo�͂����
inline void DebugPrintf(const char* pFormat, ...)
{
	//����ȕ��ɏ�����release�r���h���̓r���h����Ȃ��͈͂��w��ł���
#if defined(_DEBUG) || defined(DEBUG)//#if defined(_DEBUG) || defined(DEBUG),#endif,#endif���v���v���Z�b�T�Ƃ����P�̖��ߕ��ɂȂ��Ă�
	va_list argp;
	char buf[256];//�o�b�t�@�傫�߂�
	va_start(argp, pFormat);
	vsprintf_s(buf, 256, pFormat, argp);
	va_end(argp);
	OutputDebugStringA(buf);
#endif//_debug||debug
}
#endif // _DEBUG_PRINTF_H?
