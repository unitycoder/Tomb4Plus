#pragma once
#include "../global/vars.h"

#define GetJointAbsPosition	( (void(__cdecl*)(ITEM_INFO*, PHD_VECTOR*, long)) 0x0045FF80 )
#define GetSpheres	( (long(__cdecl*)(ITEM_INFO*, SPHERE*, long)) 0x0045FC90 )
#define TestCollision	( (long(__cdecl*)(ITEM_INFO*, ITEM_INFO*)) 0x0045FB10 )
