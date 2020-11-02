
#include "camera.h"
#include "MyDirect3D.h"
#include <d3d9.h>
#include "KeyLoggerr.h"
#include "CharOBJGeter.h"
#include "Player.h"
float test = 0;
static D3DXVECTOR3 g_vFront(0.0f, -0.5f, 1.0f);
static D3DXVECTOR3 g_vRight(1.0f, 0.0f, 0.0f);
static D3DXVECTOR3 g_vUp(0.0f, 1.0f, 0.0f);
static D3DXVECTOR3 g_vAT(0.0f, 0.0f, 0.0f);
static D3DXVECTOR3 g_Position(0.0f, 1.0f, -5.0f);
static D3DXVECTOR3 g_vMoveingSPD(0.0f, 0.0f, 0.0f);
#define MOVEING_ACCEL (0.04f)
#define MOVEING_SPD_MAX (1.0f)
#define MOVEING_ATTE_NUATION_RATE (0.8f)
static float g_ROTSPD = .1f;



void CameraInit(void)
{
	 g_vFront= D3DXVECTOR3(0.0f, -0.5f, 1.0f);
	g_vRight= D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	
	//�O�����x�N�g���ƉE�����x�N�g���Ƃ��傩���ɂȂ������x�N�g�����Y�o
	//������x�N�g���͊O�ςŋ��߂邱�Ƃ��o����
	//Cross�Ƃ�������Ă���̂͊�{�I�ɊO��
	D3DXVec3Cross(&g_vUp, &g_vFront, &g_vRight);
	//�e�x�N�g���𐳋K��(����1�ɂ���)(���H���₷���悤��)
	D3DXVec3Normalize(&g_vFront, &g_vFront);
	D3DXVec3Normalize(&g_vRight, &g_vRight);
	D3DXVec3Normalize(&g_vUp, &g_vUp);


	g_vMoveingSPD = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}
void CameraUpDate(OBJData* Pj)
{
	
	g_Position = CharOBJGetPos(Pj, 0+ GetYChange());

	g_Position.z += -5.0f;
	g_Position.y += 1.0f;
	/*
	D3DXVECTOR3 dir(0.0f, 0.0f, 0.0f);
	if (KeyLogger_Press(KL_BEFORE))
	{
		D3DXVECTOR3 v = g_vFront;
		v.y = 0.0f;
		D3DXVec3Normalize(&v, &v);
		//g_Position+=v*.1f;
		//g_vMoveingSPD+= v*MOVEING_ACCEL;
		dir += v;
	}
	if (KeyLogger_Press(KL_REAR))
	{
		D3DXVECTOR3 v = g_vFront;
		v.y = 0.0f;
		D3DXVec3Normalize(&v, &v);
		//g_Position -= v * .1f;
		//g_vMoveingSPD += -v * MOVEING_ACCEL;
		dir += -v;
	}
	if (KeyLogger_Press(KL_UP))
	{
		D3DXVECTOR3 v(0.0f, g_vUp.y, 0.0f);
		D3DXVec3Normalize(&v, &v);
		dir += v;
		
		//g_Position += v * .1f;
		//g_vMoveingSPD += v * MOVEING_ACCEL;

	}
	if (KeyLogger_Press(KL_DOWN))
	{
		D3DXVECTOR3 v(0.0f, -g_vUp.y, 0.0f);
		D3DXVec3Normalize(&v, &v);
		dir += v;
		//	g_Position -= v * .1f;
		//g_vMoveingSPD -= v * MOVEING_ACCEL;

	}
	if (KeyLogger_Press(KL_LEFT))
	{
		dir += -g_vRight;
		//g_vMoveingSPD -= g_vRight * MOVEING_ACCEL;
	//	g_vMoveingSPD -= g_vRight * MOVEING_ACCEL;
		

	}
	if (KeyLogger_Press(KL_RIGHT))
	{
		dir += g_vRight;
		//g_Position += g_vRight * .1f;
	//	g_vMoveingSPD += g_vRight * MOVEING_ACCEL;
	}
	//D3DXVec3Transform�n�ɂ�
	//�ED3DXVec3Transform�@�@�@�@:���W�ϊ������4�����x�N�g���ŏo�́A��=1��ǉ����ĉ��Z
	//�ED3DXVec3TransformCoord  :���W�ϊ������3�����x�N�g���ŏo�́A��=1��ǉ����ĉ��Z�A���������폜
	//�����l�������Ȃ�����D3DXVec3TransformCoord���g���ׂ�
	//�ED3DXVec3TransformNormal  :���W�ϊ������3�����x�N�g���ŏo�́A����0��ǉ����ĉ��Z�Aw�������폜


	if (KeyLogger_Press(KL_UPRowling))
	{
		D3DXMATRIX mtxR;
		D3DXMatrixRotationX(&mtxR, -g_ROTSPD);
		D3DXVec3TransformNormal(&g_vFront, &g_vFront, &mtxR);
		D3DXVec3TransformNormal(&g_vRight, &g_vRight, &mtxR);
		D3DXVec3TransformNormal(&g_vUp, &g_vUp, &mtxR);

	}
	if (KeyLogger_Press(KL_DOWNRowling))
	{
		D3DXMATRIX mtxR;
		D3DXMatrixRotationX(&mtxR, g_ROTSPD);
		D3DXVec3TransformNormal(&g_vFront, &g_vFront, &mtxR);
		D3DXVec3TransformNormal(&g_vRight, &g_vRight, &mtxR);
		D3DXVec3TransformNormal(&g_vUp, &g_vUp, &mtxR);
	}


	if (KeyLogger_Press(KL_ROTUP))
	{
		D3DXMATRIX mtxR;
		D3DXMatrixRotationAxis(&mtxR, &g_vUp, -g_ROTSPD);
		D3DXVec3TransformNormal(&g_vFront, &g_vFront, &mtxR);
		D3DXVec3TransformNormal(&g_vUp, &g_vUp, &mtxR);
	}
	if (KeyLogger_Press(KL_ROTDOWN))
	{
		D3DXMATRIX mtxR;
		D3DXMatrixRotationAxis(&mtxR, &g_vUp, g_ROTSPD);
		D3DXVec3TransformNormal(&g_vFront, &g_vFront, &mtxR);
		D3DXVec3TransformNormal(&g_vUp, &g_vUp, &mtxR);
	}
	if (KeyLogger_Press(KL_LEFTROT) && KeyLogger_Press(KL_LALT))
	{
		D3DXVECTOR3 temp_at = g_Position + g_vFront * 2.5f;//2.5f�͋���

		D3DXMATRIX mtxR;
		D3DXMatrixRotationY(&mtxR, g_ROTSPD);
		D3DXVec3TransformNormal(&g_vFront, &g_vFront, &mtxR);
		D3DXVec3TransformNormal(&g_vRight, &g_vRight, &mtxR);
		D3DXVec3TransformNormal(&g_vUp, &g_vUp, &mtxR);

		g_Position = temp_at - g_vFront * 2.5f;
	}
	else if (KeyLogger_Press(KL_LEFTROT))
	{
		D3DXMATRIX mtxR;
		D3DXMatrixRotationY(&mtxR, -g_ROTSPD);
		D3DXVec3TransformNormal(&g_vFront, &g_vFront, &mtxR);
		D3DXVec3TransformNormal(&g_vRight, &g_vRight, &mtxR);
		D3DXVec3TransformNormal(&g_vUp, &g_vUp, &mtxR);

	}
	if (KeyLogger_Press(KL_RIGHTROT) && KeyLogger_Press(KL_LALT))
	{
		D3DXVECTOR3 temp_at = g_Position + g_vFront * 2.5f;//2.5f�͋���

		D3DXMATRIX mtxR;
		D3DXMatrixRotationY(&mtxR, -g_ROTSPD);
		D3DXVec3TransformNormal(&g_vFront, &g_vFront, &mtxR);
		D3DXVec3TransformNormal(&g_vRight, &g_vRight, &mtxR);
		D3DXVec3TransformNormal(&g_vUp, &g_vUp, &mtxR);

		g_Position = temp_at - g_vFront * 2.5f;
	}
	else if (KeyLogger_Press(KL_RIGHTROT))
	{
		D3DXMATRIX mtxR;
		D3DXMatrixRotationY(&mtxR, g_ROTSPD);
		D3DXVec3TransformNormal(&g_vFront, &g_vFront, &mtxR);
		D3DXVec3TransformNormal(&g_vRight, &g_vRight, &mtxR);
		D3DXVec3TransformNormal(&g_vUp, &g_vUp, &mtxR);
	}
	//�����x�̌v�Z
	D3DXVec3Normalize(&dir, &dir);
	g_vMoveingSPD += dir * MOVEING_ACCEL;

	//���x�}��
	if (D3DXVec3Length(&g_vMoveingSPD) > MOVEING_SPD_MAX)
	{
		D3DXVec3Normalize(&g_vMoveingSPD, &g_vMoveingSPD);

		g_vMoveingSPD *= MOVEING_SPD_MAX;
	}
	//�ړ�
	g_Position += g_vMoveingSPD;
	//���x����
	g_vMoveingSPD *= MOVEING_ACCEL;
	*/
}
void CameraSetting(void)
{
	test = 0.01f;
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	//�r���[�ϊ��s��̍쐬

	D3DXMATRIX mtxView;
	//�����_���Z�o����
	D3DXVECTOR3 At = g_Position + g_vFront;
	//(0.0f, 0.0f,0.0f);//�����_


	D3DXMatrixLookAtLH(&mtxView, &g_Position, &At, &g_vUp);
	//�f�o�C�X�Ƀr���[�ϊ��s���ݒ肷��
	pDevice->SetTransform(D3DTS_VIEW, &mtxView);
	//�v���W�F�N�V����(�p�[�X�y�N�e�B�u)�ϊ��s����쐬
	D3DXMATRIX MtxProj;
	float fovy = D3DXToRadian(60);
	float Aspect = (float)SCREEN_WHIDTH / SCREEN_HEIGHT;
	float Z_Near = 0.1f;
	float Z_Far = 100.0f;
	D3DXMatrixPerspectiveFovLH(&MtxProj, fovy, Aspect, Z_Near, Z_Far);
	//�f�o�C�X�Ƀv���W�F�N�V�����ϊ��s���ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &MtxProj);

}

const D3DXVECTOR3& camera_GetFlontVector(void)
{
	return g_vFront;//���[�J���ϐ��ł���Ă̓_��
}

const D3DXVECTOR3& camera_GetPos(void)
{
	return g_Position;//���[�J���ϐ��ł���Ă̓_��
}
