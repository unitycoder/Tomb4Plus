#include "../tomb4/pch.h"
#include "gameflow.h"
#include "moveblok.h"
#include "control.h"
#include "collide.h"
#include "objects.h"
#include "lara_states.h"
#include "sound.h"
#include "delstuff.h"
#include "items.h"
#include "draw.h"
#include "sphere.h"
#include "deltapak.h"
#include "../specific/function_stubs.h"
#include "tomb4fx.h"
#include "../specific/3dmath.h"
#include "../specific/output.h"
#include "box.h"
#include "../specific/input.h"
#include "lara.h"

#include "trng/trng_extra_state.h"

#include "../tomb4/mod_config.h"
#include "../specific/file.h"

static short MovingBlockBounds[12] = { 0, 0, -256, 0, 0, 0, -1820, 1820, -5460, 5460, -1820, 1820 };

static PHD_VECTOR MovingBlockPos = { 0, 0, 0 };

static void ClearMovableBlockSplitters(long x, long y, long z, short room_number)
{
	FLOOR_INFO* floor;
	short room_num, height;

	floor = GetFloor(x, y, z, &room_number);
	boxes[floor->box].overlap_index = ~0x4000;
	height = boxes[floor->box].height;
	room_num = room_number;
	floor = GetFloor(x + 1024, y, z, &room_number);

	if (floor->box != 0x7FF)
	{
		if (boxes[floor->box].height == height && boxes[floor->box].overlap_index & 0x8000 && boxes[floor->box].overlap_index & 0x4000)
			ClearMovableBlockSplitters(x + 1024, y, z, room_number);
	}

	room_number = room_num;
	floor = GetFloor(x - 1024, y, z, &room_number);

	if (floor->box != 0x7FF)
	{
		if (boxes[floor->box].height == height && boxes[floor->box].overlap_index & 0x8000 && boxes[floor->box].overlap_index & 0x4000)
			ClearMovableBlockSplitters(x - 1024, y, z, room_number);
	}

	room_number = room_num;
	floor = GetFloor(x, y, z + 1024, &room_number);

	if (floor->box != 0x7FF)
	{
		if (boxes[floor->box].height == height && boxes[floor->box].overlap_index & 0x8000 && boxes[floor->box].overlap_index & 0x4000)
			ClearMovableBlockSplitters(x, y, z + 1024, room_number);
	}

	room_number = room_num;
	floor = GetFloor(x, y, z - 1024, &room_number);

	if (floor->box != 0x7FF)
	{
		if (boxes[floor->box].height == height && boxes[floor->box].overlap_index & 0x8000 && boxes[floor->box].overlap_index & 0x4000)
			ClearMovableBlockSplitters(x, y, z - 1024, room_number);
	}
}

void InitialiseMovingBlock(short item_number)
{
	ITEM_INFO* item;

	item = &items[item_number];
	ClearMovableBlockSplitters(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, item->room_number);

	MOD_GLOBAL_INFO *global_info = get_game_mod_global_info();
	MOD_LEVEL_MISC_INFO *misc_info = get_game_mod_level_misc_info(gfCurrentLevel);
	// TRNG
	int climbable_block_height = 0;
	if (global_info->trng_pushable_extended_ocb && item->trigger_flags & 0x40) {
		climbable_block_height = item->trigger_flags & 0xf;
	// TREP
	} else if (misc_info->enable_standing_pushables) {
		climbable_block_height = (item->trigger_flags & 0xf00) >> 8;
	}

	if (climbable_block_height) {
		if (item->status == ITEM_INACTIVE) {
			AlterFloorHeight(item, -climbable_block_height * 256);
		}
	}
}

static long TestBlockPush(ITEM_INFO* item, long height, ushort quadrant, bool can_push_over_ledges)
{
	ITEM_INFO** itemlist;
	ITEM_INFO* collided;
	FLOOR_INFO* floor;
	ROOM_INFO* r;
	long x, y, z, rx, rz;
	short room_number;

	// TRNG
	MOD_GLOBAL_INFO *global_info = get_game_mod_global_info();

	if (global_info->trng_pushable_extended_ocb && item->trigger_flags & 0x40) {
		if (item->trigger_flags & 0x100) { // TRNG: Pushing disabled
			return 0;
		}

		if (quadrant == EAST || quadrant == WEST) {
			if (item->trigger_flags & 0x400) { // TRNG: East and West direction disabled
				return 0;
			}
		} else if (quadrant == NORTH || quadrant == SOUTH) {
			if (item->trigger_flags & 0x200) { // TRNG: North and South direction disabled
				return 0;
			}
		}
	}

	x = item->pos.x_pos;
	y = item->pos.y_pos;
	z = item->pos.z_pos;
	itemlist = (ITEM_INFO**)&tsv_buffer[0];

	switch (quadrant)
	{
	case NORTH:
		z += 1024;
		break;

	case EAST:
		x += 1024;
		break;

	case SOUTH:
		z -= 1024;
		break;

	case WEST:
		x -= 1024;
		break;
	}

	room_number = item->room_number;
	floor = GetFloor(x, y - 256, z, &room_number);
	r = &room[room_number];
	rx = (x - r->x) >> 10;
	rz = (z - r->z) >> 10;

	if (r->floor[rx * r->x_size + rz].stopper)
		return 0;

	if (can_push_over_ledges) {
		if (GetHeight(floor, x, y - 256, z) < y)
			return 0;
	} else  {
		if (GetHeight(floor, x, y - 256, z) != y)
			return 0;
	}

	GetHeight(floor, x, y, z);

	if (height_type != WALL)
		return 0;

	y -= height - 100;
	floor = GetFloor(x, y, z, &room_number);

	if (GetCeiling(floor, x, y, z) > y)
		return 0;

	rx = item->pos.x_pos;
	rz = item->pos.z_pos;
	item->pos.x_pos = x;
	item->pos.z_pos = z;
	GetCollidedObjects(item, 256, 1, itemlist, 0, 0);
	item->pos.x_pos = rx;
	item->pos.z_pos = rz;

	if (itemlist[0])
	{
		for (int i = 0; itemlist[0] != 0; i++, itemlist++)
		{
			collided = itemlist[0];

			if (collided->object_number == TWOBLOCK_PLATFORM || collided->object_number == HAMMER)
				return 1;
		}

		return 0;
	}

	return 1;
}

static long TestBlockPull(ITEM_INFO* item, long height, ushort quadrant)
{
	ITEM_INFO** itemlist;
	ITEM_INFO* collided;
	FLOOR_INFO* floor;
	ROOM_INFO* r;
	long x, y, z, destx, destz, rx, rz, ignore;
	short room_number;

	// TRNG
	MOD_GLOBAL_INFO *global_info = get_game_mod_global_info();

	if (global_info->trng_pushable_extended_ocb && item->trigger_flags & 0x40) {
		if (item->trigger_flags & 0x80) { // TRNG: Pulling disabled
			return 0;
		}

		if (quadrant == EAST || quadrant == WEST) {
			if (item->trigger_flags & 0x400) { // TRNG: East and West direction disabled
				return 0;
			}
		} else if (quadrant == NORTH || quadrant == SOUTH) {
			if (item->trigger_flags & 0x200) { // TRNG: North and South direction disabled
				return 0;
			}
		}
	}

	itemlist = (ITEM_INFO**)&tsv_buffer[0];
	destx = 0;
	destz = 0;

	switch (quadrant)
	{
	case NORTH:
		destz = -1024;
		break;

	case EAST:
		destx = -1024;
		break;

	case SOUTH:
		destz = 1024;
		break;

	case WEST:
		destx = 1024;
		break;
	}

	x = item->pos.x_pos + destx;
	y = item->pos.y_pos;
	z = item->pos.z_pos + destz;
	room_number = item->room_number;
	floor = GetFloor(x, y - 256, z, &room_number);
	r = &room[room_number];
	rx = (x - r->x) >> 10;
	rz = (z - r->z) >> 10;

	if (r->floor[rx * r->x_size + rz].stopper)
		return 0;

	if (GetHeight(floor, x, y - 256, z) != y)
		return 0;

	floor = GetFloor(x, y - height, z, &room_number);

	if (floor->ceiling << 8 > y - height)
		return 0;

	rx = item->pos.x_pos;
	rz = item->pos.z_pos;
	item->pos.x_pos = x;
	item->pos.z_pos = z;
	GetCollidedObjects(item, 256, 1, itemlist, 0, 0);
	item->pos.x_pos = rx;
	item->pos.z_pos = rz;

	if (itemlist[0])
	{
		ignore = 0;

		for (int i = 0; itemlist[0] != 0; i++, itemlist++)
		{
			collided = itemlist[0];

			if (collided->object_number == TWOBLOCK_PLATFORM || collided->object_number == HAMMER)
			{
				ignore = 1;
				break;
			}
		}

		if (!ignore)
			return 0;
	}

	x += destx;
	z += destz;
	room_number = item->room_number;
	floor = GetFloor(x, y - 256, z, &room_number);

	if (GetHeight(floor, x, y - 256, z) != y)
		return 0;

	floor = GetFloor(x, y - 762, z, &room_number);

	if (floor->ceiling << 8 > y - 762)
		return 0;

	x = lara_item->pos.x_pos + destx;
	y = lara_item->pos.y_pos;
	z = lara_item->pos.z_pos + destz;
	room_number = lara_item->room_number;
	GetFloor(x, y, z, &room_number);
	r = &room[room_number];
	rx = (x - r->x) >> 10;
	rz = (z - r->z) >> 10;

	if (r->floor[rx * r->x_size + rz].stopper)
		return 0;

	rx = lara_item->pos.x_pos;
	rz = lara_item->pos.z_pos;
	lara_item->pos.x_pos = x;
	lara_item->pos.z_pos = z;
	GetCollidedObjects(lara_item, 256, 1, itemlist, 0, 0);
	lara_item->pos.x_pos = rx;
	lara_item->pos.z_pos = rz;

	if (itemlist[0])
	{
		for (int i = 0; itemlist[0] != 0; i++, itemlist++)
		{
			collided = itemlist[0];

			if (collided == item || collided->object_number == TWOBLOCK_PLATFORM || collided->object_number == HAMMER)
				return 1;
		}

		return 0;
	}

	return 1;
}

void MovableBlock(short item_number)
{
	ITEM_INFO* item;
	PHD_VECTOR pos;
	long offset;
	ushort quadrant;
	short frame, base;
	static char sfx = 0;

	item = &items[item_number];

	MOD_GLOBAL_INFO *global_info = get_game_mod_global_info();
	MOD_LEVEL_MISC_INFO *misc_info = get_game_mod_level_misc_info(gfCurrentLevel);
	// TRNG
	int climbable_block_height = 0;
	if (global_info->trng_pushable_extended_ocb && item->trigger_flags & 0x40) {
		climbable_block_height = item->trigger_flags & 0xf;
	// TREP
	}
	else if (misc_info->enable_standing_pushables)
	{
		climbable_block_height = (item->trigger_flags & 0xf00) >> 8;
	}

	// TRNG
	if (global_info->trng_pushables_have_gravity) {
		short room_number = item->room_number;
		FLOOR_INFO *floor_info = GetFloor(item->pos.x_pos, item->pos.y_pos - 128, item->pos.z_pos, &room_number);
		int height = GetHeight(floor_info, item->pos.x_pos, item->pos.y_pos - 128, item->pos.z_pos);

		if (item->pos.y_pos < height)
		{
			item->gravity_status = 1;
			ApplyItemGravity(item);

			floor_info = GetFloor(item->pos.x_pos, item->pos.y_pos - 128, item->pos.z_pos, &room_number);
			height = GetHeight(floor_info, item->pos.x_pos, item->pos.y_pos - 128, item->pos.z_pos);
			if (item->room_number != room_number)
				ItemNewRoom(item_number, room_number);
		}
		else if (item->gravity_status)
		{
			item->gravity_status = 0;
			item->pos.y_pos = height;
			SoundEffect(SFX_BOULDER_FALL, &item->pos, SFX_DEFAULT);

			// If the object has landed and Lara is not performing animations, complete the sequence.
			if (lara_item->anim_number != ANIM_PULL && lara_item->anim_number != ANIM_PUSH && lara_item->anim_number != 417 && lara_item->anim_number != 418)
			{
				floor_info = GetFloor(item->pos.x_pos, item->pos.y_pos - 128, item->pos.z_pos, &room_number);
				height = GetHeight(floor_info, item->pos.x_pos, item->pos.y_pos - 128, item->pos.z_pos);

				TestTriggers(trigger_data, 1, item->flags & IFL_CODEBITS, trigger_index_room, trigger_index_floor);
				RemoveActiveItem(item_number);
				item->status = ITEM_INACTIVE;

				if (climbable_block_height > 0)
				{
					if (item->room_number != room_number)
						ItemNewRoom(item_number, room_number);

					AlterFloorHeight(item, -climbable_block_height * 256);
				}
			}
		}
	}

	pos.x = 0;
	pos.y = 0;
	pos.z = 0;
	quadrant = ushort(lara_item->pos.y_rot + 0x2000) / 0x4000;

	switch (lara_item->anim_number)
	{
	case ANIM_PUSH:
		frame = lara_item->frame_number;
		base = anims[ANIM_PUSH].frame_base;

		if ((frame < base + 30 || frame > base + 67) && (frame < base + 78 || frame > base + 125) && (frame < base + 140 || frame > base + 160))
		{
			if (sfx)
			{
				SoundEffect(SFX_PUSH_BLOCK_END, &item->pos, SFX_ALWAYS);
				sfx = 0;
			}
		}
		else
		{
			SoundEffect(SFX_PUSHABLE_SOUND, &item->pos, SFX_ALWAYS);
			sfx = 1;
		}

		GetLaraJointPos(&pos, 14);

		switch (quadrant)
		{
		case NORTH:
			offset = pos.z + *(long*)&item->item_flags[2] - *(long*)&lara_item->item_flags[2];

			if (abs(item->pos.z_pos - offset) < 512 && item->pos.z_pos < offset)
				item->pos.z_pos = offset;

			break;

		case EAST:
			offset = pos.x + *(long*)item->item_flags - *(long*)lara_item->item_flags;

			if (abs(item->pos.x_pos - offset) < 512 && item->pos.x_pos < offset)
				item->pos.x_pos = offset;

			break;

		case SOUTH:
			offset = pos.z + *(long*)&item->item_flags[2] - *(long*)&lara_item->item_flags[2];

			if (abs(item->pos.z_pos - offset) < 512 && item->pos.z_pos > offset)
				item->pos.z_pos = offset;

			break;

		case WEST:
			offset = pos.x + *(long*)item->item_flags - *(long*)lara_item->item_flags;

			if (abs(item->pos.x_pos - offset) < 512 && item->pos.x_pos > offset)
				item->pos.x_pos = offset;

			break;
		}


		if (lara_item->frame_number == anims[lara_item->anim_number].frame_end - 1)
		{
			// T4Plus: Update Room
			UpdateItemRoom(item_number, -256);

			if (input & IN_ACTION)
			{
				// TRNG
				MOD_GLOBAL_INFO *global_info = get_game_mod_global_info();
				bool can_push_over_ledges = false;
				if (global_info->trng_pushable_extended_ocb && item->trigger_flags & 0x40) {
					if (!(item->trigger_flags & 0x100)) { // TRNG: Pushing disabled
						can_push_over_ledges = item->trigger_flags & 0x20;
					}
				}

				if (!TestBlockPush(item, 1024, quadrant, can_push_over_ledges))
					lara_item->goal_anim_state = 2;
			}
			else
				lara_item->goal_anim_state = 2;
		}

		break;

	case ANIM_PULL:
		frame = lara_item->frame_number;
		base = anims[ANIM_PULL].frame_base;

		if ((frame < base + 40 || frame > base + 122) && (frame < base + 130 || frame > base + 170))
		{
			if (sfx)
			{
				SoundEffect(SFX_PUSH_BLOCK_END, &item->pos, SFX_ALWAYS);
				sfx = 0;
			}
		}
		else
		{
			SoundEffect(SFX_PUSHABLE_SOUND, &item->pos, SFX_ALWAYS);
			sfx = 1;
		}

		GetLaraJointPos(&pos, 14);

		switch (quadrant)
		{
		case NORTH:
			offset = pos.z + *(long*)&item->item_flags[2] - *(long*)&lara_item->item_flags[2];

			if (abs(item->pos.z_pos - offset) < 512 && item->pos.z_pos > offset)
				item->pos.z_pos = offset;

			break;

		case EAST:
			offset = pos.x + *(long*)item->item_flags - *(long*)lara_item->item_flags;

			if (abs(item->pos.x_pos - offset) < 512 && item->pos.x_pos > offset)
				item->pos.x_pos = offset;

			break;

		case SOUTH:
			offset = pos.z + *(long*)&item->item_flags[2] - *(long*)&lara_item->item_flags[2];

			if (abs(item->pos.z_pos - offset) < 512 && item->pos.z_pos < offset)
				item->pos.z_pos = offset;

			break;

		case WEST:
			offset = pos.x + *(long*)item->item_flags - *(long*)lara_item->item_flags;

			if (abs(item->pos.x_pos - offset) < 512 && item->pos.x_pos < offset)
				item->pos.x_pos = offset;

			break;
		}

		if (lara_item->frame_number == anims[lara_item->anim_number].frame_end - 1)
		{
			// T4Plus: Update Room
			UpdateItemRoom(item_number, -256);

			if (input & IN_ACTION)
			{
				if (!TestBlockPull(item, 1024, quadrant))
					lara_item->goal_anim_state = 2;
			}
			else
				lara_item->goal_anim_state = 2;
		}

		break;

	case 417:
	case 418:
		frame = lara_item->frame_number;

		if (frame == anims[417].frame_base || frame == anims[418].frame_base)
		{
			item->pos.x_pos = (item->pos.x_pos & -512) | 512;
			item->pos.z_pos = (item->pos.z_pos & -512) | 512;
		}

		if (frame == anims[lara_item->anim_number].frame_end)
		{
			if (item->gravity_status == 0 || !global_info->trng_pushables_have_gravity) {
				TestTriggers(trigger_data, 1, item->flags & IFL_CODEBITS, trigger_index_room, trigger_index_floor);
				RemoveActiveItem(item_number);
				item->status = ITEM_INACTIVE;

				if (climbable_block_height > 0) {
					AlterFloorHeight(item, -climbable_block_height * 256);
				}
			}
		}

		break;
	}
}

void MovableBlockCollision(short item_number, ITEM_INFO* laraitem, COLL_INFO* coll)
{
	ITEM_INFO* item;
	PHD_VECTOR pos;
	short* bounds;
	short room_number, yrot, quadrant;

	item = &items[item_number];

	MOD_GLOBAL_INFO *global_info = get_game_mod_global_info();
	MOD_LEVEL_MISC_INFO* misc_info = get_game_mod_level_misc_info(gfCurrentLevel);

	// TRNG
	int climbable_block_height = 0;
	if (global_info->trng_pushable_extended_ocb && item->trigger_flags & 0x40) {
		climbable_block_height = item->trigger_flags & 0xf;
	// TREP
	} else if (misc_info->enable_standing_pushables) {
		climbable_block_height = (item->trigger_flags & 0xf00) >> 8;
	}

	room_number = item->room_number;

	// TODO: currently, climable blocks are not compatible with raising blocks.
	if (climbable_block_height == 0)
	{
		if (!get_game_mod_global_info()->trng_advanced_block_raising_behaviour)
		{
			item->pos.y_pos = GetHeight(GetFloor(item->pos.x_pos, item->pos.y_pos - 256, item->pos.z_pos, &room_number),
				item->pos.x_pos, item->pos.y_pos, item->pos.z_pos);
		}
	}

	if (item->room_number != room_number)
		ItemNewRoom(item_number, room_number);

	if (input & IN_ACTION && laraitem->current_anim_state == AS_STOP && laraitem->anim_number == ANIM_BREATH && !laraitem->gravity_status &&
		lara.gun_status == LG_NO_ARMS && item->status == ITEM_INACTIVE && item->trigger_flags >= 0 || (lara.IsMoving && lara.GeneralPtr == item_number))
	{
		room_number = laraitem->room_number;
		GetFloor(item->pos.x_pos, item->pos.y_pos - 256, item->pos.z_pos, &room_number);

		if (room_number == item->room_number)
		{
			// TRNG - disable movement in certain directions
			if (global_info->trng_pushable_extended_ocb && item->trigger_flags & 0x40) {
				quadrant = (ushort)(laraitem->pos.y_rot + 8192) >> 14;
				if (quadrant == EAST || quadrant == WEST) {
					if (item->trigger_flags & 0x400) { // TRNG: East and West direction disabled
						return;
					}
				}
				else if (quadrant == NORTH || quadrant == SOUTH) {
					if (item->trigger_flags & 0x200) { // TRNG: North and South direction disabled
						return;
					}
				}
			}

			bounds = GetBoundsAccurate(item);
			MovingBlockBounds[0] = bounds[0] - 100;
			MovingBlockBounds[1] = bounds[1] + 100;
			MovingBlockBounds[4] = bounds[4] - 200;
			MovingBlockBounds[5] = 0;
			yrot = item->pos.y_rot;
			item->pos.y_rot = (laraitem->pos.y_rot + 0x2000) & 0xC000;

			if (TestLaraPosition(MovingBlockBounds, item, laraitem))
			{
				if (climbable_block_height != 0 && item->status == ITEM_INACTIVE) {
					// NGLE: remove the block collision immediately
					AlterFloorHeight(item, climbable_block_height * 256);

					item->status = ITEM_ACTIVE;
				}

				if ((ushort(yrot + 0x2000) / 0x4000) + ((ushort)item->pos.y_rot / 0x4000) & 1)
					if (climbable_block_height == 0)
						MovingBlockPos.z = bounds[0] - 35;
					else
						MovingBlockPos.z = bounds[0] - 105;
				else
					if (climbable_block_height == 0)
						MovingBlockPos.z = bounds[4] - 35;
					else
						MovingBlockPos.z = bounds[0] - 105;

				if (MoveLaraPosition(&MovingBlockPos, item, laraitem))
				{
					laraitem->anim_number = ANIM_PPREADY;
					laraitem->frame_number = anims[ANIM_PPREADY].frame_base;
					laraitem->current_anim_state = AS_PPREADY;
					laraitem->goal_anim_state = AS_PPREADY;
					lara.IsMoving = 0;
					lara.gun_status = LG_HANDS_BUSY;
					lara.CornerX = item;

					// NGLE: restore it once we can grab it
					if (climbable_block_height != 0 && item->status == ITEM_ACTIVE)
					{
						AlterFloorHeight(item, -climbable_block_height * 256);

						item->status = ITEM_INACTIVE;
					}
				}
				else
					lara.GeneralPtr = item_number;
			}
			else if (lara.IsMoving && lara.GeneralPtr == item_number)
			{
				lara.IsMoving = 0;
				lara.gun_status = LG_NO_ARMS;
			}

			item->pos.y_rot = yrot;
		}
	}
	else if (laraitem->current_anim_state == AS_PPREADY && laraitem->frame_number == anims[ANIM_PPREADY].frame_base + 19 && lara.CornerX == item)
	{
		pos.x = 0;
		pos.y = 0;
		pos.z = 0;
		quadrant = (ushort)(laraitem->pos.y_rot + 8192) >> 14;
		 
		if (input & IN_FORWARD)
		{
			// TRNG
			MOD_GLOBAL_INFO *global_info = get_game_mod_global_info();
			bool can_push_over_ledges = false;
			if (global_info->trng_pushable_extended_ocb && item->trigger_flags & 0x40) {
				if (!(item->trigger_flags & 0x100)) { // TRNG: Pushing disabled
					can_push_over_ledges = item->trigger_flags & 0x20;
				}
			}

			if (!TestBlockPush(item, 1024, quadrant, can_push_over_ledges))
				return;

			laraitem->goal_anim_state = AS_PUSHBLOCK;

			if (climbable_block_height > 0) {
				// NGLE: Reset the floorstate and position back to normal
				AlterFloorHeight(item, climbable_block_height * 256);
			}
		}
		else if (input & IN_BACK)
		{
			if (!TestBlockPull(item, 1024, quadrant))
				return;

			laraitem->goal_anim_state = AS_PULLBLOCK;

			if (climbable_block_height > 0) {
				// NGLE: Reset the floorstate and position back to normal
				AlterFloorHeight(item, climbable_block_height * 256);
			}
		}
		else
			return;

		AddActiveItem(item_number);
		item->status = ITEM_ACTIVE;
		lara.head_x_rot = 0;
		lara.head_y_rot = 0;
		lara.torso_x_rot = 0;
		lara.torso_y_rot = 0;
		GetLaraJointPos(&pos, 14);
		*(long*)&laraitem->item_flags[0] = pos.x;
		*(long*)&laraitem->item_flags[2] = pos.z;
		*(long*)&item->item_flags[0] = item->pos.x_pos;
		*(long*)&item->item_flags[2] = item->pos.z_pos;
	}
	else
		if (climbable_block_height == 0)
			ObjectCollision(item_number, laraitem, coll);
}

void InitialisePlanetEffect(short item_number)
{
	ITEM_INFO* item;
	ITEM_INFO* item2;
	char* pifl;
	uchar others[4];

	item = &items[item_number];
	item->mesh_bits = 0;

	for (int i = 0; i < level_items; i++)	//get the pushable we are linked to
	{
		item2 = &items[i];

		if (item2->object_number >= PUSHABLE_OBJECT1 && item2->object_number <= PUSHABLE_OBJECT5 && item2->trigger_flags == item->trigger_flags)
		{
			item->item_flags[0] = i;
			break;
		}
	}

	if (item->trigger_flags == 1)	//get other planet effects
	{
		for (int i = 0, j = 0; i < level_items; i++)
		{
			item2 = &items[i];

			if (item2->object_number == PLANET_EFFECT && item_number != i)
				others[j++] = i;
		}

		pifl = (char*)&item->item_flags[2];

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				item2 = &items[others[j]];

				if (item2->trigger_flags == i + 2)
				{
					*pifl++ = others[j];
					break;
				}
			}
		}
	}
}

void ControlPlanetEffect(short item_number)
{
	ITEM_INFO* item;
	ITEM_INFO* item2;
	PHD_VECTOR pos;
	PHD_VECTOR pos2;
	char* pifl;
	long b, g;

	item = &items[item_number];

	if (!TriggerActive(item))
		return;

	if (item->item_flags[0] > 0)
	{
		items[item->item_flags[0]].trigger_flags = -items[item->item_flags[0]].trigger_flags;	//disable pushable :D
		item->item_flags[0] = NO_ITEM;
	}

	item->mesh_bits = 255;
	AnimateItem(item);

	if (item->trigger_flags == 1)
	{
		if ((items[LOBYTE(item->item_flags[2])].flags & IFL_CODEBITS) == IFL_CODEBITS &&
			(items[HIBYTE(item->item_flags[2])].flags & IFL_CODEBITS) == IFL_CODEBITS &&
			(items[LOBYTE(item->item_flags[3])].flags & IFL_CODEBITS) == IFL_CODEBITS &&
			(items[HIBYTE(item->item_flags[3])].flags & IFL_CODEBITS) == IFL_CODEBITS)
		{
			pos.x = 0;
			pos.y = 0;
			pos.z = 0;
			GetJointAbsPosition(item, &pos, 0);

			item2 = find_an_item_with_object_type(ANIMATING4);
			pos2.x = 0;
			pos2.y = 0;
			pos2.z = 0;
			GetJointAbsPosition(item2, &pos2, 0);

			b = (GetRandomControl() & 0x1F) + 224;
			g = b - (GetRandomControl() & 0x3F);
			TriggerLightningGlow(pos.x, pos.y, pos.z, RGBA(0, g, b, (GetRandomControl() & 0x1F) + 48));
			TriggerLightningGlow(pos2.x, pos2.y, pos2.z, RGBA(0, g, b, (GetRandomControl() & 0x1F) + 64));

			if (!(GlobalCounter & 3))
				TriggerLightning(&pos, &pos2, (GetRandomControl() & 0x1F) + 32, RGBA(0, g, b, 24), 1, 32, 5);

			pifl = (char*)&item->item_flags[2];

			for (int i = 0; i < 4; i++)
			{
				pos2.x = 0;
				pos2.y = 0;
				pos2.z = 0;
				GetJointAbsPosition(&items[pifl[i]], &pos2, 0);

				if (!(GlobalCounter & 3))
					TriggerLightning(&pos2, &pos, (GetRandomControl() & 0x1F) + 32, RGBA(0, g, b, 24), 1, 32, 5);

				TriggerLightningGlow(pos.x, pos.y, pos.z, RGBA(0, g, b, (GetRandomControl() & 0x1F) + 48));
				SoundEffect(SFX_ELEC_ARCING_LOOP, (PHD_3DPOS*)&pos, SFX_DEFAULT);
				pos = pos2;
			}

			TriggerLightningGlow(pos2.x, pos2.y, pos2.z, RGBA(0, g, b, (GetRandomControl() & 0x1F) + 48));
		}
	}
}

void DrawPlanetEffect(ITEM_INFO* item)
{
	OBJECT_INFO* obj;
	short** meshpp;
	long* bone;
	short* frm[2];
	short* rot;
	long poppush;

	// T4Plus: Animation safety check
	if (item->anim_number < 0 || item->anim_number >= num_anims) {
		return;
	}

	if (!item->mesh_bits)
		return;

	GetFrames(item, frm, &poppush);

	phd_PushMatrix();
	phd_TranslateAbs(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos);
	phd_RotYXZ(item->pos.y_rot, item->pos.x_rot, item->pos.z_rot);
	CalculateObjectLighting(item, frm[0]);

	obj = &objects[item->object_number];
	meshpp = &meshes[obj->mesh_index];
	bone = &bones[obj->bone_index];
	phd_TranslateRel(frm[0][6], frm[0][7], frm[0][8]);
	rot = frm[0] + 9;
	gar_RotYXZsuperpack(&rot, 0);
	phd_PutPolygons(*meshpp, -1);
	phd_PutPolygons(*meshpp, -1);
	meshpp += 2;

	for (int i = 0; i < obj->nmeshes - 1; i++, bone += 4, meshpp += 2)
	{
		poppush = bone[0];

		//These look inverted..
		if (poppush & 1)
			phd_PopMatrix();

		if (poppush & 2)
			phd_PushMatrix();

		phd_TranslateRel(bone[1], bone[2], bone[3]);
		gar_RotYXZsuperpack(&rot, 0);
		phd_PutPolygons(*meshpp, -1);
	}

	phd_PopMatrix();
}
