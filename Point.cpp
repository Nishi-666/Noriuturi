/*///////////
	ポイント関連(Point.cpp)
							2020年11月31日
							山谷 開偉

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
{//え？3つの★の必要ポイントを決める為の関数だからSetTristarなのはいいとして、なぜL10StarNumっていうint型なのかって？そりゃー開発者の趣味と三発機の怨念ゾ
	StarPoint[L10StarNum] = SetPoint;
}