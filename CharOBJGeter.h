#pragma once
#include "CharOBJ.h"
D3DXVECTOR3 CharOBJGetPos(OBJData* Pj,int Num);//“–ŠY”‚Ìpos‚ğŠm•Û
D3DXVECTOR3 CharOBJGetPos(OBJData* Pj, int Type,  int Num);//“–ŠYType‚ÌNum”Ô–Ú‚Ìpos‚ğŠm•Û
D3DXVECTOR3 CharOBJGetRot(OBJData* Pj, int Num);//“–ŠY”‚Ìpos‚ğŠm•Û
D3DXVECTOR3 CharOBJGetRot(OBJData* Pj, int Type,  int Num);//“–ŠYType‚ÌNum”Ô–Ú‚Ìpos‚ğŠm•Û
D3DXVECTOR3 CharOBJGetSize(OBJData* Pj, int Num);//“–ŠY”‚Ìpos‚ğŠm•Û
D3DXVECTOR3 CharOBJGetSize(OBJData* Pj, int Type, int Num);//“–ŠYType‚ÌNum”Ô–Ú‚Ìpos‚ğŠm•Û
int CharOBJGetType(OBJData* Pj,int x,int y);//“–ŠYType‚ÌNum”Ô–Ú‚Ìpos‚ğŠm•Û
//
//int  CharOBJGetType(OBJData* Pj, int Num);//“–ŠY”‚ÌType‚ğŠm•Û