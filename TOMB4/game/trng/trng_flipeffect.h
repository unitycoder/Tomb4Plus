enum NG_FLIPEFFECTS {
	DISABLE_INPUT_FOR_TIME = 51,
	ENABLE_INPUT = 52,
	KILL_AND_OR_SET_LARA_ON_FIRE = 63,
	PLAY_CD_TRACK_ON_CHANNEL_1 = 68,
	STOP_ALL_CD_TRACKS = 69,
	FORCE_LARA_ANIMATION_0_255_OF_SLOT_ANIMATION = 77,
	FORCE_LARA_ANIMATION_256_512_OF_SLOT_ANIMATION = 80,
	REMOVE_WEAPONS_OR_FLARES_FROM_LARAS_HANDS = 83,
	DISARM_LARA = 96,
	GLOBAL_TRIGGER_ENABLE_DISABLE = 109,
	PERFORM_TRIGGERGROUP_FROM_SCRIPT_IN_SPECIFIC_WAY = 118,
	ORGANIZER_ENABLE = 127,
	ORGANIZER_DISABLE = 128,
	PLAY_CD_TRACK_ON_CHANNEL_2 = 129,
	STOP_CD_TRACK_ON_CHANNEL = 130,
	ATTRACT_LARA_IN_DIRECTION_ON_GROUND = 134,
	SET_VOLUME_OF_AUDIO_TRACK_ON_CHANNEL = 133,
	ACTIVATE_ITEM_GROUP_WITH_TIMER = 145,
	UNTRIGGER_ITEM_GROUP_WITH_TIMER = 146,
	ATTRACT_LARA_IN_DIRECTION_IN_AIR = 153,
	ATTRACT_LARA_IN_DIRECTION_ON_GROUND_AND_IN_AIR = 158,
	PLAY_TRACK_ON_CHANNEL_WITH_RESTORE = 193,
	VARIABLES_ADD_VALUE_TO_VARIABLE = 231,
	VARIABLES_SUBTRACT_VALUE_FROM_VARIABLE = 233,
	VARIABLES_MULTIPLY_VARIABLE_BY_VALUE = 251,
	VARIABLES_DIVIDE_VARIABLE_BY_VALUE = 253,
	CAMERA_SHOW_BLACK_SCREEN_FOR_SECONDS_WITH_FINAL_CURTAIN_EFFECT = 367,
	CAMERA_SET_CINEMA_EFFECT_TYPE_FOR_SECONDS = 369,
	PERFORM_TRIGGERGROUP_FROM_SCRIPT_IN_SINGLE_EXECUTION = 371,
	PERFORM_TRIGGERGROUP_FROM_SCRIPT_IN_MULTI_EXECUTION = 372,
	GLOBAL_TRIGGER_ENABLE_WITH_ID = 374,
	GLOBAL_TRIGGER_DISABLE_WITH_ID = 375,
	SET_LARA_HOLSTER_TYPE = 407
};

extern bool NGTriggerGroupFunction(unsigned int trigger_group_id, unsigned char execution_type);
extern bool NGFlipEffect(unsigned short param, short extra, bool oneshot, bool heavy, bool skip_checks);