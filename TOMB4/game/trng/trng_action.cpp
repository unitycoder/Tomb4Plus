#include "../../tomb4/pch.h"

#include "../../specific/function_stubs.h"
#include "../../specific/file.h"
#include "../control.h"
#include "../effects.h"
#include "../objects.h"
#include "../door.h"
#include "../items.h"
#include "../lot.h"
#include "trng.h"
#include "trng_action.h"
#include "trng_extra_state.h"

void NGItemActivator(int item_id, bool anti) {
	ITEM_INFO* item;

	item = &items[item_id];

	if (!item->active)
	{
		if (anti)
			return;

		item->flags |= IFL_CODEBITS;

		if (objects[item->object_number].intelligent)
		{
			if (item->status == ITEM_INACTIVE)
			{
				item->touch_bits = 0;
				item->status = ITEM_ACTIVE;
				AddActiveItem(item_id);
				EnableBaddieAI(item_id, 1);
			}
			else if (item->status == ITEM_INVISIBLE)
			{
				item->touch_bits = 0;

				if (EnableBaddieAI(item_id, 0))
					item->status = ITEM_ACTIVE;
				else
					item->status = ITEM_INVISIBLE;

				AddActiveItem(item_id);
			}
		}
		else
		{
			item->touch_bits = 0;
			AddActiveItem(item_id);
			item->status = ITEM_ACTIVE;
		}
	} else {
		if (!anti)
			return;

		RemoveActiveItem(item_id);
		item->status = ITEM_INACTIVE;
		item->flags &= ~IFL_CODEBITS;
	}
}

int NGFindIndexForLaraStartPosWithMatchingOCB(unsigned int ocb) {
	for (int i = 0; i < nAIObjects; i++) {
		if (AIObjects[i].object_number == LARA_START_POS && ocb == AIObjects[i].trigger_flags) {
			return i;
		}
	}

	return -1;
}

void NGForceItemAnimation(unsigned short item_id, unsigned int animation) {
	items[item_id].anim_number = objects[items[item_id].object_number].anim_index + animation;
	items[item_id].frame_number = anims[items[item_id].anim_number].frame_base;
}

void NGHurtEnemy(unsigned short item_id, unsigned short damage) {
	if (items[item_id].hit_points > 0) {
		items[item_id].hit_points -= damage;
	}
}

int NGActionTrigger(unsigned short param, unsigned short extra, unsigned short timer) {
	unsigned char action_type = (unsigned char)extra & 0xff;
	unsigned char action_data = (unsigned char)(extra >> 8) & 0xff;

	int result = NGAction(param, extra, !NGCheckFloorStatePressedThisFrameOrLastFrame());

	// Replicates a weird bug in the original
	if (action_type == TRIGGER_MOVEABLE_ACTIVATE_WITH_TIMER || action_type == UNTRIGGER_MOVEABLE_ACTIVATE_WITH_TIMER || action_type == OPEN_OR_CLOSE_DOOR_ITEM) {
		if (!NGCheckFloorStatePressedThisFrameOrLastFrame()) {
			ITEM_INFO* item;

			item = &items[param];
			if (item->active) {
				item->timer = timer * 30;
			}
		}
	}

	return result;
}

int NGAction(unsigned short param, unsigned short extra, bool first_frame) {
	unsigned char action_type = (unsigned char)extra & 0xff;
	unsigned char action_data = (unsigned char)(extra >> 8) & 0xff;

	switch (action_type) {
		case TURN_ANIMATING_MOVING_ENDLESSLY_IN_WAY: {
			unsigned short item_id = param;
			// TODO: values are estimated and may not be accurate
			switch (action_data) {
				// Clockwise slowly (one degree per frame)
				case 0x00:
					NGSetAutoRotationPerFrame(item_id, 182);
					break;
				// Clockwise fastly (two degrees per frame)
				case 0x01:
					NGSetAutoRotationPerFrame(item_id, 182 * 2);
					break;
				// Inverse Clockwise slowly (one degree per frame)
				case 0x02:
					NGSetAutoRotationPerFrame(item_id, -182);
					break;
				// Inverse Clockwise fastly (two degrees per frame)
				case 0x03:
					NGSetAutoRotationPerFrame(item_id, -182 * 2);
					break;
			}
			break;
		}
		case PERFORM_FLIPEFFECT_ON_ITEM: {
			effect_routines[action_data](&items[param]);
			break;
		}
		case FREEZE_ENEMY_FOR_SECONDS: {
			unsigned short item_id = param;
			if (!NGIsItemFrozen(param)) {
				if (first_frame) {
					if (action_data == 0) {
						NGSetItemFreezeTimer(item_id, -1);
					}
					else {
						NGSetItemFreezeTimer(item_id, action_data * 30);
					}
				}
			}
			break;
		}
		case UNFREEZE_ENEMY_WITH_EFFECT: {
			if (!first_frame) {
				unsigned short item_id = param;
				if (action_data != 0x00) {
					Log(0, "Unimplemented action data for UNFREEZE_ENEMY_WITH_EFFECT");
				}

				if (NGIsItemFrozen(param)) {
					// TODO: action_data signifies a special effect when unfreezeing
					NGSetItemFreezeTimer(item_id, 0);
				}
			}
			break;
		}
		case HURT_ENEMY: {
			if (first_frame) {
				NGHurtEnemy(param, action_data & 0x7f);
			}
			break;
		}
		case MOVE_ITEM_IMMEDIATELY_TO_LARA_START_POS_WITH_MATCHING_OCB_SETTINGS: {
			if (first_frame) {
				int lara_start_pos_id = NGFindIndexForLaraStartPosWithMatchingOCB(action_data & 0x7f);
				if (lara_start_pos_id >= 0) {
					AIOBJECT *ai = &AIObjects[lara_start_pos_id];
					if (ai) {
						items[param].pos.x_pos = ai->x;
						items[param].pos.y_pos = ai->y;
						items[param].pos.z_pos = ai->z;
						items[param].pos.y_rot = ai->y_rot;
					}
				}
			}
			break;
		}
		case TRIGGER_MOVEABLE_ACTIVATE_WITH_TIMER: {
			if (first_frame) {
				items[param].timer = (action_data & 0x7f) * 30;
				NGItemActivator(param, false);
			}
			break;
		}
		case UNTRIGGER_MOVEABLE_ACTIVATE_WITH_TIMER: {
			if (first_frame) {
				NGItemActivator(param, true);
			}
			break;
		}
		case SHOW_TRIGGER_COUNTDOWN_TIMER_FOR_ENEMY: {
			if (first_frame) {
				NGSetDisplayTimerForMoveableWithType(param, (NGTimerTrackerType)(action_data & 0x7f));
			}
			break;
		}
		case FORCE_ANIMATION_0_TO_31_ON_ITEM: {
			if (first_frame) {
				NGForceItemAnimation(param, action_data & 0x1f);
			}
			break;
		}
		case FORCE_ANIMATION_32_TO_63_ON_ITEM: {
			if (first_frame) {
				NGForceItemAnimation(param, (action_data & 0x1f) + 32);
			}
			break;
		}
		case FORCE_ANIMATION_64_TO_95_ON_ITEM: {
			if (first_frame) {
				NGForceItemAnimation(param, (action_data & 0x1f) + 64);
			}
			break;
		}
		case OPEN_OR_CLOSE_DOOR_ITEM: {
			if (first_frame) {
				items[param].timer = (action_data & 0x7f) * 30;
				NGItemActivator(param, false);

				if (action_data) {
					items[param].flags |= IFL_CODEBITS;
				} else {
					items[param].flags &= ~IFL_CODEBITS;
				}
				return param;
			}
			break;
		}
		case MOVE_ITEM_UP_FOR_CLICKS:
			if (first_frame) {
				if (NGGetItemUpDownTimer(param) == 0) {
					NGSetItemUpDownTimer(param, (action_data + 1) * 8);
				}
			}
			break;
		case MOVE_ITEM_DOWN_FOR_CLICKS:
			if (first_frame) {
				if (NGGetItemUpDownTimer(param) == 0) {
					NGSetItemUpDownTimer(param, (action_data + 1) * -8);
				}
			}
			break;
		case MOVE_ITEM_WEST_FOR_CLICKS:
			if (first_frame) {
				if (NGGetItemEastWestTimer(param) == 0) {
					NGSetItemEastWestTimer(param, (action_data + 1) * -8);
				}
			}
			break;
		case MOVE_ITEM_SOUTH_FOR_CLICKS:
			if (first_frame) {
				if (NGGetItemNorthSouthTimer(param) == 0) {
					NGSetItemNorthSouthTimer(param, (action_data + 1) * -8);
				}
			}
			break;
		case MOVE_ITEM_EAST_FOR_CLICKS:
			if (first_frame) {
				if (NGGetItemEastWestTimer(param) == 0) {
					NGSetItemEastWestTimer(param, (action_data + 1) * 8);
				}
			}
			break;
		case MOVE_ITEM_NORTH_FOR_CLICKS:
			if (first_frame) {
				if (NGGetItemNorthSouthTimer(param) == 0) {
					NGSetItemNorthSouthTimer(param, (action_data + 1) * 8);
				}
			}
			break;
		case DISABLE_ITEM_COLLISION:
			if (first_frame)
				NGDisableItemCollision(param);
			break;
		case ENABLE_ITEM_COLLISION:
			if (first_frame)
				NGEnableItemCollision(param);
			break;
		case MOVE_ITEM_UP_BY_UNITS_X8: {
			if (first_frame)
				NGMoveItemByUnits(param, NG_UP, 8 * ((action_data)+1));
			break;
		}
		case MOVE_ITEM_DOWN_BY_UNITS_X8: {
			if (first_frame)
				NGMoveItemByUnits(param, NG_DOWN, 8 * ((action_data)+1));
			break;
		}
		case MOVE_ITEM_WEST_BY_UNITS_X8: {
			if (first_frame)
				NGMoveItemByUnits(param, NG_WEST, 8 * ((action_data)+1));
			break;
		}
		case MOVE_ITEM_NORTH_BY_UNITS_X8: {
			if (first_frame)
				NGMoveItemByUnits(param, NG_NORTH, 8 * ((action_data)+1));
			break;
		}
		case MOVE_ITEM_EAST_BY_UNITS_X8: {
			if (first_frame)
				NGMoveItemByUnits(param, NG_EAST, 8 * ((action_data)+1));
			break;
		}
		case MOVE_ITEM_SOUTH_BY_UNITS_X8: {
			if (first_frame)
				NGMoveItemByUnits(param, NG_SOUTH, 8 * ((action_data)+1));
			break;
		}
		default:
			if (first_frame)
				printf("Unimplemented NGTrigger %u\n", action_type);
			break;
		};
	return -1;
};