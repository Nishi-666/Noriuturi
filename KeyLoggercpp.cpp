#include "KeyLoggerr.h"
#include "keyboard.h"
//�g��key��8�ȉ���char ,16�ȉ���short ,����ȏ��int��
static unsigned long g_CurrentData = 0;//���̓��͒l
static unsigned long g_PrevData = 0;//1�O�̓��͒l
static unsigned long g_TriggerData;
static unsigned long g_ReleaseData;

static int g_KeyLloggerMode = 0;//0:�m�[�}�� 1:�L�^ 2:�Đ�

static unsigned long *g_p_RecordCurrentData = NULL;
static int g_RecordPlayFrame;
static int g_RecordFrame = 0;
static Keyboard_Keys g_KKs[KL_MAX]=
{
	KK_W,
	KK_S,
	KK_A,
	KK_D,
	KK_LEFT,
	KK_RIGHT,
	KK_Q,
	KK_E,
	KK_SPACE,
	KK_N,
	KK_X,
	KK_R,
	KK_T,
	KK_Y,
	KK_SPACE,
	KK_UP,
	KK_DOWN
};
/*	KL_BEFORE,
	KL_REAR,
	KL_LEFT,
	KL_RIGHT,
	KL_LEFTROT,
	KL_RIGHTROT,
	KL_UP,
	KL_DOWN,
	KL_DECISION,
	KL_ATTACK = KL_DECISION,
	KL_BOAM,
	KL_CANCEL,
	KL_RESET,
	KL_MAX,*/

/*typedef struct KeyConv_tag
{
	Keyboard_Keys KK;
	KeyKind KK;
}KeyConv;
*/
void KeyLogger_initialize(void)
{
	g_CurrentData = g_PrevData = g_TriggerData= g_ReleaseData = 0 ; g_KeyLloggerMode = 0;
	g_p_RecordCurrentData = NULL;
	g_RecordFrame = 0;
	g_RecordPlayFrame=0;
}

//�I��
void KeyLogger_Finalize(void) 
{

	if (g_p_RecordCurrentData)
	{
		free(g_p_RecordCurrentData);
		g_p_RecordCurrentData = NULL;
	}
}

//�X�V
void KeyLogger_Update(void)
{
	 g_PrevData= g_CurrentData; 
	 if (g_KeyLloggerMode<=1)
	 {
		 g_CurrentData = 0;
		 for (int i = 0; i < KL_MAX; i++)
		 {
			 if (Keyboard_IsKeyDown(g_KKs[i]))
			 {
				 g_CurrentData |= 1u << i;
			 }
		 }
		 if (g_KeyLloggerMode==1)
		 {
			 g_p_RecordCurrentData[g_RecordPlayFrame++] = g_CurrentData;
		 }
	 }	 
	 else
	 {
		 if (g_RecordPlayFrame >= g_RecordFrame)
		 {
			 g_RecordPlayFrame = g_RecordFrame;
		 }
		 g_p_RecordCurrentData[g_RecordFrame++] = g_CurrentData;

	//		 if(g_RecordPlayFrame>�}�b�N�X��������L�^���~�߂ă��K�[���[�h���́[�܂��
	 }

	 g_TriggerData = (g_PrevData ^ g_CurrentData) & g_CurrentData;
	 g_ReleaseData = (g_PrevData ^ g_CurrentData) &g_PrevData;
}
bool KeyLogger_Press(KeyKind kl)//�����Ă���
{
	return g_CurrentData& (1u << (int)kl);
}
bool KeyLogger_Trigger(KeyKind kl)//�������u��
{
	return g_TriggerData & (1u << (int)kl);
}
bool KeyLogger_Release(KeyKind kl)//�������u��
{
	return g_ReleaseData & (1u << (int)kl);
}



void KeyLogger_RecordStart(int FrameMax)
{
	if (g_p_RecordCurrentData)
	{
		free(g_p_RecordCurrentData);
	}
	g_p_RecordCurrentData = (unsigned long*)malloc(FrameMax);
	g_KeyLloggerMode = 1;
	g_RecordFrame = 0;
}
void KeyLogger_RecordEND(void)
{
	FILE* fp = fopen("KeyLogger.bat","wb");
	fwrite(&g_RecordFrame, sizeof(g_RecordFrame), 1, fp);
	fwrite(&g_p_RecordCurrentData, sizeof(unsigned long),g_RecordFrame, fp);
	fclose(fp);
	g_KeyLloggerMode = 0;
}
void KeyLogger_RecordLoad(int FrameMax)
{
	FILE* fp = fopen("KeyLogger.bat", "rb");
	g_p_RecordCurrentData = (unsigned long*)malloc(FrameMax);
	fread(&g_RecordFrame, sizeof(g_RecordFrame), 1, fp);
	fread(&g_p_RecordCurrentData, sizeof(unsigned short), g_RecordFrame, fp);
	fclose(fp);

}
void KeyLogger_RecordPlay(void)
{
	g_RecordPlayFrame = 0;
	g_KeyLloggerMode = 2;

}
bool KeyLogger_IsRecordPlay(void)
{
	if (g_KeyLloggerMode == 2)
	{
		return true;
	}
	return false;
}