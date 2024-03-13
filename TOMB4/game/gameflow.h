#pragma once
#include "../global/types.h"

char *GetCustomStringForTextID(int id);
char *GetFixedStringForTextID(int id);
void DoGameflow();
void DoLevel(uchar Name, uchar Audio);
void DoTitle(uchar Name, uchar Audio);
void LoadGameflow();
long DoCredits();

extern GAMEFLOW* Gameflow;
extern PHD_VECTOR gfLoadCam;
extern PHD_VECTOR gfLoadTarget;
extern uchar gfLoadRoom;
extern PHD_VECTOR gfLensFlare;
extern CVECTOR gfLensFlareColour;
extern CVECTOR gfDistanceFog;
extern CVECTOR gfVolumetricFog;
extern CVECTOR gfLayer1Col;
extern CVECTOR gfLayer2Col;
extern ushort* gfStringOffset;
extern ushort* gfFilenameOffset;
extern uchar* gfScriptFile;
extern uchar* gfLanguageFile;
extern char* gfStringWad;
extern char* gfFilenameWad;
extern long gfMirrorZPlane;
extern long gfStatus;
extern ushort gfLevelFlags;
extern uchar gfCurrentLevel;
extern uchar gfLevelComplete;
extern uchar gfGameMode;
extern uchar gfMirrorRoom;
extern uchar gfNumMips;
extern uchar gfRequiredStartPos;
extern uchar gfMips[8];
extern uchar gfLevelNames[255]; // T4Plus: increased to 255
extern char gfUVRotate;
extern char gfLayer1Vel;
extern char gfLayer2Vel;

extern ulong GameTimer;
extern uchar bDoCredits;
extern char DEL_playingamefmv;
extern char skipped_level;
extern char Chris_Menu;
extern char title_controls_locked_out;

extern uint8_t gfLegend;
extern int32_t gfLegendTime;

enum gf_commands
{
	CMD_FMV = 0x80,
	CMD_LEVEL,
	CMD_TITLE,
	CMD_ENDSEQ,
	CMD_PLAYCUT,
	CMD_CUT1,
	CMD_CUT2,
	CMD_CUT3,
	CMD_CUT4,
	CMD_LAYER1,
	CMD_LAYER2,
	CMD_UVROT,
	CMD_LEGEND,
	CMD_LENSFLARE,
	CMD_MIRROR,
	CMD_FOG,
	CMD_ANIMATINGMIP,
	CMD_CAMERA,
	CMD_RESETHUB,
	CMD_KEY1,
	CMD_KEY2,
	CMD_KEY3,
	CMD_KEY4,
	CMD_KEY5,
	CMD_KEY6,
	CMD_KEY7,
	CMD_KEY8,
	CMD_KEY9,
	CMD_KEY10,
	CMD_KEY11,
	CMD_KEY12,
	CMD_PUZZLE1,
	CMD_PUZZLE2,
	CMD_PUZZLE3,
	CMD_PUZZLE4,
	CMD_PUZZLE5,
	CMD_PUZZLE6,
	CMD_PUZZLE7,
	CMD_PUZZLE8,
	CMD_PUZZLE9,
	CMD_PUZZLE10,
	CMD_PUZZLE11,
	CMD_PUZZLE12,
	CMD_PICKUP1,
	CMD_PICKUP2,
	CMD_PICKUP3,
	CMD_PICKUP4,
	CMD_EXAMINE1,
	CMD_EXAMINE2,
	CMD_EXAMINE3,
	CMD_KEYCOMBO1_1,
	CMD_KEYCOMBO1_2,
	CMD_KEYCOMBO2_1,
	CMD_KEYCOMBO2_2,
	CMD_KEYCOMBO3_1,
	CMD_KEYCOMBO3_2,
	CMD_KEYCOMBO4_1,
	CMD_KEYCOMBO4_2,
	CMD_KEYCOMBO5_1,
	CMD_KEYCOMBO5_2,
	CMD_KEYCOMBO6_1,
	CMD_KEYCOMBO6_2,
	CMD_KEYCOMBO7_1,
	CMD_KEYCOMBO7_2,
	CMD_KEYCOMBO8_1,
	CMD_KEYCOMBO8_2,
	CMD_PUZZLECOMBO1_1,
	CMD_PUZZLECOMBO1_2,
	CMD_PUZZLECOMBO2_1,
	CMD_PUZZLECOMBO2_2,
	CMD_PUZZLECOMBO3_1,
	CMD_PUZZLECOMBO3_2,
	CMD_PUZZLECOMBO4_1,
	CMD_PUZZLECOMBO4_2,
	CMD_PUZZLECOMBO5_1,
	CMD_PUZZLECOMBO5_2,
	CMD_PUZZLECOMBO6_1,
	CMD_PUZZLECOMBO6_2,
	CMD_PUZZLECOMBO7_1,
	CMD_PUZZLECOMBO7_2,
	CMD_PUZZLECOMBO8_1,
	CMD_PUZZLECOMBO8_2,
	CMD_PICKUPCOMBO1_1,
	CMD_PICKUPCOMBO1_2,
	CMD_PICKUPCOMBO2_1,
	CMD_PICKUPCOMBO2_2,
	CMD_PICKUPCOMBO3_1,
	CMD_PICKUPCOMBO3_2,
	CMD_PICKUPCOMBO4_1,
	CMD_PICKUPCOMBO4_2,
};

enum gf_strings	//auto generated from the script compiler
{
	TXT_Cambodia_1984,
	TXT_Egypt_present_day,
	TXT_Angkor_Wat,
	TXT_Race_For_The_Iris,
	TXT_The_Tomb_Of_Seth,
	TXT_Burial_Chambers,
	TXT_Valley_Of_The_Kings,
	TXT_KV5,
	TXT_Temple_Of_Karnak,
	TXT_The_Great_Hypostyle_Hall,
	TXT_Sacred_Lake,
	TXT_Lake_2,
	TXT_Tomb_Of_Semerkhet,
	TXT_Guardian_Of_Semerkhet,
	TXT_Desert_Railroad,
	TXT_Alexandria,
	TXT_Coastal_Ruins,
	TXT_Pharos_Temple_Of_Isis,
	TXT_Cleopatras_Palaces,
	TXT_Catacombs,
	TXT_Temple_Of_Poseidon,
	TXT_The_Lost_Library,
	TXT_Hall_Of_Demetrius,
	TXT_City_Of_The_Dead,
	TXT_Trenches,
	TXT_Chambers_Of_Tulun,
	TXT_Citadel_Gate,
	TXT_Street_Bazaar,
	TXT_Citadel,
	TXT_The_Sphinx_Complex,
	TXT_The_Valley_Temple,
	TXT_Underneath_The_Sphinx,
	TXT_Menkaures_Pyramid,
	TXT_Inside_Menkaures_Pyramid,
	TXT_The_Mastabas,
	TXT_The_Great_Pyramid,
	TXT_Khufus_Queens_Pyramids,
	TXT_Inside_The_Great_Pyramid,
	TXT_Temple_Of_Horus,
	// Times Strings Start
	TXT_The_Times_Office,
	TXT_The_Times_Exclusive,
	TXT_The_Gold_Mask,
	// Times Strings End
	TXT_Unlimited_s,
	TXT_USE,
	TXT_CHOOSE_AMMO,
	TXT_COMBINE,
	TXT_SEPERATE,
	TXT_EQUIP,
	TXT_COMBINE_WITH,
	TXT_LOAD_GAME,
	TXT_SAVE_GAME,
	TXT_EXAMINE,
	TXT_More,
	TXT_Select_Ammo,
	TXT_Select_Option,
	TXT_Combine,
	TXT_Uzi,
	TXT_Pistols,
	TXT_Shotgun,
	TXT_Revolver,
	TXT_Revolver_LaserSight,
	TXT_Crossbow,
	TXT_Crossbow_LaserSight,
	TXT_Grenade_Gun,
	TXT_Shotgun_Normal_Ammo,
	TXT_Shotgun_Wideshot_Ammo,
	TXT_Grenadegun_Normal_Ammo,
	TXT_Grenadegun_Super_Ammo,
	TXT_Grenadegun_Flash_Ammo,
	TXT_Crossbow_Normal_Ammo,
	TXT_Crossbow_Poison_Ammo,
	TXT_Crossbow_Explosive_Ammo,
	TXT_Revolver_Ammo,
	TXT_Uzi_Ammo,
	TXT_Pistol_Ammo,
	TXT_LaserSight,
	TXT_Large_Medipack,
	TXT_Small_Medipack,
	TXT_Binoculars,
	TXT_Flares,
	TXT_Compass,
	TXT_Load,
	TXT_Save,
	TXT_Small_Waterskin_Empty,
	TXT_Small_Waterskin,
	TXT_Small_Waterskin2,
	TXT_Small_Waterskin3,
	TXT_Large_WaterSkin_Empty,
	TXT_Large_WaterSkin,
	TXT_Large_WaterSkin2,
	TXT_Large_WaterSkin3,
	TXT_Large_WaterSkin4,
	TXT_Large_WaterSkin5,
	TXT_Crowbar,
	TXT_QuestItem1,
	TXT_QuestItem2,
	TXT_QuestItem3,
	TXT_QuestItem4,
	TXT_QuestItem5,
	TXT_QuestItem6,
	TXT_Mechanical_Scarab,
	TXT_Mechanical_Scarab_With,
	TXT_Winding_Key,
	TXT_Armoury_Key,
	TXT_The_Guards_Keys,
	TXT_Scrap_Of_Paper,
	TXT_Stone_of_Maat,
	TXT_Stone_of_Khepri,
	TXT_Stone_of_Atum,
	TXT_Stone_of_Re,
	TXT_Northern_Shaft_Key,
	TXT_Southern_Shaft_Key,
	TXT_Eastern_Shaft_Key,
	TXT_Black_Beetle,
	TXT_Broken_Beetle,
	TXT_Broken_Glasses,
	TXT_Fire_Circle_Scroll,
	TXT_Ignition_Key,
	TXT_Music_Scroll,
	TXT_Coin_Piece,
	TXT_Eye_Of_Horus,
	TXT_Eye_Piece,
	TXT_The_Timeless_Sands,
	TXT_The_Hand_Of_Orion,
	TXT_The_Hand_Of_Sirius,
	TXT_Scarab_Talisman,
	TXT_The_Golden_Serpent,
	TXT_Golden_Skull,
	TXT_Metal_Blade,
	TXT_Wooden_Handle,
	TXT_Silver_Key,
	TXT_Western_Shaft_Key,
	TXT_Shovel,
	TXT_Holy_Scripture,
	TXT_Canopic_Jar_1,
	TXT_Canopic_Jar_2,
	TXT_Sun_Goddess,
	TXT_Sun_Disk,
	TXT_Sun_Talisman,
	TXT_Cartouche_Piece_1,
	TXT_Cartouche_Piece_2,
	TXT_Ba_Cartouche,
	TXT_Ra_Cartouche,
	TXT_Golden_Vraeus,
	TXT_Guardian_Key,
	TXT_Hypostyle_Key,
	TXT_Temple_Key,
	TXT_Nitrous_Oxide_Feeder,
	TXT_Valve_Pipe,
	TXT_Nitrous_Oxide_Cannister,
	TXT_Car_Jack,
	TXT_Car_Jack_Body,
	TXT_Handle,
	TXT_Roof_Key,
	TXT_Weapon_Code_Key,
	TXT_Mine_Detonator,
	TXT_Mine_Detonator_Body,
	TXT_Mine_Position_Data,
	TXT_Trident,
	TXT_Golden_Star,
	TXT_Hook_and_Pole,
	TXT_Wall_Hook,
	TXT_Broken_Handle,
	TXT_Hathor_Effigy,
	TXT_Ornate_Handle,
	TXT_Portal_Guardian,
	TXT_Horsemans_Gem,
	TXT_Pharos_Knot,
	TXT_Pharos_Pillar,
	TXT_Token,
	TXT_Gate_Key,
	TXT_The_Rules_of_Senet,
	TXT_Bag_of_Sand,
	TXT_Jerrycan,
	TXT_Yes,
	TXT_No,
	TXT_Load_Game,
	TXT_New_Game,
	TXT_Paused,
	TXT_Select_Game_To_Load,
	TXT_Select_Game_To_Save,
	TXT_GAME_OVER,
	TXT_Save_Game,
	TXT_Exit_to_Title,
	TXT_DEMO_MODE,
	TXT_Current_Location,
	TXT_Statistics,
	TXT_Distance_Travelled,
	TXT_Ammo_Used,
	TXT_Secrets_Found,
	TXT_Location,
	TXT_Health_Packs_Used,
	TXT_Time_Taken,
	TXT_days,
	TXT_of,
	TXT_Action,
	TXT_Draw_Weapon,
	TXT_Jump,
	TXT_Roll,
	TXT_Walk,
	TXT_Look,
	TXT_Duck,
	TXT_Dash,
	TXT_Inventory,
	TXT_RULES1,
	TXT_RULES2,
	TXT_PETEPOO,

	/* -------- PlayStation strings */

	TXT_BSELECT,
	TXT_BCANCEL,
	TXT_BGOBACK,
	TXT_BOK,
	TXT_CANCELB,
	TXT_MEMCARD,
	TXT_INSERT,
	TXT_CHECKING,
	TXT_FORMAT,
	TXT_LOADING,
	TXT_SAVING,
	TXT_FORMATTING,
	TXT_OVERWRITE,
	TXT_UNFORMATTED,
	TXT_NOSPACE,
	TXT_NOGAMES,
	TXT_LOADING2,
	TXT_Load_OK,
	TXT_Saved_OK,
	TXT_Format_OK,
	TXT_Load_Failed,
	TXT_Save_Failed,
	TXT_Format_Failed,
	TXT_Empty,
	TXT_Controller_Removed,
	TXT_Resume,
	TXT_Quit,
	TXT_Game_Settings,
	TXT_Control_Options,
	TXT_Are_you_sure_you_want_to,
	TXT_Screen_Adjust,
	TXT_FXVOL,
	TXT_MUSICVOL,
	TXT_Use_directional_buttons,
	TXT_Configure_Controls,
	TXT_Configuration_n,
	TXT_Vibration_On,
	TXT_Vibration_Off,
	TXT_Manual_Targeting,
	TXT_Automatic_Targeting,
	TXT_PAD,
	TXT_PAD2,
	TXT_PSX_Programmers,
	TXT_Additional_Programmers,
	TXT_AI_Programming,
	TXT_Animators,
	TXT_Level_Designers,
	TXT_FMV_Sequences,
	TXT_Additional_Artwork,
	TXT_Music_Sound_FX,
	TXT_Original_Story,
	TXT_Script,
	TXT_Producer,
	TXT_QA,
	TXT_Executive_Producers,
	TXT_Additional_Sound_FX,
	TXT_TEAM1,
	TXT_TEAM2,
	TXT_TEAM3,
	TXT_TEAM4,
	TXT_TEAM5,
	TXT_TEAM6,
	TXT_TEAM8,
	TXT_TEAM7,
	TXT_TEAM9,
	TXT_TEAM10,
	TXT_TEAM11,
	TXT_TEAM12,
	TXT_TEAM13,
	TXT_TEAM14,
	TXT_TEAM15,
	TXT_TEAM16,
	TXT_TEAM17,
	TXT_TEAM18,
	TXT_TEAM19,
	TXT_TEAM20,
	TXT_TEAM21,
	TXT_TEAM22,
	TXT_TEAM23,
	TXT_TEAM24,
	TXT_TEAM25,
	TXT_TEAM26,
	TXT_TEAM27,
	TXT_TEAM28,
	TXT_TEAM29,
	TXT_TEAM30,
	TXT_TEAM31,
	TXT_TEAM32,
	TXT_TEAM33,
	TXT_TEAM34,
	TXT_TEAM35,
	TXT_TEAM36,
	TXT_TEAM37,
	TXT_TEAM38,
	TXT_TEAM39,
	TXT_TEAM40,

	/* -------- PC strings */

	TXT_PC_Programmer,
	TXT_Programmers,
	TXT_Additional_Programming,
	TXT_Resume2,
	TXT_Options,
	TXT_Empty_Slot,
	TXT_Music_Volume,
	TXT_SFX_Volume,
	TXT_Sound_Quality,
	TXT_Low,
	TXT_Medium,
	TXT_High,
	TXT_Targeting,
	TXT_Manual,
	TXT_Automatic,
	TXT_Graphics_Adapter,
	TXT_Output_Settings,
	TXT_Output_Resolution,
	TXT_Texture_Bit_Depth,
	TXT_OK,
	TXT_Cancel,
	TXT_Hardware_Acceleration,
	TXT_Software_Mode,
	TXT_Volumetric_FX,
	TXT_Bilinear_Filtering,
	TXT_Bump_Mapping,
	TXT_Low_Resolution_Textures,
	TXT_Low_Resolution_Bump_Maps,
	TXT_Sound_Device,
	TXT_Disable,
	TXT_Bit,
	TXT_Full_Screen,
	TXT_Windowed,
	TXT_Render_Options,
	TXT_No_Sound_Card_Installed,
	TXT_Failed_To_Setup_DirectX,
	TXT_Exit,
	TXT_Control_Configuration,
	TXT_Use_Flare,
	TXT_Control_Method,
	TXT_Mouse,
	TXT_Keyboard,
	TXT_Joystick,
	TXT_Waiting,
	TXT_Reset,
	TXT_Save_Settings,
	TXT_Saved_OK2,
	TXT_Step_Left,
	TXT_Step_Right,
	TXT_Play,
	TXT_Setup,
	TXT_Install,
	TXT_Uninstall,
	TXT_ReadMe,
	TXT_Demo_Mode_Esc_To_Exit,
	TXT_Select_Level,
	TXT_No_FMV,
	// Level Editor Strings Start
	TXT_OEM1,
	// Level Editor Strings End
	TXT_THE_LAST_STRING_ENTRY,
	TXT_NUM_STRINGS
};
