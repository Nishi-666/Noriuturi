#pragma once
#ifndef KEYLOGGER_H
#define KEYLOGGER_H

typedef enum KeyKind_tag
{//ここにゲームで使うキーボード全て描け//ここではアナログパッドなどのは不可
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

//終了
void KeyLogger_Finalize(void);

//更新
void KeyLogger_Update(void);
bool KeyLogger_Press(KeyKind kl);//押してたら
bool KeyLogger_Trigger(KeyKind kl);//押した瞬間
bool KeyLogger_Release(KeyKind kl);//離した瞬間

void KeyLogger_RecordStart(int FrameMax);
void KeyLogger_RecordEND(void);
void KeyLogger_RecordLoad(int FrameMax);
void KeyLogger_RecordPlay(void);
bool KeyLogger_IsRecordPlay(void);
#endif // KEYLOGGER_H
