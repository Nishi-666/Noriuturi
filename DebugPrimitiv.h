#pragma once
#ifndef DEBUG_PRIMITIV_H_
#define DEBUG_PRIMITIV_H_

void DebugPrimitiv_Init(void);
void DebugPrimitiv_Finalize(void);
void DebugPrimitiv_BatchBegin(void);
void DebugPrimitiv_BatchDrawCircle(float x,float y,float radius);
void DebugPrimitiv_BatchRun(void);

#endif//#ifdef DEBUG_PRIMITIV_H_
