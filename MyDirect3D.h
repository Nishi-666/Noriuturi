//
//�g�����֌W���Ԃ�����

#include <d3d9.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "Config.h"
#ifdef  MY_DIRECT3D_H_
#define MY_DIRECT3D_H_


#endif //  MY_DIRECT3D_H_
//Direct3D9�̏������A���s����0�𓊉�
bool MyDirect3D_initialize(HWND hw);
//Direct3D9�̏I�������A���s����0�𓊉�
void MyDirect3D_Finalize(void);
//D3D�f�o�C�X�̎擾
LPDIRECT3DDEVICE9 MyDirect3D_GetDevice(void);
LPDIRECT3D9 MyDirect3D_GetLPDIRECT3D9(void);


//�ϐ��̓w�b�_�ɏ�������_��