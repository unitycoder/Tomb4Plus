enum NG_ACTION_TYPE {
	TURN_ANIMATING_CLOCKWISE_BY_DEGREES = 1,
	PERFORM_FLIPEFFECT_ON_ITEM = 13,
	FORCE_ANIMATION_0_TO_31_ON_ITEM = 15,
	FORCE_ANIMATION_32_TO_63_ON_ITEM = 16,
	FORCE_ANIMATION_64_TO_95_ON_ITEM = 17,
	OPEN_OR_CLOSE_DOOR_ITEM = 26,
	MOVE_ITEM_UP_FOR_CLICKS = 30,
	MOVE_ITEM_DOWN_FOR_CLICKS = 31,
	MOVE_ITEM_WEST_FOR_CLICKS = 32,
	MOVE_ITEM_NORTH_FOR_CLICKS = 33,
	MOVE_ITEM_EAST_FOR_CLICKS = 34,
	MOVE_ITEM_SOUTH_FOR_CLICKS = 35,
	HURT_ENEMY = 38,
	MOVE_ITEM_IMMEDIATELY_TO_LARA_START_POS_WITH_MATCHING_OCB_SETTINGS = 40,
	TRIGGER_MOVEABLE_ACTIVATE_WITH_TIMER = 43,
	UNTRIGGER_MOVEABLE_ACTIVATE_WITH_TIMER = 44,
	SHOW_TRIGGER_COUNTDOWN_TIMER_FOR_ENEMY = 52,
	FREEZE_ENEMY_FOR_SECONDS = 58,
	UNFREEZE_ENEMY_WITH_EFFECT = 59,
	DISABLE_ITEM_COLLISION = 61,
	ENABLE_ITEM_COLLISION = 62,
	MOVE_ITEM_UP_BY_UNITS_X8 = 63,
	MOVE_ITEM_DOWN_BY_UNITS_X8 = 64,
	MOVE_ITEM_WEST_BY_UNITS_X8 = 65,
	MOVE_ITEM_NORTH_BY_UNITS_X8 = 66,
	MOVE_ITEM_EAST_BY_UNITS_X8 = 67,
	MOVE_ITEM_SOUTH_BY_UNITS_X8 = 68,
};

extern int NGActionTrigger(unsigned short param, unsigned short extra, unsigned short timer);
extern int NGAction(unsigned short param, unsigned short extra, bool skip_checks);