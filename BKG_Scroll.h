#pragma once

#include <d3d9.h>
#include<d3d9.h>
#include "Config.h"
#ifdef  BKG_SCR_H_
#define BKG_SCR_H_
#endif
bool BKG_SCR_initialize(void);
void BKG_SCR_Update(void);
void BKG_SCR_Draw(void);
void BKG_SCR_Finalize(void);