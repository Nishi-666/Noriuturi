#pragma once
#ifndef KEYLOGGER_H
#define KEYLOGGER_H

typedef enum KeyKind_tag
{//�����ɃQ�[���Ŏg���L�[�{�[�h�S�ĕ`��//�����ł̓A�i���O�p�b�h�Ȃǂ͕̂s��
	KL_BEFORE,
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
	KL_ROTUP,
	KL_ROTDOWN,
	KL_LALT,
	KL_UPRowling,
	KL_DOWNRowling,
	KL_MAX,
}KeyKind;

void KeyLogger_initialize(void);

//�I��
void KeyLogger_Finalize(void);

//�X�V
void KeyLogger_Update(void);
bool KeyLogger_Press(KeyKind kl);//�����Ă���
bool KeyLogger_Trigger(KeyKind kl);//�������u��
bool KeyLogger_Release(KeyKind kl);//�������u��

void KeyLogger_RecordStart(int FrameMax);
void KeyLogger_RecordEND(void);
void KeyLogger_RecordLoad(int FrameMax);
void KeyLogger_RecordPlay(void);
bool KeyLogger_IsRecordPlay(void);
#endif // KEYLOGGER_H
