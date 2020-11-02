#pragma once
#include "Game_Judgement.h"
#include "Game_Barret.h"
#include "Game_Enemy.h"
#include "Game_Player.h"
#include "Game_Explosion.h"
#include "GameEnemy_Barret.h"
#include "Game_BOSS.h"
#include "Game.h"
#include "sound.h"
#include "Score.h"
//�Q�[���v���C���[�̏�����
void GameJudgement_initialize(void)
{

}

//�I��
void GameJudgement_Finalize(void)
{
}

//�X�V
void GameJudgement_Update(void)
{

	//�G�Ƒ����̓����蔻��
	//���݂����L��������ׂ�
	for (int BC = 0; BC < GameBarret_GetMax(); BC++)
	{

		for (int i = 0; i < 30; i++)
		{
			if (GameBarret_IsEnable(BC) && GameEnemy_IsEnable(i))
			{
				if (Collision_CircleAndCircleHie(&GameEnemy_GetCollision(i), &GameBarret_GetCollision(BC)))
				{
					GameBarret_Despawn(BC);
					GameEnemy_Despawn(i);

					D3DXVECTOR2 p = GetEneemy_thisPos(i);
					addScore(100);
					GameExplosion_Spawn(p.x, p.y);
					PlaySound(SOUND_LABEL_SE_EXPLOSION);
				}
			}
		}
	}

	for (int BC = 0; BC < GameBarret_GetMax(); BC++)
	{


		if (GameBarret_IsEnable(BC) && GameBoss_IsEnable())
		{
			if (Collision_CircleAndCircleHie(&GameBoss_GetCollision(), &GameBarret_GetCollision(BC)))
			{
				GameBarret_Despawn(BC);
				addScore(1000);
				GameBoss_Damage(1);

				D3DXVECTOR2 p = GetBoss_thisPos();
				GameExplosion_Spawn(p.x, p.y);

				PlaySound(SOUND_LABEL_SE_EXPLOSION);
			}
		}
	}
	
	for (int i = 0; i < 30; i++)
	{
		if (GamePlayer_IsEnable() && GameEnemy_IsEnable(i) && !GeTDeadCoolTimes())
		{
			if (Collision_CircleAndCircleHie(&GamePlayer_GetCollision(), &GameEnemy_GetCollision(i)))
			{
				GameEnemy_Despawn(i);
				//�����łǂ��ɂ�����	
				LifeMinus();
				PlaySound(SOUND_LABEL_SE_EXPLOSION);
			}
		}
	}
	for (int i = 0; i < 60; i++)
	{
		if (GamePlayer_IsEnable() && GameEnemyBarret_IsEnable(i) && !GeTDeadCoolTimes())
		{
			if (Collision_CircleAndCircleHie(&GamePlayer_GetCollision(), &GameEnemyBarret_GetCollision(i)))
			{
			//	GamePlayer_Despawn();
				GameEnemyBarret_Despawn(i);
				LifeMinus();
				PlaySound(SOUND_LABEL_SE_EXPLOSION);
			}
		}
	}
	//���݂����L���������瓖���蔻�肵��

	//�������Ă���e���G������������
}
