/*============================================================

�f�o�b�O�t�H���g���W���[��[Debug_Font.h]                           Author:Kai Yamaya
												   Date:2020/7/13
-------------------------------------------------------

==============================================================
*/#ifndef DEBUG_FONT_H
#define DEBUG_FONT_H
//�f�o�b�O�t�H���g���W���[���̏�����
void DebugFont_initialize(void);
//�f�o�b�O�t�H���g���W���[���̏I������
void DebugFont_finalize(void);
//�f�o�b�O�t�H���g�̕\��
//����:pString:�f�o�b�O������ւ̃|�C���^
//Dx/Dy�f�o�b�O���W�ւ̕`����W
void DebugFont_Draw(float Dx, float Dy, const char* pString, int FontNum);
#endif//DEBUG_FONT_H
void DebugFont_Draw(float Dx, float Dy, const char* pString, int FontNum, float FontSize);