#include "../tomb4/pch.h"
#include "ahmet.h"
#include "collide.h"
#include "lara_states.h"
#include "delstuff.h"
#include "tomb4fx.h"
#include "../specific/function_stubs.h"
#include "sound.h"
#include "items.h"

short ScalesBounds[12] = { -1408, -640, 0, 0, -512, 512, -1820, 1820, -5460, 5460, -1820, 1820 };

void ScalesCollision(short item_number, ITEM_INFO* l, COLL_INFO* coll)
{
	ITEM_INFO* item;
	DRIP_STRUCT* drip;
	PHD_VECTOR pos;
	short roty;

	item = &items[item_number];

	if (TestBoundsCollide(item, l, 100))
	{
		if ((l->anim_number == ANIM_POURWATERSKIN || l->anim_number == ANIM_FILLSCALE) && item->current_anim_state == 1)
		{
			roty = item->pos.y_rot;
			item->pos.y_rot = (l->pos.y_rot + 0x2000) & 0xC000;
			ScalesBounds[0] = -1408;
			ScalesBounds[1] = -640;
			ScalesBounds[4] = -512;
			ScalesBounds[5] = 0;

			if (TestLaraPosition(ScalesBounds, item, l))
			{
				if (l->anim_number == ANIM_POURWATERSKIN)
				{
					l->anim_number = ANIM_FILLSCALE;
					l->frame_number = anims[ANIM_FILLSCALE].frame_base;
				}
				else if (l->frame_number == anims[ANIM_FILLSCALE].frame_base + 51)
					SoundEffect(SFX_POUR, &l->pos, SFX_DEFAULT);
				else if (l->frame_number == anims[ANIM_FILLSCALE].frame_base + 74)
				{
					AddActiveItem(item_number);
					item->status = ITEM_ACTIVE;

					if (l->item_flags[3] < item->trigger_flags)			//too little
						item->goal_anim_state = 4;
					else if (l->item_flags[3] == item->trigger_flags)	//nice
						item->goal_anim_state = 2;
					else												//too much
						item->goal_anim_state = 3;
				}
			}

			item->pos.y_rot = roty;
		}
		else
		{
			GlobalCollisionBounds[0] = 640;
			GlobalCollisionBounds[1] = 1280;
			GlobalCollisionBounds[2] = -1280;
			GlobalCollisionBounds[3] = 0;
			GlobalCollisionBounds[4] = -256;
			GlobalCollisionBounds[5] = 384;
			ItemPushLara(item, l, coll, 0, 2);
			GlobalCollisionBounds[0] = -256;
			GlobalCollisionBounds[1] = 256;
			ItemPushLara(item, l, coll, 0, 2);
			GlobalCollisionBounds[0] = -1280;
			GlobalCollisionBounds[1] = -640;
			ItemPushLara(item, l, coll, 0, 2);
		}
	}

	if (l->frame_number >= anims[ANIM_POURWATERSKIN].frame_base + 44 && l->frame_number <= anims[ANIM_POURWATERSKIN].frame_base + 72 ||
		l->frame_number >= anims[ANIM_FILLSCALE].frame_base + 51 && l->frame_number <= anims[ANIM_FILLSCALE].frame_base + 74)
	{
		pos.x = 0;
		pos.y = 0;
		pos.z = 0;
		GetLaraJointPos(&pos, 14);
		drip = &Drips[GetFreeDrip()];
		drip->x = pos.x;
		drip->y = pos.y;
		drip->z = pos.z;
		drip->On = 1;
		drip->R = (GetRandomControl() & 0xF) + 24;
		drip->G = (GetRandomControl() & 0xF) + 44;
		drip->B = (GetRandomControl() & 0xF) + 56;
		drip->Yvel = (GetRandomControl() & 0x1F) + 32;
		drip->Gravity = (GetRandomControl() & 0x1F) + 32;
		drip->Life = (GetRandomControl() & 0x1F) + 16;
		drip->RoomNumber = l->room_number;
	}
}

void inject_ahmet(bool replace)
{
	INJECT(0x00401AC0, ScalesCollision, replace);
}
