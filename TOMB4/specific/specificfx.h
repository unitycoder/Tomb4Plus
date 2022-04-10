#pragma once
#include "../global/vars.h"

void inject_specificfx(bool replace);

void DrawTrainStrips();
void S_PrintShadow(short size, short* box, ITEM_INFO* item);
void S_DrawDrawSparks(SPARKS* sptr, long smallest_size, short* xyptr, long* zptr);
void DrawBikeSpeedo(long ux, long uy, long vel, long maxVel, long turboVel, long size, long unk);
void Draw2DSprite(long x, long y, long slot, long unused, long unused2);
void DrawJeepSpeedo(long ux, long uy, long vel, long maxVel, long turboVel, long size, long spriteSlot);
void DrawDebris();
void DoScreenFade();
void DrawPsxTile(long x_y, long height_width, long color, long u0, long u1);
void DrawFlash();
void S_DrawDarts(ITEM_INFO* item);
void ClipCheckPoint(D3DTLVERTEX* v, float x, float y, float z, short* clip);
void DrawFlatSky(ulong color, long zpos, long ypos, long drawtype);
void OutputSky();
void setXY4(D3DTLVERTEX* v, long x1, long y1, long x2, long y2, long x3, long y3, long x4, long y4, long z, short* clip);
void setXY3(D3DTLVERTEX* v, long x1, long y1, long x2, long y2, long x3, long y3, long z, short* clip);
void setXYZ4(D3DTLVERTEX* v, long x1, long y1, long z1, long x2, long y2, long z2, long x3, long y3, long z3, long x4, long y4, long z4, short* clip);
void setXYZ3(D3DTLVERTEX* v, long x1, long y1, long z1, long x2, long y2, long z2, long x3, long y3, long z3, short* clip);
void SetFade(long start, long end);
void DrawLaserSightSprite();
void DrawSprite(long x, long y, long slot, long col, long size, long z);
void ShowTitle();
void SetUpLensFlare(long x, long y, long z, GAME_VECTOR* lfobj);
void InitTarget_2();
void InitBinoculars();
void DrawBinoculars();
void DrawWraithTrail(ITEM_INFO* item);
void DrawDrips();

#define DrawTrainFloorStrip	( (void(__cdecl*)(long, long, TEXTURESTRUCT*, long)) 0x0048B480 )
#define DrawRope	( (void(__cdecl*)(ROPE_STRUCT*)) 0x00489540 )
#define S_DrawSparks	( (void(__cdecl*)()) 0x0043A1B0 )
#define DoUwEffect	( (void(__cdecl*)()) 0x0048A840 )
#define S_DrawSmokeSparks	( (void(__cdecl*)()) 0x00487260 )
#define S_DrawSplashes	( (void(__cdecl*)()) 0x00486430 )
#define DrawBubbles	( (void(__cdecl*)()) 0x004860D0 )
#define DrawBlood	( (void(__cdecl*)()) 0x0048A0C0 )
#define DrawShockwaves	( (void(__cdecl*)()) 0x0048CAA0 )
#define DrawLightning	( (void(__cdecl*)()) 0x0048D9B0 )
#define ClipLine	( (long(__cdecl*)(long&, long&, long, long&, long&, long, long, long, long, long)) 0x00488690 )
