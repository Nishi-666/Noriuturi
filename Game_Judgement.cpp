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
//ゲームプレイヤーの初期化
void GameJudgement_initialize(void)
{

}

//終了
void GameJudgement_Finalize(void)
{
}

//更新
void GameJudgement_Update(void)
{

	//敵と多摩の当たり判定
	//お互いが有効化しらべる
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
				//ここでどうにかする	
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
	//お互いが有効だったら当たり判定して

	//当たってたら弾も敵も無効化する
}
