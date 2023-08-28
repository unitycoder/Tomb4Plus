#pragma once

enum NG_FLIPEFFECTS {
	INVENTORY_REMOVE_INVENTORY_ITEM = 47,
	INVENTORY_INCREASE_INVENTORY_ITEMS_BY_ONE_IN_X_WAY = 48,
	INVENTORY_DECREASE_INVENTORY_ITEMS_BY_ONE = 49,
	INVENTORY_SET_INVENTORY_ITEMS = 50,
	DISABLE_INPUT_FOR_TIME = 51,
	KEYBOARD_ENABLE_INPUT = 52,
	KEYBOARD_SIMULATE_RECEIVEMENT_OF_KEYBOARD_COMMAND = 53,
	SCREEN_HIDE_SCREEN_FOR_X_TIME_IN_WAY = 54,
	SCREEN_SHOW_SCREEN = 55,
	ANIMATED_TEXTURES_STOP_ANIMATION_RANGE = 56,
	ANIMATED_TEXTURES_RESTART_ANATIMION_RANGE = 57,
	ANIMATED_TEXTURES_SET_THE_FRAME_OF_TEXTURE_OF_FIRST_P_RANGE = 58,
	ANIMATED_TEXTURES_SET_THE_FRAME_OF_TEXTURE_OF_SECOND_P_RANGE = 59,
	ANIMATED_TEXTURES_INVERT_SCROLL_DIRECTION = 60,
	WEATHER_FOG_ENABLE_VOLUMETRIC_FX = 61,
	WEATHER_FOG_DISABLE_VOLUMETRIC_FX = 62,
	KILL_AND_OR_SET_LARA_ON_FIRE = 63,
	TEXT_PRINT_NGEXTRA_STRING_ON_SCREEN_FOR_X_SECONDS = 64,
	TEXT_PRINT_STANDARD_STRING_ON_SCREEN_FOR_X_SECONDS = 65,
	TEXT_SET_COLOR_AND_POSITION_FOR_NEXT_PRINT_STRING_FLIPEFFECT = 66,
	TEXT_ERASE_ALL_STRINGS_SHOWED_WITH_PRINT_STRING_EFFECT = 67,
	PLAY_CD_TRACK_ON_CHANNEL_1 = 68,
	STOP_ALL_CD_TRACKS = 69,
	PLAY_SOUND_FROM_FIRST_GROUP = 70,
	PLAY_SOUND_FROM_SECOND_GROUP = 71,
	STOP_SOUND_FROM_FIRST_GROUP = 72,
	STOP_SOUND_FROM_SECOND_GROUP = 73,
	STOP_ALL_SOUND_SAMPLES = 74,
	TEXT_SET_BLINK_STATUS_AND_SPEED = 75,
	TEXT_RESET_ALL_TEXT_FORMATTING_SETTINGS_WITH_DEFAULT_VALUES = 76,
	FORCE_LARA_ANIMATION_0_255_OF_SLOT_ANIMATION = 77,
	FORCE_LARA_STATE_ID_AND_NEXT_STATE_ID = 78,
	MOVE_LARA_TO_START_POS_WITH_OCB_VALUE_IN_X_WAY = 79,
	FORCE_LARA_ANIMATION_256_512_OF_SLOT_ANIMATION = 80,
	TEXT_SET_SIZE_CHARACTERS_FOR_NEXT_PRINT_STRING_COMMAND = 81,
	DELAY_LOAD_LEVEL_IN_X_SECONDS = 82,
	REMOVE_WEAPONS_OR_FLARES_FROM_LARAS_HANDS = 83,
	CUTSCENE_SET_FADEIN_FOR_X_TIME = 84,
	CUTSCENE_SET_FADEOUT_FOR_X_TIME = 85,
	TIMER_SHOW_OR_HIDE_SCREEN_TIMER = 86,
	ANIMCOMMAND_ADD_TO_CURRENT_OBJECT_EFFECT_FOR_X_TIME = 87,
	ENABLE_OR_DISABLE_MIRROR_WITH_X_HIDDEN_ROOM = 88,
	DAMAGE_LARA_LIFE_BY_PERCENTAGE_OF_FULL_VITALITY = 89,
	RECHARGE_LARA_LIFE_BY_PERCENTAGE_OF_FULL_VITALITY = 90,
	LARA_INVULNERABLE_FOR_X_TIME_WITH_EFFECT = 91,
	LARA_REMOVE_FLAMES = 92,
	LARA_REMOVE_INVULNERABLE_STATUS = 93,
	ANIMATED_TEXTURES_START_THE_X_TEXTURE_SEQUENCE_FOR_ANIMATED_RANGE = 94,
	ANIMATED_TEXTURES_STOP_TEXTURE_SEQUENCE = 95,
	LARA_DISARM_LARA = 96,
	BACKUP_SAVE_IN_SILENT_WAY_THE_CURRENT_GAME_IN_X_BACKUP_FILE = 97,
	BACKUP_RESTORE_THE_X_BACKUP_FILE_IN_WAY = 98,
	LARA_SWAP_MESHES_OF_LARA_WITH_SLOT_IN_WAY = 99,
	LARA_SET_SINGLE_X_LARA_MESH_WITH_MESH_GOT_FROM_SLOT = 100,
	ANIMCOMMAND_ACTIVATE_HEAVY_TRIGGERS_IN_SECTOR_WHERE_LARA_IS = 101,
	ANIMCOMMAND_TURN_CURRENT_OBJECT_OF_X_DEGREES_IN_WAY = 102,
	ANIMCOMMAND_UPDATE_ALSO_ORIGINAL_LARA_POSITION_AFTER_A_SETPOSITION = 103,
	LARA_TOGGLE_INFINITE_AIR = 104,
	LARA_COPY_MESHES_FROM_X_SLOT_TO_LARA_MESHES_IN_WAY = 105,
	LARA_BACKUP_MESHES_OF_LARA_IN_X_SLOT_IN_WAY = 106,
	LARA_ENABLE_OR_DISABLE_WEAPONS = 107,
	LARA_HIDE_OR_SHOW_HOLSTER_MESHES = 108,
	GLOBAL_TRIGGER_ENABLE_DISABLE = 109,
	LARA_INCREASE_AIR_FOR_LARA_OF_X_UNITS_IN_WAY = 110,
	LARA_DECREASE_DAMAGE_BAR_OF_DAMAGE_ROOM_OF_X_UNITS_IN_WAY = 111,
	LARA_DECREASE_COLD_BAR_OF_COLD_ROOM_OF_X_UNITS_IN_WAY = 112,
	LARA_HEALTH_POISON_LARA_WITH_X_INTENSITY_OF_POISON = 113,
	LARA_REMOVE_POSION_FROM_LARA = 114,
	SET_ROOM_TYPE = 115,
	REMOVE_ROOM_TYPE = 116,
	WEATHER_SET_RAIN_OR_SNOW_INTENSITY_FOR_X_ROOM_WITH_NEW_INTENSITY_VALUE = 117,
	PERFORM_TRIGGERGROUP_FROM_SCRIPT_IN_SPECIFIC_WAY = 118,
	CAMERA_SET_CURRENT_CAMERA_AS_FOLLOR_CAMERA_ON_AXIS_UNTIL_CONDITION = 119,
	CAMERA_STOP_CURRENT_AXIS_OR_EFFECT_CAMERA_AND_THE_CAMERA_LINKED_WITH_IT = 120,
	LARA_DISABLE_X_SKILL = 121,
	LARA_RESTORE_X_SKILL = 122,
	CAMERA_USE_CURRENT_CAMERA_TO_PERFORM_X_EFFECT_AT_DISTANCE_FROM_TARGET = 123,
	FLIPMAP_ENABLED_X_FLIPMAP_WITH_BUTTONS_FOR_ACTIVATION = 124,
	FLIPMAP_ON = 125,
	FLIPMAP_OFF = 126,
	ORGANIZER_ENABLE = 127,
	ORGANIZER_DISABLE = 128,
	SOUND_PLAY_CD_TRACK_ON_CHANNEL_2 = 129,
	SOUND_STOP_CD_TRACK_ON_CHANNEL = 130,
	SOUND_PLAY_X_IMPORTED_FILE_IN_LOOP_MODE_ON_CHANNEL = 131,
	SOUND_PLAY_X_IMPORTED_FILE_IN_SINGLE_PLAY_MODE_ON_CHANNEL = 132,
	SOUND_SET_X_VOLUME_OF_AUDIO_TRACK_ON_CHANNEL = 133,
	LARA_ATTRACT_LARA_IN_DIRECTION_ON_GROUND_WITH_SPEED = 134,
	LARA_ATTRACT_LARA_IN_DIRECTION_IN_AIR_WITH_SPEED = 135,
	LARA_ATTRACT_LARA_UP_DOWN = 136,
	ITEMGROUP_MOVE_CONTINUOUSLY_FORWARD_BACKWARD_X_ITEMGROUP_OF_CLICKS = 137,
	ITEMGROUP_MOVE_UP_X_ITEMGROUP_FOR_CLICKS = 138,
	ITEMGROUP_MOVE_DOWN_X_ITEMGROUP_FOR_CLICKS = 139,
	ITEMGROUP_MOVE_TO_WEST_X_ITEMGROUP_FOR_CLICKS = 140,
	ITEMGROUP_MOVE_TO_NORTH_X_ITEMGROUP_FOR_CLICKS = 141,
	ITEMGROUP_MOVE_TO_EAST_X_ITEMGROUP_FOR_CLICKS = 142,
	ITEMGROUP_MOVE_TO_SOUTH_X_ITEMGROUP_FOR_CLICKS = 143,
	ITEMGROUP_MOVE_CONTINOUSLY_UPSTAIRS_DOWNSTAIRS_X_ITEMGROUP_FOR_CLICKS = 144,
	ITEMGROUP_ACTIVATE_ITEMGROUP_WITH_TIMER = 145,
	ITEMGROUP_UNTRIGGER_ITEMGROUP_WITH_TIMER = 146,
	ITEMGROUP_DISABLE_ALL_CONTINUOUS_ACTIONS_X_ITEMGROUP = 147,
	TEXT_PRINT_NGEXTRA_STRING_ONSCREEN_FREEZE_GAME_AND_WAIT_FOR_ESCAPE = 148,
	TEXT_PRINT_STANDARD_STRING_ONSCREEN_FREEZE_GAME_AND_WAIT_FOR_ESCAPE = 149,
	WEATHER_SKY_X_ENABLE_DISABLE_THE_LAYER = 150,
	WEATHER_SKY_X_ENABLE_DISABLE_LIGHTNING = 151,
	WEATHER_SKY_SET_NEW_X_COLOR_FOR_LAYER = 152,
	WEATHER_SKY_SET_NEW_X_SPEED_FOR_LAYER = 153,
	WEATHER_SKY_CHANGE_SLOWLY_THE_COLOR_OF_LAYER1_TO_X_COLOR_IN_SECONDS = 154,
	WEATHER_SKY_CHANGE_SLOWLY_THE_COLOR_OF_LAYER2_TO_X_COLOR_IN_SECONDS = 155,
	WEATHER_SET_X_NEW_STATE_FOR_SNOW_IN_CURRENT_LEVEL = 156,
	WEATHER_SET_X_NEW_STATE_FOR_RAIN_IN_CURRENT_LEVEL = 157,
	LARA_ATTRACT_LARA_IN_DIRECTION_ON_GROUND_AND_IN_AIR_WITH_SPEED = 158,
	DISTANCE_SET_LEVEL_FAR_VIEW_DISTANCE_TO_X_NUMBER_OF_SECTORS = 159,
	STATIC_SHATTER = 160,
	STATIC_REMOVE_COLLISION_FROM = 161,
	STATIC_RESTORE_COLLISION_TO = 162,
	STATIC_SET_ICE_TRANSPARENCY = 163,
	STATIC_SET_GLASS_TRANSPARENCY = 164,
	STATIC_REMOVE_TRANSPARENCY = 165,
	STATIC_MOVE_STATIC_WITH_DATA_IN_X_PARAMETERS_LIST = 166,
	MOVEABLE_MOVE_MOVEABLE_WITH_DATA_IN_X_PARAMETERS_LIST = 167,
	SOUND_PLAY_SOUND_SINGLE_PLAYBACK_OF_GLOBAL_SOUND_MAP = 168,
	LARA_FORCE_X_ANIMATION_FOR_LARA_PRESERVE_STATE_ID = 169,
	LARA_FORCE_X_ANIMATION_FOR_LARA_SET_NEW_STATE_ID = 170,
	LARA_FORCE_X_ANIMATION_FOR_LARA_SET_NEUTRAL_STATE_ID = 171,
	STATIC_ROTATE_STATIC_WITH_DATA_OF_X_PARAMETER_LIST = 172,
	MOVEABLE_ROTATE_MOVEABLE_WITH_DATA_IN_X_PARAMETERS_LIST = 173,
	STATIC_STOP_ALL_ROTATION_FOR_X_STATIC = 174,
	STATIC_STOP_ALL_ROTATION_FOR_STATICS_IN_X_ROOM = 175,
	MOVEABLE_STOP_ALL_ROTATION_FOR_MOVEABLES_IN_X_ROOM = 176,
	STATIC_STOP_THE_MOTION_OF_X_STATIC = 177,
	MOVEABLE_STOP_ALL_MOTIONS_OF_ALL_MOVEABLES_IN_X_ROOM = 178,
	STATIC_STOP_THE_MOVEMENTS_OF_ALL_STATICS_IN_X_ROOM = 179,
	STATIC_EXPLODE = 180,
	STATIC_SET_EXPLOSIVE_ATTRIBUTE = 181,
	STATIC_REMOVE_EXPLOSIVE_ATTRIBUTE = 182,
	STATIC_SET_POISON_ATTRIBUTE = 183,
	STATIC_REMOVE_POISON_ATTRIBUTE = 184,
	STATIC_SET_DAMAGE_ATTRIBUTE = 185,
	STATIC_REMOVE_DAMAGE_ATTRIBUTE = 186,
	STATIC_SET_BURNING_ATTRIBUTE = 187,
	STATIC_REMOVE_BURNING_ATTRIBUTE = 188,
	STATIC_VISIBILITY_SET_AS_INVISIBLE = 189,
	STATIC_VISIBILITY_RENDER_NEWLY_VISIBLE = 190,
	STATIC_SET_COLOR = 191,
	TRIGGERGROUP_STOP_X_TRIGGERGROUP = 192,
	PLAY_TRACK_ON_CHANNEL_WITH_RESTORE = 193,
	WEATHER_SET_X_DISTANCE_FOG_VALUE = 194,
	WEATHER_CHANGE_START_FOR_DISTANCE_TO_X_DISTANCE_IN_SECONDS = 195,
	WEATHER_PULSE_START_DISTANCE_FOG_FROM_CURRENT_TO_X_DISTANCE_IN_SECONDS = 196,
	WEATHER_ENABLE_OR_DISABLE_ALL_FOG = 197,
	WEATHER_STOP_THE_PULSE_START_DISTANCE_FOG_AND_SET_NEW_X_FOG_DISTANCE = 198,
	LARA_LIGHT_OR_PUT_OUT_THE_TORCH_IN_LARAS_HAND = 199,
	LARA_GIVE_OR_REMOVE_THE_TORCH_TO_OR_FROM_HAND_OF_LARA = 200,
	TEXT_VERTICAL_SCROLLING_OF_NGEXTRA_X_STRING_WITH_SPEED = 201,
	TEXT_ABORT_ALL_VERTICAL_SCROLLING_TEXT_OPERATIONS = 202,
	TEXT_PRINT_FORMATTED_TEXT_NGEXTRA_STRING_WITH_FORMATTING_DATA = 203,
	TEXT_REMOVE_X_EXTRA_NGSTRING_FROM_SCREEN = 204,
	TEXT_VERTICAL_SCROLLING_OF_NGEXTRA_X_STRING_WITH_FORMATTING_DATA = 205,
	TEXT_HORIZONTAL_SCROLLING_OF_NGEXTRA_X_STRING_WITH_FORMATTING_DATA = 206,
	TEXT_PRINT_PSX_X_STRING_WITH_FORMATTING_DATA = 207,
	TEXT_PRINT_PC_X_STRING_WITH_FORMATTING_DATA = 208,
	TEXT_PRINT_PC_X_STRING_WITH_FORMATTING_DATA_AND_WAIT_FOR_ESCAPE = 209,
	TEXT_PRINT_NGEXTRA_X_STRING_WITH_FORMATTING_DATA_AND_WAIT_FOR_ESCAPE = 210,
	ANIMCOMMAND_SET_TEMPORARY_FREE_HANDS_UNTIL_IS_PERFORMING_X_ANIMATION = 211,
	ANIMCOMMAND_SET_TEMPORARY_FREE_HANDS_FOR_X_SECONDS = 212,
	ANIMCOMMAND_REMOVE_FREE_HANDS_AND_RESTORE_PREVIOUS_STATUS = 213,
	CAMERA_CHANGE_CAMERA_MODE_WITH_X_PARAMETER_FOR_TIME = 214,
	CAMERA_RESTORE_CAMERA_MODE_AFTER_A_CHANGE_CAMERA_FLIPEFFECT = 215,
	ANIMCOMMAND_RESET_THE_NUMBER_OF_TURNS_JUMP_POWER_OF_PARALLEL_BAR = 216,
	IMAGES_SHOW_IMAGE_WITH_DATA_IN_X_IMAGE_SCRIPT_COMMAND_FOR_SECONDS = 217,
	IMAGES_REMOVE_FROM_SCREEN_THE_CURRENT_POP_UP_IMAGE = 218,
	DIARY_ADD_EXTRA_NG_STIRNG_TO_DIARY = 219,
	DIARY_CLEAR_ALL_STRINGS_IN_X_DIARY = 220,
	DIARY_REMOVE_LAST_STRING_FROM_X_DIARY = 221,
	DIARY_SHOW_DIARY_AT_PAGE = 222,
	SHOW_STATISTICS_SCREEN = 223,
	WEATHER_SET_THE_X_COLOR_FOR_DISTANCE_FOG = 224,
	WEATHER_ENABLE_HARDWARE_FOG = 225,
	WEATHER_SET_X_MAX_VISIBILITY_DISTANCE_FOR_FOG_BULBS = 226,
	WEATHER_SET_X_END_FOG_LIMIT_FOR_DISTANCE_FOG = 227,
	WEATHER_CHANGE_END_LIMIT_OF_DISTANCE_FOG_IN_X_WAY_WITH_SPEED = 228,
	WEATHER_CHANGE_START_LIMIT_OF_DISTANCE_FOG_IN_X_WAY_WITH_SPEED = 229,
	WEATHER_STOP_THE_X_CHANGE_LIMIT_OF_DISTANEC_FOG_EFFECT = 230,
	VARIABLES_ADD_VALUE_TO_X_VARIABLE = 231,
	VARIABLES_SET_X_VARIABLE_TO_VALUE = 232,
	VARIABLES_SUBTRACT_VALUE_FROM_X_VARIABLE = 233,
	VARIABLES_SET_IN_X_VARIABLE_THE_BIT = 234,
	VARIABLES_CLEAR_IN_X_VARIABLE_THE_BIT = 235,
	VARIABLES_COPY_CURRENTVALUE_TO_X_STORE_VARIABLE = 236,
	VARIABLES_COPY_X_STORE_VARIABLE_TO_CURRENTVALUE = 237,
	VARIABLES_COPY_THE_X_TEXT_VARIABLE_TO_Y_TEXT_VALUE = 238,
	VARIABLES_COPY_THE_X_NG_STRING_TO_Y_TEXT_VALUE = 239,
	VARIABLES_ADD_TO_BIG_TEXT_THE_X_NG_STRING_WITH_SEPARATOR = 240,
	VARIABLES_CLEAR_THE_X_VARIABLE_GROUP = 241,
	VARIABLES_ADD_TO_BIG_TEXT_THE_X_TEXT_VARIABLE_WITH_SEPARATOR = 242,
	VARIABLES_ADD_TO_BIG_TEXT_THE_X_NUMERIC_VARIABLE_WITH_SEPARATOR = 243,
	VARIABLES_COPY_TO_X_NUMERIC_VARIABLE_THE_SAVEGAME_MEMORY_VALUE = 244,
	VARIABLES_COPY_FROM_X_NUMERIC_VARIABLE_THE_SAVEGAME_MEMORY_VALUE = 245,
	VARIABLES_SET_IN_X_SAVEGAME_MEMORY_THE_VALUE = 246,
	VARIABLES_SET_IN_X_SAVEGAME_MEMORY_THE_BIT = 247,
	VARIABLES_CLEAR_IN_X_SAVEGAME_MEMORY_THE_BIT = 248,
	VARIABLES_ADD_TO_X_SAVEGAME_MEMORY_THE_VALUE = 249,
	VARIABLES_SUBTRACT_FROM_X_SAVEGAME_MEMORY_THE_VALUE = 250,
	VARIABLES_MULTIPLY_X_VARIABLE_BY_VALUE = 251,
	VARIABLE_SET_IN_X_NUMBERIC_VARIABLE_THE_NEGATIVE_VALUE = 252,
	VARIABLES_DIVIDE_X_VARIABLE_BY_VALUE = 253,
	VARIABLES_SET_IN_X_SAVEGAME_MEMORY_THE_NEGATIVE_VALUE = 254,
	VARIABLES_SET_IN_X_SELECTED_ITEM_MEMORY_THE_VALUE = 255,
	VARIABLES_COPY_TO_X_NUMERIC_VARIABLE_THE_SELECTED_ITEM_MEMORY = 256,
	VARIABLES_COPY_FROM_X_NUMERIC_VARIABLE_TO_SELECTED_ITEM_MEMORY = 257,
	VARIABLES_ADD_TO_X_SELECTED_ITEM_MEMORY_THE_VALUE = 258,
	VARIABLES_SET_IN_X_SELECTED_ITEM_MEMORY_THE_BIT = 259,
	VARIABLES_CLEAR_IN_X_SELECTED_ITEM_MEMORY_THE_BIT = 260,
	VARIABLES_SET_IN_X_SELECTED_ITEM_MEMORY_THE_BIG_NUMBER_VALUE = 261,
	VARIABLES_SET_IN_X_SAVEGAME_MEMORY_THE_BIG_NUMBER_VALUE = 262,
	VARIABLES_SET_IN_X_NUMBERIC_VARIABLE_THE_BIG_NUMBER_VALUE = 263,
	VARIABLES_START_TRNG_TIMER_TO_X_MODE = 264,
	VARIABLES_STOP_THE_X_TRNG_TIMER = 265,
	VARIABLES_INITIALIZE_TRNG_TIMER_TO_X_SECONDS = 266,
	VARIABLES_INITIALIZE_X_TRNG_TIMER_TO_BIG_NUMBER_SECONDS = 267,
	VARIABLES_INITIALIZE_X_TRNG_TIMER_TO_FRAME_TICKS = 268,
	VARIABLES_SHOW_TRNG_TIMER_IN_X_POSITION = 269,
	VARIABLES_HIDE_TRNG_TIMER_IN_X_POSITION = 270,
	VARIABLES_COPY_X_NUMBERIC_VARIABLE_TO_CURRENTVALUE = 271,
	VARIABLES_COPY_CURRENTVALUE_TO_X_NUMBERIC_VALUE = 272,
	VARIABLES_ADD_TO_X_SAVEGAME_MEMORY_THE_CURRENTVALUE = 273,
	VARIABLES_SUBTRACT_FROM_X_SAVEGAME_MEMORY_THE_CURRENTVALUE = 274,
	VARIABLES_ADD_TO_SELECTED_ITEM_MEMORY_THE_CURRENTVALUE = 275,
	VARIABLES_SUBTRACT_TO_SELECTED_ITEM_MEMORY_THE_CURRENTVALUE = 276,
	VARIABLES_COPY_FROM_X_CODE_MEMORY_TO_CURRENTVALUE = 277,
	VARIABLES_COPY_FROM_CURRENTVALUE_TO_X_CODE_MEMORY = 278,
	VARIABLES_SET_IN_X_CODE_MEMORY_THE_VALUE = 279,
	VARIABLES_ADD_TO_X_CODE_MEMORY_THE_VALUE = 280,
	VARIABLES_SET_IN_X_CODE_MEMORY_THE_BIT = 281,
	VARIABLES_CLEAR_IN_X_CODE_MEMORY_THE_BIT = 282,
	VARIABLES_ADD_TO_X_CODE_MEMORY_THE_CURRENTVALUE = 283,
	VARIABLES_INVERT_THE_SIGN_OF_X_NUMERIC_VALUE = 284,
	VARIABLES_ADD_TO_CURRENTVALUE_THE_X_NUMERIC_VARIABLE = 285,
	VARIABLES_SUBTRACT_FROM_CURRENTVALUE_THE_X_NUMERIC_VARIABLE = 286,
	VARIABLES_DIVIDE_CURRENTVALUE_BY_X_NUMERIC_VARIABLE = 287,
	VARIABLES_MULTIPLY_CURRENTVALUE_BY_X_NUMERIC_VARIABLE = 288,
	SWITCH_PERFORM_THE_X_SWITCH_SCRIPT_COMMAND = 289,
	ORGANIZER_RESUME_X_ORGANIZER_IN_Y_WAY = 290,
	VARIABLES_COPY_TO_X_NUMERIC_VARIABLE_THE_Y_COLOR_RGB = 291,
	VARIABLES_SET_THE_X_SLOT_AS_SELECTED_SLOT_MEMORY = 292,
	VARIABLES_COPY_FROM_SELECTED_SLOT_MEMORY_TO_X_NUMERIC_VARIABLE = 293,
	VARIABLES_COPY_FROM_X_NUMERIC_VARIABLE_TO_SELECTED_SLOT_MEMORY = 294,
	VARIABLES_COPY_FROM_SELECTED_ANIMATION_MEMORY_TO_X_NUMERIC_VARIABLE = 295,
	VARIABLES_COPY_FROM_X_NUMERIC_VARIABLE_TO_SELECTED_ANIMATION_MEMORY = 296,
	VARIABLES_CONVERT_THE_X_NGLE_ROOM_INDEX_IN_TOMB_ROOM_INDEX_TO_CURRENTVALUE = 297,
	VARIABLES_CONVERT_THE_TOMB_ROOM_INDEX_TO_NGLE_ROOM_INDEX_IN_CURRENTVALUE = 298,
	VARIABLES_CONVERT_THE_NGLE_ROOM_INDEX_TO_TOMB_ROOM_INDEX_IN_CURRENTVALUE = 299,
	VARIABLES_CONVERT_THE_TOMB_ITEM_INDEX_TO_NGLE_ITEM_INDEX_IN_CURRENTVALUE = 300,
	VARIABLES_CONVERT_THE_NGLE_ITEM_INDEX_TO_TOMB_ITEM_INDEX_IN_CURRENTVALUE = 301,
	VARIABLES_SAVE_THE_COORDINATES_AND_FACING_OF_ITEM_INDEX_IN_CURRENTVALUE = 302,
	VARIABLES_GENERATE_IN_X_NUMERIC_VARIABLE_THE_RANDOM_NUMBER = 303,
	VARIABLES_GENERATE_IN_X_NUMERIC_VARIABLE_A_RANDOM_CURRENTVALUE = 304,
	VARIABLES_PERFORM_OPERATION_X_NUMERICVARIABLE_AND_NUMBER = 305,
	INVENTORY_POP_UP_INVENTORY_TO_SELECT_X_ITEM_IN_WAY = 306,
	SCREEN_FLASH_SCREEN_WITH_LIGHT_COLOR_FOR_DURATION = 355,
	SPRITE_SHOW_SPRITE_WITH_DATA_IN_PARAMETERS_FOR_DURATION = 357,
	CAMERA_SHOW_BLACK_SCREEN_FOR_SECONDS_WITH_FINAL_CURTAIN_EFFECT = 367,
	CAMERA_SET_CINEMA_EFFECT_TYPE_FOR_SECONDS = 369,
	PERFORM_TRIGGERGROUP_FROM_SCRIPT_IN_SINGLE_EXECUTION = 371,
	PERFORM_TRIGGERGROUP_FROM_SCRIPT_IN_MULTI_EXECUTION = 372,
	GLOBAL_TRIGGER_ENABLE_WITH_ID = 374,
	GLOBAL_TRIGGER_DISABLE_WITH_ID = 375,
	SET_LARA_HOLSTER_TYPE = 407
};

extern bool NGFlipEffect(unsigned short param, short extra, bool heavy, bool skip_checks);
extern bool NGFlipEffectTrigger(unsigned short param, short extra, bool heavy);