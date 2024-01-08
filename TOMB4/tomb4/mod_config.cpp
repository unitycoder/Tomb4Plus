#include "../tomb4/pch.h"
#include "mod_config.h"
#include "../specific/file.h"

#include "libs/tiny-json/tiny-json.h"
#include "../specific/function_stubs.h"
#include "../game/trng/trng.h"
#include "../specific/audio.h"
#include "tomb4plus/t4plus_inventory.h"
#include "../game/lara.h"

#include "../game/trep/furr.h"

#define READ_JSON_INTEGER_CAST(value_name, json, my_struct, my_type) { const json_t* value_name = json_getProperty(json, #value_name); \
    if (value_name && JSON_INTEGER == json_getType(value_name)) { \
        (my_struct)->value_name = (my_type)json_getInteger(value_name); } \
    }

#define READ_JSON_SINT8(value_name, json, my_struct) { const json_t* value_name = json_getProperty(json, #value_name); \
    if (value_name && JSON_INTEGER == json_getType(value_name)) { \
        (my_struct)->value_name = (signed char)json_getInteger(value_name); } \
    }

#define READ_JSON_SINT16(value_name, json, my_struct) { const json_t* value_name = json_getProperty(json, #value_name); \
    if (value_name && JSON_INTEGER == json_getType(value_name)) { \
        (my_struct)->value_name = (signed short)json_getInteger(value_name); } \
    }

#define READ_JSON_SINT32(value_name, json, my_struct) { const json_t* value_name = json_getProperty(json, #value_name); \
    if (value_name && JSON_INTEGER == json_getType(value_name)) { \
        (my_struct)->value_name = (signed int)json_getInteger(value_name); } \
    }

#define READ_JSON_UINT8(value_name, json, my_struct) { const json_t* value_name = json_getProperty(json, #value_name); \
    if (value_name && JSON_INTEGER == json_getType(value_name)) { \
        (my_struct)->value_name = (unsigned char)json_getInteger(value_name); } \
    }

#define READ_JSON_UINT16(value_name, json, my_struct) { const json_t* value_name = json_getProperty(json, #value_name); \
    if (value_name && JSON_INTEGER == json_getType(value_name)) { \
        (my_struct)->value_name = (unsigned short)json_getInteger(value_name); } \
    }

#define READ_JSON_UINT32(value_name, json, my_struct) { const json_t* value_name = json_getProperty(json, #value_name); \
    if (value_name && JSON_INTEGER == json_getType(value_name)) { \
        (my_struct)->value_name = (unsigned int)json_getInteger(value_name); } \
    }

#define READ_JSON_BOOL(value_name, json, my_struct) { const json_t* value_name = json_getProperty(json, #value_name); \
    if (value_name && JSON_BOOLEAN == json_getType(value_name)) { \
        (my_struct)->value_name = (bool)json_getBoolean(value_name); } \
    }

#define READ_JSON_BOOL_AND_SET_FLAG(value_name, json, my_struct, flag) { const json_t* value_name = json_getProperty(json, #value_name); \
    if (value_name && JSON_BOOLEAN == json_getType(value_name)) { \
        (my_struct)->value_name = (bool)json_getBoolean(value_name); } \
    } \
    flag = true;

#define READ_JSON_FLOAT32(value_name, json, my_struct) { const json_t* value_name = json_getProperty(json, #value_name); \
    if (value_name && JSON_REAL == json_getType(value_name)) { \
        (my_struct)->value_name = (float)json_getReal(value_name); } \
    }

#define READ_JSON_ARGB(value_name, json, my_struct) { \
    const json_t* value_name = json_getProperty(json, #value_name); \
    if (value_name && JSON_OBJ == json_getType(value_name)) {\
    const json_t* r = json_getProperty(value_name, "r"); \
    if (r && JSON_INTEGER == json_getType(r)) { \
        unsigned char r8 = (unsigned char)json_getInteger(r); \
        (my_struct)->value_name &= ~(0x00ff0000); \
        (my_struct)->value_name |= (((unsigned int)r8) << 16) & 0x00ff0000; \
    } \
    const json_t* g = json_getProperty(value_name, "g"); \
    if (g && JSON_INTEGER == json_getType(g)) { \
        unsigned char g8 = (unsigned char)json_getInteger(g); \
        (my_struct)->value_name &= ~(0x0000ff00); \
        (my_struct)->value_name |= (((unsigned int)g8) << 8) & 0x0000ff00; \
    } \
    const json_t* b = json_getProperty(value_name, "b"); \
    if (b && JSON_INTEGER == json_getType(b)) { \
        unsigned char b8 = (unsigned char)json_getInteger(b); \
        (my_struct)->value_name &= ~(0x000000ff); \
        (my_struct)->value_name |= (((unsigned int)b8)) & 0x000000ff; \
    } \
    const json_t* a = json_getProperty(value_name, "a"); \
    if (a && JSON_INTEGER == json_getType(a)) { \
        unsigned char a8 = (unsigned char)json_getInteger(a); \
        (my_struct)->value_name &= ~(0xff000000); \
        (my_struct)->value_name |= (((unsigned int)a8) << 24) & 0xff000000; \
    } \
    } \
    }
    

// Full overrides
bool scorpion_poison_override_found = false;

GAME_MOD_CONFIG game_mod_config;

void setup_custom_slots_for_level(int level, OBJECT_INFO* current_object_info_array) {
    OBJECT_INFO* backup_object_info_array = (OBJECT_INFO* )malloc(sizeof(OBJECT_INFO) * NUMBER_OBJECTS);

    if (backup_object_info_array) {
        memcpy(backup_object_info_array, current_object_info_array, sizeof(OBJECT_INFO) * NUMBER_OBJECTS);

        for (int i = 0; i < NUMBER_OBJECTS; i++) {
            if (game_mod_config.level_info[level].slot_info[i] != i) {
                memcpy(&current_object_info_array[i], &backup_object_info_array[game_mod_config.level_info[level].slot_info[i]], sizeof(OBJECT_INFO));
            }
        }
        free(backup_object_info_array);
    }
}

void assign_slot_for_level(int level, int dest_slot, int src_slot) {
    if (src_slot < NUMBER_OBJECTS && dest_slot < NUMBER_OBJECTS && level < MOD_LEVEL_COUNT) {
        game_mod_config.level_info[level].slot_info[dest_slot] = src_slot;
    } else {
        printf("Invalid slot assignment!\n");
    }
}

extern MOD_GLOBAL_INFO *get_game_mod_global_info() {
    return &game_mod_config.global_info;
}

MOD_LEVEL_AUDIO_INFO *get_game_mod_level_audio_info(int level) {
    return &game_mod_config.level_info[level].audio_info;
}

MOD_LEVEL_BAR_INFO *get_game_mod_level_bar_info(int level) {
    return &game_mod_config.level_info[level].bar_info;
}

MOD_LEVEL_ENVIRONMENT_INFO *get_game_mod_level_environment_info(int level) {
    return &game_mod_config.level_info[level].environment_info;
}

extern MOD_LEVEL_FONT_INFO *get_game_mod_level_font_info(int level) {
    return &game_mod_config.level_info[level].font_info;
}

extern MOD_LEVEL_CAMERA_INFO *get_game_mod_level_camera_info(int level) {
    return &game_mod_config.level_info[level].camera_info;
}

MOD_LEVEL_CREATURE_INFO *get_game_mod_level_creature_info(int level) {
    return &game_mod_config.level_info[level].creature_info;
}

MOD_LEVEL_LARA_INFO *get_game_mod_level_lara_info(int level) {
	return &game_mod_config.level_info[level].lara_info;
}

MOD_LEVEL_STAT_INFO *get_game_mod_level_stat_info(int level) {
    return &game_mod_config.level_info[level].stat_info;
}

MOD_LEVEL_FLARE_INFO *get_game_mod_level_flare_info(int level) {
    return &game_mod_config.level_info[level].flare_info;
}

MOD_LEVEL_WEAPON_INFO *get_game_mod_level_weapon_info(int level) {
    return &game_mod_config.level_info[level].weapon_info;
}

MOD_LEVEL_AMMO_INFO *get_game_mod_current_lara_ammo_info(MOD_LEVEL_WEAPON_INFO *weapon_info) {
    switch (lara.weapon_item)
    {
    case WEAPON_REVOLVER:
        return &weapon_info->six_shooter_ammo_info;
    case WEAPON_UZI:
        return &weapon_info->uzi_ammo_info;
    case WEAPON_SHOTGUN:
        if (lara.shotgun_type_carried & W_AMMO1)
            return &weapon_info->shotgun_1_ammo_info;
        else
            return &weapon_info->shotgun_2_ammo_info;
    case WEAPON_GRENADE:
        if (lara.grenade_type_carried & W_AMMO1)
            return &weapon_info->grenade_1_ammo_info;
        else if (lara.grenade_type_carried & W_AMMO2)
            return &weapon_info->grenade_2_ammo_info;
        else
            return &weapon_info->grenade_3_ammo_info;

        break;
    case WEAPON_CROSSBOW:
        if (lara.crossbow_type_carried & W_AMMO1)
            return &weapon_info->crossbow_1_ammo_info;
        else if (lara.crossbow_type_carried & W_AMMO2)
            return &weapon_info->crossbow_2_ammo_info;
        else
            return &weapon_info->crossbow_3_ammo_info;
    default:
        return &weapon_info->pistol_ammo_info;
    }
}

MOD_LEVEL_MISC_INFO *get_game_mod_level_misc_info(int level) {
    return &game_mod_config.level_info[level].misc_info;
}

void LoadGameModLevelAudioInfo(const json_t* audio, MOD_LEVEL_AUDIO_INFO* audio_info) {
    READ_JSON_BOOL(new_audio_system, audio, audio_info);
    READ_JSON_BOOL(old_cd_trigger_system, audio, audio_info);

    READ_JSON_SINT16(first_looped_audio_track, audio, audio_info);
    READ_JSON_SINT16(last_looped_audio_track, audio, audio_info);

    READ_JSON_SINT16(inside_jeep_track, audio, audio_info);
    READ_JSON_SINT16(outside_jeep_track, audio, audio_info);
    READ_JSON_SINT16(secret_track, audio, audio_info);
}

void LoadGameModLevelBarInfo(const json_t* bar, MOD_LEVEL_BAR_INFO* bar_info) {
    READ_JSON_ARGB(health_bar_main_color, bar, bar_info);
    READ_JSON_ARGB(health_bar_fade_color, bar, bar_info);
    READ_JSON_ARGB(health_bar_poison_color, bar, bar_info);

    READ_JSON_ARGB(air_bar_main_color, bar, bar_info);
    READ_JSON_ARGB(air_bar_fade_color, bar, bar_info);

    READ_JSON_ARGB(sprint_bar_main_color, bar, bar_info);
    READ_JSON_ARGB(sprint_bar_fade_color, bar, bar_info);

    READ_JSON_ARGB(loading_bar_main_color, bar, bar_info);
    READ_JSON_ARGB(loading_bar_fade_color, bar, bar_info);
}

void LoadGameModLevelEnvironmentInfo(const json_t* environment, MOD_LEVEL_ENVIRONMENT_INFO* environment_info) {
    READ_JSON_UINT32(fog_start_range, environment, environment_info);
    READ_JSON_UINT32(fog_end_range, environment, environment_info);
    READ_JSON_UINT32(far_view, environment, environment_info);
}

void LoadGameModLevelFontInfo(const json_t* font, MOD_LEVEL_FONT_INFO* font_info) {
    READ_JSON_SINT32(custom_glyph_scale_width, font, font_info);
    READ_JSON_SINT32(custom_glyph_scale_height, font, font_info);

    const json_t* char_table = json_getProperty(font, "custom_font_table");
    if (char_table && JSON_ARRAY == json_getType(char_table)) {
        json_t const *char_table_entry;
        int char_table_index = 0;
        for (char_table_entry = json_getChild(char_table); char_table_entry != 0; char_table_entry = json_getSibling(char_table_entry)) {
            if (char_table_index >= CHAR_TABLE_COUNT)
                break;

            READ_JSON_FLOAT32(u, char_table_entry, &font_info->custom_font_table[char_table_index]);
            READ_JSON_FLOAT32(v, char_table_entry, &font_info->custom_font_table[char_table_index]);

            READ_JSON_SINT16(w, char_table_entry, &font_info->custom_font_table[char_table_index]);
            READ_JSON_SINT16(h, char_table_entry, &font_info->custom_font_table[char_table_index]);
            READ_JSON_SINT16(y_offset, char_table_entry, &font_info->custom_font_table[char_table_index]);

            READ_JSON_SINT8(top_shade, char_table_entry, &font_info->custom_font_table[char_table_index]);
            READ_JSON_SINT8(bottom_shade, char_table_entry, &font_info->custom_font_table[char_table_index]);

            char_table_index++;
        }
    }
}

void LoadGameModLevelCameraInfo(const json_t* camera, MOD_LEVEL_CAMERA_INFO* camera_info) {
    READ_JSON_SINT32(chase_cam_distance, camera, camera_info);
    READ_JSON_SINT32(chase_camera_vertical_orientation, camera, camera_info);
    READ_JSON_SINT32(chase_camera_horizontal_orientation, camera, camera_info);

    READ_JSON_SINT32(combat_cam_distance, camera, camera_info);
    READ_JSON_SINT32(combat_cam_vertical_orientation, camera, camera_info);

    READ_JSON_SINT32(look_camera_distance, camera, camera_info);
    READ_JSON_SINT32(look_camera_height, camera, camera_info);

    READ_JSON_SINT32(camera_speed, camera, camera_info);
}

void LoadGameModLevelLaraInfo(const json_t* level, MOD_LEVEL_LARA_INFO *lara_info) {
    READ_JSON_SINT32(hair_gravity, level, lara_info);

    READ_JSON_SINT32(braid_x, level, lara_info);
    READ_JSON_SINT32(braid_y, level, lara_info);
    READ_JSON_SINT32(braid_z, level, lara_info);

    READ_JSON_SINT32(pigtail_left_x, level, lara_info);
    READ_JSON_SINT32(pigtail_left_y, level, lara_info);
    READ_JSON_SINT32(pigtail_left_z, level, lara_info);

    READ_JSON_SINT32(pigtail_right_x, level, lara_info);
    READ_JSON_SINT32(pigtail_right_y, level, lara_info);
    READ_JSON_SINT32(pigtail_right_z, level, lara_info);

    READ_JSON_SINT32(crawlspace_jump_animation, level, lara_info);
    READ_JSON_SINT32(crawlspace_jump_pit_deepness_threshold, level, lara_info);

    READ_JSON_BOOL(use_tr5_swimming_collision, level, lara_info);
    READ_JSON_BOOL(disable_hardcoded_breath_sound, level, lara_info);
}

void LoadGameModLevelCreatureInfo(const json_t* creature, MOD_LEVEL_CREATURE_INFO *creature_info) {
    READ_JSON_BOOL_AND_SET_FLAG(small_scorpion_is_poisonous, creature, creature_info, scorpion_poison_override_found);
    READ_JSON_SINT32(small_scorpion_poison_strength, creature, creature_info);

    READ_JSON_BOOL(remove_knights_templar_sparks, creature, creature_info);

    READ_JSON_BOOL(remove_ahmet_death_flames, creature, creature_info);
    READ_JSON_BOOL(remove_ahmet_death_loop, creature, creature_info);
    READ_JSON_BOOL(disable_ahmet_heavy_trigger, creature, creature_info);

    READ_JSON_BOOL(remove_mummy_stun_animations, creature, creature_info);
}

void LoadGameModLevelMiscInfo(const json_t *misc, MOD_LEVEL_MISC_INFO *misc_info) {
    READ_JSON_INTEGER_CAST(rain_type, misc, misc_info, WeatherType);
    READ_JSON_INTEGER_CAST(snow_type, misc, misc_info, WeatherType);

    READ_JSON_BOOL(lara_impales_on_spikes, misc, misc_info);
    READ_JSON_BOOL(enable_ricochet_sound_effect, misc, misc_info);
    READ_JSON_BOOL(enable_standing_pushables, misc, misc_info);
    READ_JSON_BOOL(enemy_gun_hit_underwater_sfx_fix, misc, misc_info);
    READ_JSON_BOOL(darts_poison_fix, misc, misc_info);
    READ_JSON_BOOL(disable_motorbike_headlights, misc, misc_info);
}

void LoadGameModLevelStatInfo(const json_t* stats, MOD_LEVEL_STAT_INFO* stat_info) {
    READ_JSON_UINT32(secret_count, stats, stat_info);
}

void LoadGameModLevelWeaponInfo(const json_t* stats, MOD_LEVEL_WEAPON_INFO* weapon_info) {

}

void LoadGameModLevel(const json_t *level, MOD_LEVEL_INFO *level_info) {
    const json_t* audio_info = json_getProperty(level, "audio_info");
    if (audio_info && JSON_OBJ == json_getType(audio_info)) {
        LoadGameModLevelAudioInfo(audio_info, &level_info->audio_info);
    }

    const json_t* bar_info = json_getProperty(level, "bar_info");
    if (bar_info && JSON_OBJ == json_getType(bar_info)) {
        LoadGameModLevelBarInfo(bar_info, &level_info->bar_info);
    }

    const json_t* environment_info = json_getProperty(level, "environment_info");
    if (environment_info && JSON_OBJ == json_getType(environment_info)) {
        LoadGameModLevelEnvironmentInfo(environment_info, &level_info->environment_info);
    }

    const json_t* font_info = json_getProperty(level, "font_info");
    if (font_info && JSON_OBJ == json_getType(font_info)) {
        LoadGameModLevelFontInfo(font_info, &level_info->font_info);
    }

    const json_t* lara_info = json_getProperty(level, "lara_info");
    if (lara_info && JSON_OBJ == json_getType(lara_info)) {
        LoadGameModLevelLaraInfo(lara_info, &level_info->lara_info);
    }

    const json_t* creature_info = json_getProperty(level, "creature_info");
    if (creature_info && JSON_OBJ == json_getType(creature_info)) {
        LoadGameModLevelCreatureInfo(creature_info, &level_info->creature_info);
    }

    const json_t* stat_info = json_getProperty(level, "stat_info");
    if (stat_info && JSON_OBJ == json_getType(stat_info)) {
        LoadGameModLevelStatInfo(stat_info, &level_info->stat_info);
    }

    const json_t* weapon_info = json_getProperty(level, "weapon_info");
    if (weapon_info && JSON_OBJ == json_getType(weapon_info)) {
        LoadGameModLevelWeaponInfo(weapon_info, &level_info->weapon_info);
    }

    const json_t* misc_info = json_getProperty(level, "misc_info");
    if (misc_info && JSON_OBJ == json_getType(misc_info)) {
        LoadGameModLevelMiscInfo(misc_info, &level_info->misc_info);
    }
}

void SetupDefaultFontInfoForLevel(MOD_LEVEL_INFO* level_info) {
    level_info->font_info.custom_glyph_scale_width = 512;
    level_info->font_info.custom_glyph_scale_height = 240;

    memcpy(level_info->font_info.custom_font_table, DEFAULT_CHAR_TABLE, sizeof(CHARDEF) * CHAR_TABLE_COUNT);
}

void SetupDefaultSlotInfoForLevel(MOD_LEVEL_INFO* level_info) {
    for (int i = 0; i < NUMBER_OBJECTS; i++) {
        level_info->slot_info[i] = i;
    }
}

void SetupDefaultWeaponInfoForLevel(MOD_LEVEL_INFO* level_info) {
    // Pistols
    level_info->weapon_info.pistol_ammo_info.damage = 1;
    level_info->weapon_info.pistol_ammo_info.fire_rate = 9;
    level_info->weapon_info.pistol_ammo_info.dispertion = 1456;
    level_info->weapon_info.pistol_ammo_info.flash_duration = 3;

    level_info->weapon_info.pistol_ammo_info.weapon_pickup_amount = 40;
    level_info->weapon_info.pistol_ammo_info.ammo_pickup_amount = 40;

    level_info->weapon_info.pistol_ammo_info.add_pistol_shell = true;

    // Uzis
    level_info->weapon_info.uzi_ammo_info.damage = 1;
    level_info->weapon_info.uzi_ammo_info.fire_rate = 3;
    level_info->weapon_info.uzi_ammo_info.dispertion = 1456;
    level_info->weapon_info.uzi_ammo_info.flash_duration = 3;

    level_info->weapon_info.uzi_ammo_info.weapon_pickup_amount = 30;
    level_info->weapon_info.uzi_ammo_info.ammo_pickup_amount = 30;

    level_info->weapon_info.uzi_ammo_info.add_pistol_shell = true;

    // Six-Shooter
    level_info->weapon_info.six_shooter_ammo_info.damage = 21;
    level_info->weapon_info.six_shooter_ammo_info.fire_rate = 16;
    level_info->weapon_info.six_shooter_ammo_info.dispertion = 728;
    level_info->weapon_info.six_shooter_ammo_info.flash_duration = 3;

    level_info->weapon_info.six_shooter_ammo_info.weapon_pickup_amount = 6;
    level_info->weapon_info.six_shooter_ammo_info.ammo_pickup_amount = 6;

    // Shotgun (Normal ammo)
    level_info->weapon_info.shotgun_1_ammo_info.shots = 6;
    level_info->weapon_info.shotgun_1_ammo_info.damage = 3;
    level_info->weapon_info.shotgun_1_ammo_info.fire_rate = 32;
    level_info->weapon_info.shotgun_1_ammo_info.dispertion = 0; // TODO: softcode wideshot vs normal support
    level_info->weapon_info.shotgun_1_ammo_info.flash_duration = 3;

    level_info->weapon_info.shotgun_1_ammo_info.weapon_pickup_amount = 6;
    level_info->weapon_info.shotgun_1_ammo_info.ammo_pickup_amount = 6;

    level_info->weapon_info.shotgun_1_ammo_info.add_shotgun_shell = true;

    // Shotgun (Wideshot ammo)
    level_info->weapon_info.shotgun_2_ammo_info.shots = 6;
    level_info->weapon_info.shotgun_2_ammo_info.damage = 3;
    level_info->weapon_info.shotgun_2_ammo_info.fire_rate = 32;
    level_info->weapon_info.shotgun_2_ammo_info.dispertion = 0; // TODO: softcode wideshot vs normal support
    level_info->weapon_info.shotgun_2_ammo_info.flash_duration = 3;

    level_info->weapon_info.shotgun_2_ammo_info.weapon_pickup_amount = 6;
    level_info->weapon_info.shotgun_2_ammo_info.ammo_pickup_amount = 6;

    level_info->weapon_info.shotgun_2_ammo_info.add_shotgun_shell = true;

    // Grenade gun
    // Normal
    level_info->weapon_info.grenade_1_ammo_info.shots = 1;
    level_info->weapon_info.grenade_1_ammo_info.damage = 20;

    level_info->weapon_info.grenade_1_ammo_info.dispertion = 1456;

    // Super
    level_info->weapon_info.grenade_2_ammo_info.shots = 1;
    level_info->weapon_info.grenade_2_ammo_info.damage = 20;

    level_info->weapon_info.grenade_2_ammo_info.dispertion = 1456;

    // Flash
    level_info->weapon_info.grenade_3_ammo_info.shots = 1;
    level_info->weapon_info.grenade_3_ammo_info.damage = 20;

    level_info->weapon_info.grenade_3_ammo_info.dispertion = 1456;

    // Crossbow
    // Normal
    level_info->weapon_info.crossbow_1_ammo_info.shots = 1;
    level_info->weapon_info.crossbow_1_ammo_info.damage = 5;

    level_info->weapon_info.crossbow_1_ammo_info.dispertion = 1456;

    // Poison
    level_info->weapon_info.crossbow_2_ammo_info.shots = 1;
    level_info->weapon_info.crossbow_2_ammo_info.damage = 5;

    level_info->weapon_info.crossbow_2_ammo_info.dispertion = 1456;

    // Explosive
    level_info->weapon_info.crossbow_3_ammo_info.shots = 1;
    level_info->weapon_info.crossbow_3_ammo_info.damage = 5;

    level_info->weapon_info.crossbow_3_ammo_info.dispertion = 1456;


}

void SetupDefaultObjectInfoForLevel(MOD_LEVEL_INFO* level_info) {
    MOD_LEVEL_OBJECT_INFO* obj = nullptr;

    for (int i = 0; i < NUMBER_OBJECTS; i++) {
        obj = &level_info->object_info[i];
        obj->hit_points = -16384;
        obj->damage_1 = 0;
        obj->damage_2 = 0;
        obj->damage_3 = 0;
        obj->override_hit_type = false;
        obj->override_hit_type = false;
        obj->explode_immediately = false;
        obj->explode_after_death_animation = false;
        obj->hit_type = HIT_NONE;
        obj->explosive_death_only = false;
    }
}

void SetupLevelDefaults() {
    for (int i = 0; i < MOD_LEVEL_COUNT; i++) {
        if (i <= 3) {
            if (!scorpion_poison_override_found)
                game_mod_config.level_info[i].creature_info.small_scorpion_is_poisonous = false;
        }
    }
}

void SetupGlobalDefaults() {
    MOD_GLOBAL_INFO* mod_global_info = &game_mod_config.global_info;

    mod_global_info->plugin_count = 0;
    for (int i = 0; i < MAX_PLUGIN_COUNT; i++) {
        memset(mod_global_info->plugins[i], 0x00, MAX_PLUGIN_NAME_LEN);
    }
}

void LoadGameModConfigFirstPass() {
    SetupGlobalDefaults();

    char* json_buf = NULL;
    if (LoadFile("game_mod_config.json", &json_buf) <= 0) {
        Log(1, "LoadGameModConfigFirstPass: Failed to load game_mod_config.json!");
    }

    const json_t* level = nullptr;

    FURROpcode *furr_command_list = (FURROpcode * )malloc(MAX_FURR_COMMANDS * sizeof(FURROpcode));
   
    json_t* mem = NULL;
    if (json_buf) {
        mem = (json_t*)malloc(MAXIMUM_JSON_ALLOCATION_BLOCKS * sizeof(json_t));
        if (mem) {
            const json_t* root_json = json_create(json_buf, mem, MAXIMUM_JSON_ALLOCATION_BLOCKS);
            if (root_json) {
                const json_t* global = json_getProperty(root_json, "global_info");
                if (global && JSON_OBJ == json_getType(global)) {
                    MOD_GLOBAL_INFO* mod_global_info = &game_mod_config.global_info;

                    READ_JSON_UINT8(trng_version_major, global, &mod_global_info->trng_engine_version);
                    READ_JSON_UINT8(trng_version_minor, global, &mod_global_info->trng_engine_version);
                    READ_JSON_UINT8(trng_version_maintainence, global, &mod_global_info->trng_engine_version);
                    READ_JSON_UINT8(trng_version_build, global, &mod_global_info->trng_engine_version);

                    const json_t* furr_data = json_getProperty(global, "furr_data");
                    if (furr_data && JSON_OBJ == json_getType(furr_data)) {
                        const json_t* furr_flipeffects = json_getProperty(furr_data, "furr_flipeffects");
                        if (furr_flipeffects && JSON_ARRAY == json_getType(furr_flipeffects)) {
                            json_t const* furr_flipeffect;
                            int furr_flipeffect_index = 47;
                            for (furr_flipeffect = json_getChild(furr_flipeffects); furr_flipeffect != nullptr; furr_flipeffect = json_getSibling(furr_flipeffect)) {
                                if (furr_flipeffect_index > LAST_FURR_FLIPEFFECT) {
                                    Log(1, "LoadGameModConfigFirstPass: FURR flipeffect overflow!");
                                    break;
                                }
                                if (furr_flipeffect && JSON_ARRAY == json_getType(furr_flipeffect)) {
                                    json_t const* furr_flipeffect_block;
                                    int furr_flipeffect_block_index = 0;

                                    //
                                    int furr_command_count = 0;
                                    int furr_command_buffer_size = 0;

                                    // First pass to determine the required size of the bytecode buffer
                                    for (furr_flipeffect_block = json_getChild(furr_flipeffect); furr_flipeffect_block != nullptr; furr_flipeffect_block = json_getSibling(furr_flipeffect_block)) {
                                        if (furr_flipeffect_block && JSON_ARRAY == json_getType(furr_flipeffect_block)) {
                                            json_t const* furr_flipeffect_data;
                                            int furr_flipeffect_data_index = 0;
                                            // Count the data
                                            for (furr_flipeffect_data = json_getChild(furr_flipeffect_block); furr_flipeffect_data != nullptr; furr_flipeffect_data = json_getSibling(furr_flipeffect_data)) {
                                                if (furr_flipeffect_data_index == 0) {
                                                    if (furr_flipeffect_data && JSON_TEXT == json_getType(furr_flipeffect_data)) {
                                                        const char *name = furr_flipeffect_data->u.value;
                                                        int opcode_id = furr_get_opcode_for_command_string(name);
                                                        if (opcode_id >= 0) {
                                                            int furr_command_arg_count = furr_get_arg_count_for_opcode((FURROpcode)opcode_id);

                                                            furr_command_list[furr_command_count] = (FURROpcode)opcode_id;

                                                            furr_command_count++;
                                                            if (furr_command_count >= MAX_FURR_COMMANDS) {
                                                                Log(1, "LoadGameModConfigFirstPass: Exceed maximum allowed FURR commands in flipeffect!");
                                                                free(furr_command_list);
                                                                return;
                                                            }
                                                            furr_command_buffer_size += (1 + furr_command_arg_count);
                                                        } else {
                                                            Log(1, "LoadGameModConfigFirstPass: unknown FURR opcode detected!");
                                                            free(furr_command_list);
                                                            return;
                                                        }
                                                    }
                                                } else {
                                                    break;
                                                }
                                                furr_flipeffect_data_index++;
                                            }

                                        }
                                        furr_flipeffect_block_index++;
                                    }

                                    furr_flipeffect_block_index = 0;
                                    furr_allocate_flipeffect_buffer(furr_flipeffect_index, furr_command_buffer_size);


                                    //
                                    // Second pass to populate the bytecode buffer
                                    for (furr_flipeffect_block = json_getChild(furr_flipeffect); furr_flipeffect_block != nullptr; furr_flipeffect_block = json_getSibling(furr_flipeffect_block)) {
                                        if (furr_flipeffect_block && JSON_ARRAY == json_getType(furr_flipeffect_block)) {
                                            json_t const* furr_flipeffect_data;
                                            int furr_flipeffect_data_index = 0;
                                            int furr_command_arg_count = 0;

                                            // Count the data
                                            for (furr_flipeffect_data = json_getChild(furr_flipeffect_block); furr_flipeffect_data != nullptr; furr_flipeffect_data = json_getSibling(furr_flipeffect_data)) {
                                                if (furr_flipeffect_data_index != 0) {
                                                    if (furr_flipeffect_data_index <= furr_command_arg_count) {
                                                        if (furr_flipeffect_data && JSON_INTEGER == json_getType(furr_flipeffect_data)) {
                                                            int argument_value = json_getInteger(furr_flipeffect_data);
                                                            furr_add_flipeffect_token(furr_flipeffect_index, argument_value);
                                                        }
                                                        else {
                                                            furr_add_flipeffect_token(furr_flipeffect_index, 0);
                                                        }
                                                    }
                                                } else {
                                                    furr_command_arg_count = furr_get_arg_count_for_opcode(furr_command_list[furr_flipeffect_block_index]);
                                                    furr_add_flipeffect_token(furr_flipeffect_index, furr_command_list[furr_flipeffect_block_index]);
                                                }
                                                furr_flipeffect_data_index++;
                                            }
                                            
                                            // In case we're missing args
                                            if (furr_flipeffect_data_index < furr_command_arg_count) {
                                                furr_add_flipeffect_token(furr_flipeffect_index, 0);
                                                furr_flipeffect_data_index++;
                                            }

                                        }
                                        furr_flipeffect_block_index++;
                                    }
                                }
                                furr_flipeffect_index++;
                            }
                        }
                    }

                    const json_t* plugins = json_getProperty(global, "plugins");
                    if (plugins && JSON_ARRAY == json_getType(plugins)) {
                        json_t const* plugin;
                        mod_global_info->plugin_count = 0;
                        for (plugin = json_getChild(plugins); plugin != 0; plugin = json_getSibling(plugin)) {
                            if (mod_global_info->plugin_count < MAX_PLUGIN_COUNT) {
                                if (JSON_TEXT == json_getType(plugin)) {
                                    int plugin_str_length = strlen(plugin->u.value);
                                    if (plugin_str_length < MAX_PLUGIN_NAME_LEN - 1) {
                                        memcpy(mod_global_info->plugins[mod_global_info->plugin_count], plugin->u.value, plugin_str_length);
                                    } else {
                                        printf("Invalid plugin name. Too long\n");
                                    }
                                }
                            } else {
                                break;
                            }
                            mod_global_info->plugin_count++;
                        }
                    }
                }

                level = json_getProperty(root_json, "global_level_info");
            } else {
                Log(1, "LoadGameModConfigFirstPass: Not enough memory allocated for JSON buffer!");
            }
        } else {
            Log(1, "LoadGameModConfigFirstPass: Failed to allocate memory for JSON buffer!");
        }
    }

    free(furr_command_list);

    MOD_LEVEL_INFO global_level_info;

    SetupDefaultFontInfoForLevel(&global_level_info);
    SetupDefaultSlotInfoForLevel(&global_level_info);
    SetupDefaultObjectInfoForLevel(&global_level_info);

    if (level && JSON_OBJ == json_getType(level)) {
        LoadGameModLevel(level, &global_level_info);
    }
    for (int i = 0; i < MOD_LEVEL_COUNT; i++) {
        memcpy(&game_mod_config.level_info[i], &global_level_info, sizeof(MOD_LEVEL_INFO));
    }

    SetupLevelDefaults();

    if (json_buf)
        free(json_buf);

    if (mem)
        free(mem);
}

void LoadGameModConfigSecondPass() {
    char* json_buf = NULL;
    if (LoadFile("game_mod_config.json", &json_buf) <= 0) {
        Log(1, "LoadGameModConfigSecondPass: Failed to load game_mod_config.json!");
        return;
    }

    json_t *mem = NULL;

    if (json_buf) {
        mem = (json_t*)malloc(MAXIMUM_JSON_ALLOCATION_BLOCKS * sizeof(json_t));
        if (mem) {
            const json_t* root_json = json_create(json_buf, mem, MAXIMUM_JSON_ALLOCATION_BLOCKS);
            if (root_json) {
                const json_t* global = json_getProperty(root_json, "global_info");
                if (global && JSON_OBJ == json_getType(global)) {
                    MOD_GLOBAL_INFO* mod_global_info = &game_mod_config.global_info;

                    // TRNG
                    READ_JSON_UINT8(trng_version_major, global, &mod_global_info->trng_engine_version);
                    READ_JSON_UINT8(trng_version_minor, global, &mod_global_info->trng_engine_version);
                    READ_JSON_UINT8(trng_version_maintainence, global, &mod_global_info->trng_engine_version);
                    READ_JSON_UINT8(trng_version_build, global, &mod_global_info->trng_engine_version);

                    READ_JSON_BOOL(trng_flipeffects_enabled, global, mod_global_info);
                    READ_JSON_BOOL(trng_actions_enabled, global, mod_global_info);
                    READ_JSON_BOOL(trng_conditionals_enabled, global, mod_global_info);
                    READ_JSON_BOOL(trng_ng_anim_commands_enabled, global, mod_global_info);
                    READ_JSON_BOOL(trng_rollingball_extended_ocb, global, mod_global_info);
                    READ_JSON_BOOL(trng_statics_extended_ocb, global, mod_global_info);
                    READ_JSON_BOOL(trng_pushable_extended_ocb, global, mod_global_info);
                    READ_JSON_BOOL(trng_switch_extended_ocb, global, mod_global_info);
                    READ_JSON_BOOL(trng_hack_allow_meshes_with_exactly_256_vertices, global, mod_global_info);

                    // TOMO
                    READ_JSON_BOOL(tomo_enable_weather_flipeffect, global, mod_global_info);
                    READ_JSON_BOOL(tomo_swap_whitelight_for_teleporter, global, mod_global_info);

                    // Misc
                    READ_JSON_BOOL(show_lara_in_title, global, mod_global_info);
                    READ_JSON_UINT16(max_particles, global, mod_global_info);
                }

                const json_t* levels = json_getProperty(root_json, "levels");
                if (levels && JSON_ARRAY == json_getType(levels)) {
                    json_t const* level;
                    int level_index = 0;
                    for (level = json_getChild(levels); level != nullptr; level = json_getSibling(level)) {
                        if (JSON_OBJ == json_getType(level)) {
                            LoadGameModLevel(level, &game_mod_config.level_info[level_index]);
                        }
                        level_index++;
                    }
                }
            } else {
                Log(1, "LoadGameModConfigSecondPass: Not enough memory allocated for JSON buffer!");
            }
        } else {
            Log(1, "LoadGameModConfigSecondPass: Failed to allocate memory for JSON buffer!");
        }
    }

    if (json_buf)
        free(json_buf);

    if (mem)
        free(mem);
}

void T4PlusReset() {
    furr_clear_oneshot_buffer();
    ClearWeatherFX();
    InitWeatherFX();
}

void T4PlusLevelSetup(int current_level) {
    S_Reset(); // Reset audio channels.

    MOD_LEVEL_AUDIO_INFO *audio_info = get_game_mod_level_audio_info(current_level);

    SetUsingNewAudioSystem(audio_info->new_audio_system);
    SetUsingOldTriggerMode(audio_info->old_cd_trigger_system);

    NGSetup();
}

// TODO: check if the equipment commands are valid on hub re-entry.
void T4PlusEnterLevel(int current_level, bool initial_entry) {
    if (initial_entry) {
        rain_type = get_game_mod_level_misc_info(current_level)->rain_type;
        snow_type = get_game_mod_level_misc_info(current_level)->snow_type;

        MOD_EQUIPMENT_MODIFIER* equipment_modifiers = get_game_mod_level_stat_info(current_level)->equipment_modifiers;
        for (int i = 0; i < MAX_EQUIPMENT_MODIFIERS; i++) {
            if (equipment_modifiers[i].object_id != -1) {
                T4PlusSetInventoryCount(equipment_modifiers[i].object_id, equipment_modifiers[i].amount, true);
            }
            else {
                break;
            }
        }
    }
}

void T4PlusCleanup() {
    NGCleanup();

    furr_free_all_flipeffect_buffers();
}

bool is_source_trng_version_equal_or_greater_than_target(TRNG_ENGINE_VERSION source_version, TRNG_ENGINE_VERSION target_version) {
    if (source_version.trng_version_major < target_version.trng_version_major)
        return false;

    if (source_version.trng_version_minor < target_version.trng_version_minor)
        return false;

    if (source_version.trng_version_maintainence < target_version.trng_version_maintainence)
        return false;

    if (source_version.trng_version_build < target_version.trng_version_build)
        return false;

    return true;
}

bool is_mod_trng_version_equal_or_greater_than_target(
    unsigned char target_major_version,
    unsigned char target_minor_version,
    unsigned char target_maintainence_version,
    unsigned char target_build_version) {

    TRNG_ENGINE_VERSION target_version;
    target_version.trng_version_major = target_major_version;
    target_version.trng_version_minor = target_minor_version;
    target_version.trng_version_maintainence = target_maintainence_version;
    target_version.trng_version_build = target_build_version;

    return is_source_trng_version_equal_or_greater_than_target(get_game_mod_global_info()->trng_engine_version, target_version);
}