#pragma once
#include "../global/vars.h"

void inject_box(bool replace);

void CreatureDie(short item_number, long explode);
void InitialiseCreature(short item_number);
long CreatureActive(short item_number);
void CreatureAIInfo(ITEM_INFO* item, AI_INFO* info);
long SearchLOT(LOT_INFO* LOT, long expansion);
long UpdateLOT(LOT_INFO* LOT, long expansion);
void TargetBox(LOT_INFO* LOT, short box_number);
long EscapeBox(ITEM_INFO* item, ITEM_INFO* enemy, short box_number);
long ValidBox(ITEM_INFO* item, short zone_number, short box_number);
long StalkBox(ITEM_INFO* item, ITEM_INFO* enemy, short box_number);
target_type CalculateTarget(PHD_VECTOR* target, ITEM_INFO* item, LOT_INFO* LOT);
void CreatureMood(ITEM_INFO* item, AI_INFO* info, long violent);
void GetCreatureMood(ITEM_INFO* item, AI_INFO* info, long violent);
long CreatureCreature(short item_number);
long BadFloor(long x, long y, long z, long box_height, long next_height, short room_number, LOT_INFO* LOT);
long CreatureAnimation(short item_number, short angle, short tilt);
short CreatureTurn(ITEM_INFO* item, short maximum_turn);
void CreatureTilt(ITEM_INFO* item, short angle);
void CreatureJoint(ITEM_INFO* item, short joint, short required);
void CreatureFloat(short item_number);
void CreatureUnderwater(ITEM_INFO* item, long depth);
short CreatureEffect(ITEM_INFO* item, BITE_INFO* bite, short(*generate)(long x, long y, long z, short speed, short yrot, short room_number));
short CreatureEffectT(ITEM_INFO* item, BITE_INFO* bite, short damage, short angle,
	short(*generate)(long x, long y, long z, short damage, short angle, short room_number));
long CreatureVault(short item_number, short angle, long vault, long shift);
void CreatureKill(ITEM_INFO* item, short kill_anim, short kill_state, short lara_anim);
void AlertAllGuards(short item_number);
void AlertNearbyGuards(ITEM_INFO* item);
short AIGuard(CREATURE_INFO* creature);
void FindAITargetObject(CREATURE_INFO* creature, short obj_num);

#define GetAITarget	( (void(__cdecl*)(CREATURE_INFO*)) 0x00442720 )
#define CreatureYRot	( (void(__cdecl*)(PHD_3DPOS*, short, short)) 0x00442D30 )
#define MoveCreature3DPos	( (long(__cdecl*)(PHD_3DPOS*, PHD_3DPOS*, long, short, short)) 0x00442D70 )
