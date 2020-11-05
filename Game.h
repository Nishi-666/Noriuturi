
#include <d3d9.h>
#include<d3d9.h>
#include "Config.h"
#ifdef  GAME_H_
#define GAME_H_
#endif
bool Game_initialize(bool N98);
void Game_Update(void);
void Game_Draw(void);
void Game_Finalize(void);
void StateChange(int CData);
void LifeMinus();
void StageAdd();
void Game_Reset(void);
void StageNex(void);
int GetStage();
void StateChange(int st);