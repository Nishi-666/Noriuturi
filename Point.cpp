/*///////////
	�|�C���g�֘A(Point.cpp)
							2020�N11��31��
							�R�J �J��

*/////////
#include "Point.h"

int StarPoint[3] = {};


void Point_initialize(void)
{

}
void Point_Update(void) 
{

}
void Point_Draw(D3DXMATRIX* pMtxWorld, int RBoxTextureId)
{

}
void Point_Finalize(void)
{


}
void SetTristar(int L10StarNum, int SetPoint)
{//���H3�́��̕K�v�|�C���g�����߂�ׂ̊֐�������SetTristar�Ȃ̂͂����Ƃ��āA�Ȃ�L10StarNum���Ă���int�^�Ȃ̂����āH�����[�J���҂̎�ƎO���@�̉��O�]
	StarPoint[L10StarNum] = SetPoint;
}