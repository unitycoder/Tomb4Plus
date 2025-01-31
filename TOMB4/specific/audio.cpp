#include <stdio.h>
#include <string.h>

#include "../tomb4/pch.h"
#include "audio.h"
#include "dxsound.h"
#include "file.h"
#include "function_stubs.h"
#include "dxshell.h"
#include "../game/control.h"
#include "LoadSave.h"
#include "winmain.h"
#include "platform.h"
#include "cmdline.h"

const char *LastRevelationTrackFileNames[] = 
{
	"044_attack_part_i.wav",
	"008_voncroy9a.wav",
	"100_attack_part_ii.wav",
	"010_voncroy10.wav",
	"015_voncroy14.wav",
	"073_secret.wav",
	"109_lyre_01.wav",
	"042_action_part_iv.wav",
	"043_action_part_v.wav",
	"030_voncroy30.wav",
	"012_voncroy11b.wav",
	"011_voncroy11a.wav",
	"063_misc_inc_01.wav",
	"014_voncroy13b.wav",
	"111_charmer.wav",
	"025_voncroy24b.wav",
	"023_voncroy23.wav",
	"006_voncroy7.wav",
	"024_voncroy24a.wav",
	"110_lyre_02.wav",
	"020_voncroy19.wav",
	"034_voncroy34.wav",
	"054_general_part_ii.wav",
	"036_voncroy36.wav",
	"004_voncroy5.wav",
	"035_voncroy35.wav",
	"027_voncroy27.wav",
	"053_general_part_i.wav",
	"022_voncroy22b.wav",
	"028_voncroy28_l11.wav",
	"003_voncroy4.wav",
	"001_voncroy2.wav",
	"041_action_part_iii.wav",
	"057_general_part_v.wav",
	"018_voncroy17.wav",
	"064_misc_inc_02.wav",
	"033_voncroy33.wav",
	"031_voncroy31_l12.wav",
	"032_voncroy32_l13.wav",
	"016_voncroy15.wav",
	"065_misc_inc_03.wav",
	"040_action_part_ii.wav",
	"112_gods_part_iv.wav",
	"029_voncroy29.wav",
	"007_voncroy8.wav",
	"013_voncroy12_13a_lara4.wav",
	"009_voncroy9b_lara3.wav",
	"081_dig.wav",
	"085_intro.wav",
	"071_ominous_part_i.wav",
	"095_phildoor.wav",
	"061_in_the_pyramid_part_i.wav",
	"050_underwater_find_part_i.wav",
	"058_gods_part_i.wav",
	"005_voncroy6_lara2.wav",
	"045_authentic_tr.wav",
	"060_gods_part_iii.wav",
	"055_general_part_iii.wav",
	"059_gods_part_ii.wav",
	"068_mystery_part_ii.wav",
	"076_captain2.wav",
	"019_lara6_voncroy18.wav",
	"002_voncroy3.wav",
	"066_misc_inc_04.wav",
	"067_mystery_part_i.wav",
	"038_a_short_01.wav",
	"088_key.wav",
	"017_voncroy16_lara5.wav",
	"026_vc25_l9_vc26_l10.wav",
	"056_general_part_iv.wav",
	"021_vc20_l7_vc21_l8_vc22a.wav",
	"096_sarcoph.wav",
	"087_jeepb.wav",
	"091_minilib1.wav",
	"086_jeepa.wav",
	"051_egyptian_mood_part_i.wav",
	"078_croywon.wav",
	"092_minilib2.wav",
	"083_horus.wav",
	"049_close_to_the_end_part_ii.wav",
	"037_vc37_l15_vc38.wav",
	"097_scorpion.wav",
	"089_larawon.wav",
	"094_minilib4.wav",
	"098_throne.wav",
	"048_close_to_the_end.wav",
	"070_mystery_part_iv.wav",
	"093_minilib3.wav",
	"072_puzzle_part_i.wav",
	"074_backpack.wav",
	"069_mystery_part_iii.wav",
	"052_egyptian_mood_part_ii.wav",
	"084_inscrip.wav",
	"099_whouse.wav",
	"047_boss_02.wav",
	"080_crypt2.wav",
	"090_libend.wav",
	"046_boss_01.wav",
	"062_jeep_thrills_max.wav",
	"079_crypt1.wav",
	"082_finale.wav",
	"075_captain1.wav",
	"105_a5_battle.wav",
	"077_crocgod.wav",
	"039_tr4_title_q10.wav",
	"108_a8_coastal.wav",
	"107_a7_train+.wav",
	"101_a1_in_dark.wav",
	"102_a2_in_drips.wav",
	"104_a4_weird1.wav",
	"106_a6_out_day.wav",
	"103_a3_out_night.wav"
};

// TRLE: track count increased
const char* LevelEditorTrackFileNames[] =
{
#ifdef MA_AUDIO_ENGINE
	"000",
	"001",
	"002",
	"003",
	"004",
	"005",
	"006",
	"007",
	"008",
	"009",
	"010",
	"011",
	"012",
	"013",
	"014",
	"015",
	"016",
	"017",
	"018",
	"019",
	"020",
	"021",
	"022",
	"023",
	"024",
	"025",
	"026",
	"027",
	"028",
	"029",
	"030",
	"031",
	"032",
	"033",
	"034",
	"035",
	"036",
	"037",
	"038",
	"039",
	"040",
	"041",
	"042",
	"043",
	"044",
	"045",
	"046",
	"047",
	"048",
	"049",
	"050",
	"051",
	"052",
	"053",
	"054",
	"055",
	"056",
	"057",
	"058",
	"059",
	"060",
	"061",
	"062",
	"063",
	"064",
	"065",
	"066",
	"067",
	"068",
	"069",
	"070",
	"071",
	"072",
	"073",
	"074",
	"075",
	"076",
	"077",
	"078",
	"079",
	"080",
	"081",
	"082",
	"083",
	"084",
	"085",
	"086",
	"087",
	"088",
	"089",
	"090",
	"091",
	"092",
	"093",
	"094",
	"095",
	"096",
	"097",
	"098",
	"099",
	"100",
	"101",
	"102",
	"103",
	"104",
	"105",
	"106",
	"107",
	"108",
	"109",
	"110",
	"111",
	"112",
	"113",
	"114",
	"115",
	"116",
	"117",
	"118",
	"119",
	"120",
	"121",
	"122",
	"123",
	"124",
	"125",
	"126",
	"127",
	"128",
	"129",
	"130",
	"131",
	"132",
	"133",
	"134",
	"135",
	"136",
	"137",
	"138",
	"139",
	"140",
	"141",
	"142",
	"143",
	"144",
	"145",
	"146",
	"147",
	"148",
	"149",
	"150",
	"151",
	"152",
	"153",
	"154",
	"155",
	"156",
	"157",
	"158",
	"159",
	"160",
	"161",
	"162",
	"163",
	"164",
	"165",
	"166",
	"167",
	"168",
	"169",
	"170",
	"171",
	"172",
	"173",
	"174",
	"175",
	"176",
	"177",
	"178",
	"179",
	"180",
	"181",
	"182",
	"183",
	"184",
	"185",
	"186",
	"187",
	"188",
	"189",
	"190",
	"191",
	"192",
	"193",
	"194",
	"195",
	"196",
	"197",
	"198",
	"199",
	"200",
	"201",
	"202",
	"203",
	"204",
	"205",
	"206",
	"207",
	"208",
	"209",
	"210",
	"211",
	"212",
	"213",
	"214",
	"215",
	"216",
	"217",
	"218",
	"219",
	"220",
	"221",
	"222",
	"223",
	"224",
	"225",
	"226",
	"227",
	"228",
	"229",
	"230",
	"231",
	"232",
	"233",
	"234",
	"235",
	"236",
	"237",
	"238",
	"239",
	"240",
	"241",
	"242",
	"243",
	"244",
	"245",
	"246",
	"247",
	"248",
	"249",
	"250",
	"251",
	"252",
	"253",
	"254",
	"255",
	"256"
#else
	"000.wav",
	"001.wav",
	"002.wav",
	"003.wav",
	"004.wav",
	"005.wav",
	"006.wav",
	"007.wav",
	"008.wav",
	"009.wav",
	"010.wav",
	"011.wav",
	"012.wav",
	"013.wav",
	"014.wav",
	"015.wav",
	"016.wav",
	"017.wav",
	"018.wav",
	"019.wav",
	"020.wav",
	"021.wav",
	"022.wav",
	"023.wav",
	"024.wav",
	"025.wav",
	"026.wav",
	"027.wav",
	"028.wav",
	"029.wav",
	"030.wav",
	"031.wav",
	"032.wav",
	"033.wav",
	"034.wav",
	"035.wav",
	"036.wav",
	"037.wav",
	"038.wav",
	"039.wav",
	"040.wav",
	"041.wav",
	"042.wav",
	"043.wav",
	"044.wav",
	"045.wav",
	"046.wav",
	"047.wav",
	"048.wav",
	"049.wav",
	"050.wav",
	"051.wav",
	"052.wav",
	"053.wav",
	"054.wav",
	"055.wav",
	"056.wav",
	"057.wav",
	"058.wav",
	"059.wav",
	"060.wav",
	"061.wav",
	"062.wav",
	"063.wav",
	"064.wav",
	"065.wav",
	"066.wav",
	"067.wav",
	"068.wav",
	"069.wav",
	"070.wav",
	"071.wav",
	"072.wav",
	"073.wav",
	"074.wav",
	"075.wav",
	"076.wav",
	"077.wav",
	"078.wav",
	"079.wav",
	"080.wav",
	"081.wav",
	"082.wav",
	"083.wav",
	"084.wav",
	"085.wav",
	"086.wav",
	"087.wav",
	"088.wav",
	"089.wav",
	"090.wav",
	"091.wav",
	"092.wav",
	"093.wav",
	"094.wav",
	"095.wav",
	"096.wav",
	"097.wav",
	"098.wav",
	"099.wav",
	"100.wav",
	"101.wav",
	"102.wav",
	"103.wav",
	"104.wav",
	"105.wav",
	"106.wav",
	"107.wav",
	"108.wav",
	"109.wav",
	"110.wav",
	"111.wav",
	"112.wav",
	"113.wav",
	"114.wav",
	"115.wav",
	"116.wav",
	"117.wav",
	"118.wav",
	"119.wav",
	"120.wav",
	"121.wav",
	"122.wav",
	"123.wav",
	"124.wav",
	"125.wav",
	"126.wav",
	"127.wav",
	"128.wav",
	"129.wav",
	"130.wav",
	"131.wav",
	"132.wav",
	"133.wav",
	"134.wav",
	"135.wav",
	"136.wav",
	"137.wav",
	"138.wav",
	"139.wav",
	"140.wav",
	"141.wav",
	"142.wav",
	"143.wav",
	"144.wav",
	"145.wav",
	"146.wav",
	"147.wav",
	"148.wav",
	"149.wav",
	"150.wav",
	"151.wav",
	"152.wav",
	"153.wav",
	"154.wav",
	"155.wav",
	"156.wav",
	"157.wav",
	"158.wav",
	"159.wav",
	"160.wav",
	"161.wav",
	"162.wav",
	"163.wav",
	"164.wav",
	"165.wav",
	"166.wav",
	"167.wav",
	"168.wav",
	"169.wav",
	"170.wav",
	"171.wav",
	"172.wav",
	"173.wav",
	"174.wav",
	"175.wav",
	"176.wav",
	"177.wav",
	"178.wav",
	"179.wav",
	"180.wav",
	"181.wav",
	"182.wav",
	"183.wav",
	"184.wav",
	"185.wav",
	"186.wav",
	"187.wav",
	"188.wav",
	"189.wav",
	"190.wav",
	"191.wav",
	"192.wav",
	"193.wav",
	"194.wav",
	"195.wav",
	"196.wav",
	"197.wav",
	"198.wav",
	"199.wav",
	"200.wav",
	"201.wav",
	"202.wav",
	"203.wav",
	"204.wav",
	"205.wav",
	"206.wav",
	"207.wav",
	"208.wav",
	"209.wav",
	"210.wav",
	"211.wav",
	"212.wav",
	"213.wav",
	"214.wav",
	"215.wav",
	"216.wav",
	"217.wav",
	"218.wav",
	"219.wav",
	"220.wav",
	"221.wav",
	"222.wav",
	"223.wav",
	"224.wav",
	"225.wav",
	"226.wav",
	"227.wav",
	"228.wav",
	"229.wav",
	"230.wav",
	"231.wav",
	"232.wav",
	"233.wav",
	"234.wav",
	"235.wav",
	"236.wav",
	"237.wav",
	"238.wav",
	"239.wav",
	"240.wav",
	"241.wav",
	"242.wav",
	"243.wav",
	"244.wav",
	"245.wav",
	"246.wav",
	"247.wav",
	"248.wav",
	"249.wav",
	"250.wav",
	"251.wav",
	"252.wav",
	"253.wav",
	"254.wav",
	"255.wav",
	"256.wav"
#endif
};

#pragma warning(push)
#pragma warning(disable : 4838)
#pragma warning(disable : 4309)
static char source_wav_format[50] =
{
	2, 0, 2, 0, 68, 172, 0, 0, 71, 173, 0, 0, 0, 8, 4, 0, 32, 0, 244, 7, 7, 0, 0, 1, 0, 0, 0,
	2, 0, 255, 0, 0, 0, 0, 192, 0, 64, 0, 240, 0, 0, 0, 204, 1, 48, 255, 136, 1, 24, 255
};
#pragma warning(pop)

#if !defined(MA_AUDIO_SAMPLES) || !defined(MA_AUDIO_ENGINE)
HACMDRIVER hACMDriver;
#endif

uchar* wav_file_buffer = 0;
uchar* ADPCMBuffer = 0;
bool acm_ready = 0;

long LegacyTrack = -1;
long LegacyTrackFlag = 7;

#ifndef MA_AUDIO_ENGINE

static LPDIRECTSOUNDBUFFER DSBuffer = 0;
static LPDIRECTSOUNDNOTIFY DSNotify = 0;
static ACMSTREAMHEADER StreamHeaders[4];
static HACMDRIVERID hACMDriverID = 0;
static HACMSTREAM hACMStream = 0;
static HANDLE NotifyEventHandles[2];
static HANDLE NotificationThreadHandle = 0;
static FILE* audio_stream_fp;
static CRITICAL_SECTION audio_cs;
static uchar* audio_fp_write_ptr = 0;
static uchar* pAudioWrite = 0;
static ulong AudioBytes = 0;
static long audio_buffer_size = 0;
static long CurrentNotify = 0;
static long NotifySize = 0;
static long NextWriteOffset = 0;
static long auido_play_mode = 0;
static long audio_counter = 0;
static volatile bool reading_audio_file = 0;
static volatile bool continue_reading_audio_file = 0;

void OpenStreamFile(char* name)
{
	__try
	{
		EnterCriticalSection(&audio_cs);
	}
	__finally
	{
		LeaveCriticalSection(&audio_cs);
	}

	audio_stream_fp = FileOpen(name);

	if (!audio_stream_fp)
	{
		Log(1, "%s - Not Found", name);
		return;
	}

	fseek(audio_stream_fp, 90, SEEK_SET);
	audio_fp_write_ptr = wav_file_buffer;
	memset(wav_file_buffer, 0, 0x37000);

	if (fread(wav_file_buffer, 1, 0x37000, audio_stream_fp) < 0x37000 && auido_play_mode == 1)
	{
		fseek(audio_stream_fp, 90, SEEK_SET);
		Log(0, "FileReset In OpenStreamFile");
	}
}

void GetADPCMData()
{
	if (!audio_stream_fp)
		return;

	memset(audio_fp_write_ptr, 0, 0x5800);

	if (fread(audio_fp_write_ptr, 1, 0x5800, audio_stream_fp) < 0x5800 && auido_play_mode == 1)
	{
		Log(0, "FileReset In GetADPCMData");
		fseek(audio_stream_fp, 90, SEEK_SET);
	}

	audio_fp_write_ptr += 0x5800;

	if ((long)audio_fp_write_ptr >= long(wav_file_buffer + 0x37000))
		audio_fp_write_ptr = wav_file_buffer;
}

void ACMSetVolume()
{
	long volume;

	if (!MusicVolume)
		volume = -10000;
	else
		volume = -4000 * (100 - MusicVolume) / 100;

	if (DSBuffer)
		DSBuffer->SetVolume(volume);
}

void ACMEmulateCDPlay(long track, long mode)
{
	char name[256];

	__try
	{
		EnterCriticalSection(&audio_cs);
	}
	__finally
	{
		LeaveCriticalSection(&audio_cs);
	}

	if (get_game_mod_global_info()->tr_level_editor)
	{
		wsprintf(name, "audio\\%s", LevelEditorTrackFileNames[track]);
	} else {
		wsprintf(name, "audio\\%s", LastRevelationTrackFileNames[track]);
	}

	if (mode)
		Log(8, "Playing %s %s %d", name, "Looped", track);
	else
		Log(8, "Playing %s %s %d", name, "", track);

	LegacyTrack = track;
	LegacyTrackFlag = 6;
	auido_play_mode = mode;
	OpenStreamFile(name);

	if (!audio_stream_fp)
		return;

	memcpy(ADPCMBuffer, audio_fp_write_ptr, 0x5800);
	GetADPCMData();
	DXAttempt(DSBuffer->Lock(0, audio_buffer_size, (LPVOID*)&pAudioWrite, &AudioBytes, 0, 0, 0));
	acmStreamConvert(hACMStream, &StreamHeaders[0], ACM_STREAMCONVERTF_BLOCKALIGN | ACM_STREAMCONVERTF_START);
	memcpy(ADPCMBuffer, audio_fp_write_ptr, 0x5800);
	GetADPCMData();
	acmStreamConvert(hACMStream, &StreamHeaders[1], ACM_STREAMCONVERTF_BLOCKALIGN);
	DXAttempt(DSBuffer->Unlock(pAudioWrite, audio_buffer_size, 0, 0));
	CurrentNotify = 2;
	NextWriteOffset = 2 * NotifySize;
	ACMSetVolume();
	DSBuffer->Play(0, 0, DSBPLAY_LOOPING);
}

BOOL __stdcall ACMEnumCallBack(HACMDRIVERID hadid, DWORD_PTR dwInstance, DWORD fdwSupport)
{
	ACMDRIVERDETAILS driver;

	memset(&driver, 0, sizeof(driver));
	driver.cbStruct = sizeof(ACMDRIVERDETAILS);
	acmDriverDetails(hadid, &driver, 0);

	if (strcmp(driver.szShortName, "MS-ADPCM"))
		return 1;

	hACMDriverID = hadid;
	return 0;
}

long ACMSetupNotifications()
{
	DSBPOSITIONNOTIFY posNotif[5];
	ulong ThreadId;
	long result;

	NotifyEventHandles[0] = CreateEvent(0, 0, 0, 0);
	NotifyEventHandles[1] = CreateEvent(0, 0, 0, 0);
	posNotif[0].dwOffset = NotifySize;
	posNotif[0].hEventNotify = NotifyEventHandles[0];
	Log(8, "Set notifies for position %lu", posNotif[0].dwOffset);

	for (int i = 1; i < 4; i++)
	{
		posNotif[i].dwOffset = NotifySize + posNotif[i - 1].dwOffset;
		posNotif[i].hEventNotify = NotifyEventHandles[0];
		Log(8, "Set notifies for positions %lu", posNotif[i].dwOffset);
	}

	posNotif[3].dwOffset--;
	posNotif[4].dwOffset = -1;
	posNotif[4].hEventNotify = NotifyEventHandles[1];
	NotificationThreadHandle = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ACMHandleNotifications, 0, 0, &ThreadId);

	if (!NotificationThreadHandle)
		Log(1, "Create Notification Thread failed");

	result = DSNotify->SetNotificationPositions(5, posNotif);

	if (result != DS_OK)
	{
		CloseHandle(NotifyEventHandles[0]);
		CloseHandle(NotifyEventHandles[1]);
		NotifyEventHandles[1] = 0;
		NotifyEventHandles[0] = 0;
	}
	else
		Log(8, "Setup Notifications OK");

	return result;
}

void FillADPCMBuffer(char* p, long track)
{
	reading_audio_file = 1;

	__try
	{
		EnterCriticalSection(&audio_cs);
	}
	__finally
	{
		LeaveCriticalSection(&audio_cs);
	}

	if (!audio_stream_fp)
	{
		reading_audio_file = 0;
		continue_reading_audio_file = 0;
		return;
	}

	if (track != LegacyTrack || track == -1)
	{
		Log(0, "Not Current Track %d", track);
		reading_audio_file = 0;
		continue_reading_audio_file = 0;
		return;
	}

	memset(p, 0, 0x5800);

	if (!audio_stream_fp)
	{
		reading_audio_file = 0;
		continue_reading_audio_file = 0;
		return;
	}

	fread(p, 1, 0x5800, audio_stream_fp);

	if (audio_stream_fp && feof(audio_stream_fp))
	{
		if (auido_play_mode == 1)
			fseek(audio_stream_fp, 90, SEEK_SET);
		else
		{
			audio_counter++;

			if (audio_counter > 8)
			{
				audio_counter = 0;

				if (auido_play_mode == 2)
				{
					reading_audio_file = 0;
					continue_reading_audio_file = 0;
					S_CDStop();
					return;
				}

				if (CurrentAtmosphere && !IsAtmospherePlaying)
				{
					reading_audio_file = 0;
					continue_reading_audio_file = 0;
					S_CDStop();
					S_CDPlay(CurrentAtmosphere, 1);
					return;
				}
			}
		}
	}

	reading_audio_file = 0;
	continue_reading_audio_file = 1;
}

long ACMHandleNotifications()
{
	char* write;
	ulong wait, bytes;

	while ((wait = WaitForMultipleObjects(2, NotifyEventHandles, 0, INFINITE)) != WAIT_FAILED)
	{
		EnterCriticalSection(&audio_cs);

		if (!wait && DSBuffer)
		{
			memcpy(ADPCMBuffer, audio_fp_write_ptr, 0x5800);

			if (LegacyTrack == -1)
				memset(ADPCMBuffer, 0, 0x5800);
			else
				FillADPCMBuffer((char*)audio_fp_write_ptr, LegacyTrack);

			if (continue_reading_audio_file)
			{
				audio_fp_write_ptr += 0x5800;

				if ((long)audio_fp_write_ptr >= long(wav_file_buffer + 0x37000))
					audio_fp_write_ptr = wav_file_buffer;

				DSBuffer->Lock(NextWriteOffset, NotifySize, (LPVOID*)&write, &bytes, 0, 0, 0);
				acmStreamConvert(hACMStream, &StreamHeaders[CurrentNotify], ACM_STREAMCONVERTF_BLOCKALIGN);
				DSBuffer->Unlock(&write, bytes, 0, 0);
				NextWriteOffset += bytes;

				if (NextWriteOffset >= audio_buffer_size)
					NextWriteOffset -= audio_buffer_size;

				CurrentNotify = (CurrentNotify + 1) & 3;
			}
		}

		LeaveCriticalSection(&audio_cs);

		if (!DSBuffer)
			break;
	}

	return DS_OK;
}

bool ACMInit()
{
	DSBUFFERDESC desc;
	static WAVEFORMATEX wav_format;
	static ulong StreamSize;
	ulong version, pMetric;

	version = acmGetVersion();
	InitializeCriticalSection(&audio_cs);
	acm_ready = 0;
	Log(8, "ACM Version %u.%.02u", ((version >> 16) & 0xFFFF) >> 8, (version >> 16) & 0xFF);
	acmDriverEnum(ACMEnumCallBack, 0, 0);

	if (!hACMDriverID)
	{
		Log(1, "*** Unable To Locate MS-ADPCM Driver ***");
		return 0;
	}

	if (acmDriverOpen(&hACMDriver, hACMDriverID, 0))
	{
		Log(1, "*** Failed To Open Driver MS-ADPCM Driver ***");
		return 0;
	}

	ADPCMBuffer = (uchar*)SYSTEM_MALLOC(0x5800);
	wav_file_buffer = (uchar*)SYSTEM_MALLOC(0x37000);
	wav_format.wFormatTag = WAVE_FORMAT_PCM;
	acmMetrics(0, ACM_METRIC_MAX_SIZE_FORMAT, &pMetric);
	acmFormatSuggest(hACMDriver, (LPWAVEFORMATEX)&source_wav_format, &wav_format, pMetric, ACM_FORMATSUGGESTF_WFORMATTAG);
	audio_buffer_size = 0x577C0;
	NotifySize = 0x15DF0;

	memset(&desc, 0, sizeof(desc));
	desc.dwBufferBytes = 0x577C0;
	desc.dwReserved = 0;
	desc.dwSize = 20;
	desc.dwFlags = DSBCAPS_LOCSOFTWARE | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_GETCURRENTPOSITION2;
	desc.lpwfxFormat = &wav_format;
	App.dx.lpDS->CreateSoundBuffer(&desc, &DSBuffer, 0);
	DSBuffer->QueryInterface(DSNGUID, (LPVOID*)&DSNotify);

	ACMSetupNotifications();
	acmStreamOpen(&hACMStream, hACMDriver, (LPWAVEFORMATEX)&source_wav_format, &wav_format, 0, 0, 0, 0);
	acmStreamSize(hACMStream, 0x5800, &StreamSize, 0);
	DXAttempt(DSBuffer->Lock(0, audio_buffer_size, (LPVOID*)&pAudioWrite, &AudioBytes, 0, 0, 0));
	memset(pAudioWrite, 0, audio_buffer_size);

	for (int i = 0; i < 4; i++)
	{
		memset(&StreamHeaders[i], 0, sizeof(ACMSTREAMHEADER));
		StreamHeaders[i].cbStruct = sizeof(ACMSTREAMHEADER);
		StreamHeaders[i].pbSrc = ADPCMBuffer;
		StreamHeaders[i].cbSrcLength = 0x5800;
		StreamHeaders[i].cbDstLength = StreamSize;
		StreamHeaders[i].pbDst = &pAudioWrite[NotifySize * i];
		acmStreamPrepareHeader(hACMStream, &StreamHeaders[i], 0);
	}

	DXAttempt(DSBuffer->Unlock(pAudioWrite, audio_buffer_size, 0, 0));
	acm_ready = 1;
	return 1;
}

void ACMClose()
{
	if (!acm_ready)
		return;

	EnterCriticalSection(&audio_cs);
	S_CDStop();
	CloseHandle(NotifyEventHandles[0]);
	CloseHandle(NotifyEventHandles[1]);
	acmStreamUnprepareHeader(hACMStream, &StreamHeaders[0], 0);
	acmStreamUnprepareHeader(hACMStream, &StreamHeaders[1], 0);
	acmStreamUnprepareHeader(hACMStream, &StreamHeaders[2], 0);
	acmStreamUnprepareHeader(hACMStream, &StreamHeaders[3], 0);
	acmStreamClose(hACMStream, 0);
	acmDriverClose(hACMDriver, 0);

	if (DSNotify)
	{
		Log(4, "Released %s @ %x - RefCnt = %d", "Notification", DSNotify, DSNotify->Release());
		DSNotify = 0;
	}
	else
		Log(1, "%s Attempt To Release NULL Ptr", "Notification");

	if (DSBuffer)
	{
		Log(4, "Released %s @ %x - RefCnt = %d", "Stream Buffer", DSBuffer, DSBuffer->Release());
		DSBuffer = 0;
	}
	else
		Log(1, "%s Attempt To Release NULL Ptr", "Stream Buffer");

	LeaveCriticalSection(&audio_cs);
}

void S_CDPlay(long track, long mode)
{
	if (acm_ready)
	{
		__try
		{
			EnterCriticalSection(&audio_cs);
		}
		__finally
		{
			LeaveCriticalSection(&audio_cs);
		}

		IsAtmospherePlaying = track == CurrentAtmosphere;
		audio_counter = 0;
		S_CDStop();
		ACMEmulateCDPlay(track, mode);
	}
}

void S_CDPlayExt(unsigned char track_id, unsigned char channel_id, bool looping, bool restore_old_track) {
	if (looping) {
		if (CurrentAtmosphere != track_id)
		{
			CurrentAtmosphere = (uchar)track_id;

			if (IsAtmospherePlaying)
				S_CDPlay(track_id, true);
		}
	}
	else {
		S_CDPlay(track_id, false);
	}
}

void S_CDStop()
{
	if (acm_ready && audio_stream_fp)
	{
		__try
		{
			EnterCriticalSection(&audio_cs);
		}
		__finally
		{
			LeaveCriticalSection(&audio_cs);
		}

		memset(wav_file_buffer, 0, 0x37000);
		DSBuffer->Stop();
		DSBuffer->SetCurrentPosition(0);
		while (reading_audio_file) {};
		fclose(audio_stream_fp);
		audio_stream_fp = 0;
		audio_counter = 0;
		LegacyTrackFlag = 7;
		LegacyTrack = -1;
	}
}

void S_CDStopExt(unsigned char channel_id) {
	S_CDStop();
}

void S_CDSetChannelVolume(unsigned char volume, unsigned char channel) {
	return;
}

void S_StartSyncedAudio(long track)
{
	S_CDStop();
	S_CDPlay(track, 2);
}

void S_AudioUpdate() {
	return;
}

void S_PauseAudio() {
	return;
}

void S_UnpauseAudio() {
	return;
}

void S_Reset() {
	return;
}

void SetUsingNewAudioSystem(bool enabled) {
}

void SetUsingOldTriggerMode(bool enabled) {
}

bool IsUsingNewAudioSystem() {
	return false;
}

bool IsUsingOldTriggerMode() {
	return true;
}

#else
#define STB_VORBIS_HEADER_ONLY // <-- Exclude stb_vorbis' implementation
#include "../tomb4/libs/miniaudio/extras/stb_vorbis.c"

#include "../tomb4/libs/miniaudio/miniaudio.h"
#include "../tomb4/mod_config.h"

bool new_audio_system = false;
bool old_cd_trigger_mode = true;

#define MA_AUDIO_STREAM_COUNT 2

enum StreamMode {
	STREAM_ONESHOT_AND_RESTORE_ATMOSPHERE,
	STREAM_LOOP,
	STREAM_ONESHOT_AND_SILENCE
};

struct ma_audio_stream_channel {
	ma_uint64 current_stream_length = 0;
	ma_bool32 current_stream_loops = false;
	ma_bool32 current_stream_paused = false;
	bool current_stream_finished = false;
	StreamMode current_stream_mode = StreamMode::STREAM_ONESHOT_AND_RESTORE_ATMOSPHERE;
	bool current_stream_active = false;
	int current_track = -1;
	int current_volume = 100;

	int restore_track = -1;
	StreamMode restore_stream_mode = StreamMode::STREAM_ONESHOT_AND_RESTORE_ATMOSPHERE;

	ma_decoder_config decoder_config = {};
	ma_decoder decoder = {};
	ma_device device = {};
	ma_device_config deviceConfig = {};
};

struct ma_callback_userdata {
	int channel_id = -1;
};

ma_audio_stream_channel channels[MA_AUDIO_STREAM_COUNT];
ma_callback_userdata callback_userdata[MA_AUDIO_STREAM_COUNT];

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount) {
	ma_callback_userdata *userdata = (ma_callback_userdata *)pDevice->pUserData;
	int channel_id = userdata->channel_id;

	ma_decoder* pDecoder = &channels[channel_id].decoder;
	if (pDecoder == NULL) {
		return;
	}

	if (!channels[channel_id].current_stream_paused) {
		ma_uint64 frames_read;
		ma_data_source_read_pcm_frames(pDecoder, pOutput, frameCount, &frames_read);

		channels[channel_id].current_stream_finished = false;
		if (!channels[channel_id].current_stream_loops) {
			if (frames_read == 0) {
				channels[channel_id].current_stream_finished = true;
			}
		}
	}
}

void stop_track_on_stream_channel(int channel_id) {
	if (channel_id == 0) {
		LegacyTrack = -1;
		LegacyTrackFlag = 7;
	}

	channels[channel_id].current_track = -1;

	if (channels[channel_id].device.pContext) {
		if (ma_device_stop(&channels[channel_id].device) != MA_SUCCESS) {
			printf("Failed to stop playback device.\n");
			ma_device_uninit(&channels[channel_id].device);
			ma_decoder_uninit(&channels[channel_id].decoder);
		}
	}
}

bool load_and_play_track(const char* path, StreamMode mode, int channel_id) {
	stop_track_on_stream_channel(channel_id);

#if defined(_WIN32) && defined(UNICODE)
	wchar_t wide_path[MAX_PATH];
	MultiByteToWideChar(CP_UTF8, 0, path, -1, wide_path, sizeof(wide_path) / sizeof(wchar_t));
	ma_result result = ma_decoder_init_file_w(wide_path, &channels[channel_id].decoder_config, &channels[channel_id].decoder);
#else
	ma_result result = ma_decoder_init_file(path, &channels[channel_id].decoder_config, &channels[channel_id].decoder);
#endif
	if (result != MA_SUCCESS) {
		return false;
	}

	channels[channel_id].current_stream_mode = mode;

	ma_data_source_set_looping(&channels[channel_id].decoder, channels[channel_id].current_stream_mode == STREAM_LOOP ? MA_TRUE : MA_FALSE);

	channels[channel_id].deviceConfig = ma_device_config_init(ma_device_type_playback);
	channels[channel_id].deviceConfig.playback.format = channels[channel_id].decoder.outputFormat;
	channels[channel_id].deviceConfig.playback.channels = channels[channel_id].decoder.outputChannels;
	channels[channel_id].deviceConfig.sampleRate = channels[channel_id].decoder.outputSampleRate;
	channels[channel_id].deviceConfig.dataCallback = data_callback;
	channels[channel_id].deviceConfig.pUserData = &callback_userdata[channel_id];

	result = ma_data_source_get_length_in_pcm_frames(&channels[channel_id].decoder, &channels[channel_id].current_stream_length);
	if (result != MA_SUCCESS) {
		return false;
	}

	if (ma_device_init(NULL, &channels[channel_id].deviceConfig, &channels[channel_id].device) != MA_SUCCESS) {
		printf("Failed to open playback device.\n");
		ma_decoder_uninit(&channels[channel_id].decoder);
		return false;
	}

	ma_data_source_get_length_in_pcm_frames(&channels[channel_id].decoder, &channels[channel_id].current_stream_length);
	channels[channel_id].current_stream_loops = ma_data_source_is_looping(&channels[channel_id].decoder);

	if (ma_device_start(&channels[channel_id].device) != MA_SUCCESS) {
		printf("Failed to start playback device.\n");
		ma_device_uninit(&channels[channel_id].device);
		ma_decoder_uninit(&channels[channel_id].decoder);
		return false;
	}

	return true;
}

bool play_track_on_stream_channel(int channel_id, long track, StreamMode mode) {
	std::string audio_path = working_dir_path + "audio" + PATH_SEPARATOR;

	char name[2048];
	memset(name, 0x00, sizeof(name));

	if (get_game_mod_global_info()->tr_level_editor)
	{
		platform_find_file_with_substring(audio_path.c_str(), LevelEditorTrackFileNames[track], name);

		// Not sure if we should detect vorbis by filename since ogg is container format.
		// May need to investigate the spec further.
		char* ext = strrchr(name, '.');
		if (ext) {
			if (platform_strcicmp(ext, "wav") == 0) {
				channels[channel_id].decoder_config.encodingFormat = ma_encoding_format_wav;
			} else if (platform_strcicmp(ext, "mp3") == 0) {
				channels[channel_id].decoder_config.encodingFormat = ma_encoding_format_mp3;
			} else if (platform_strcicmp(ext, "flac") == 0) {
				channels[channel_id].decoder_config.encodingFormat = ma_encoding_format_flac;
			} else {
				channels[channel_id].decoder_config.encodingFormat = ma_encoding_format_unknown;
			}
		} else {
			channels[channel_id].decoder_config.encodingFormat = ma_encoding_format_unknown;
		}
	} else {
		memcpy(name, LastRevelationTrackFileNames[track], strlen(LastRevelationTrackFileNames[track]));
		channels[channel_id].decoder_config.encodingFormat = ma_encoding_format_wav;
	}

	audio_path += PATH_SEPARATOR;
	audio_path += name;

	bool result = load_and_play_track(audio_path.c_str(), (StreamMode)mode, channel_id);

	if (result) {
		channels[channel_id].current_stream_active = true;
		channels[channel_id].current_track = track;
	}

	if (channel_id == 0) {
		LegacyTrack = track;
		LegacyTrackFlag = 6;
	}

	ACMSetVolume();

	return result;
}

void track_complete_callback(int channel_id) {
	if (channels[channel_id].current_stream_mode == STREAM_ONESHOT_AND_RESTORE_ATMOSPHERE) {
		if (CurrentAtmosphere && !IsAtmospherePlaying)
		{
			if (channels[channel_id].current_stream_active) {
				S_CDStop();
				S_CDPlay(CurrentAtmosphere, 1);
			}
		}
	} else {
		if (channels[channel_id].current_stream_active) {
			stop_track_on_stream_channel(channel_id);

			if (channels[channel_id].restore_track != -1) {
				int next_track = channels[channel_id].restore_track;
				StreamMode next_stream_mode = channels[channel_id].restore_stream_mode;

				channels[channel_id].restore_track = -1;

				play_track_on_stream_channel(channel_id, next_track, next_stream_mode);
			}
		}
	}

	channels[channel_id].current_stream_finished = false;
}

bool ACMInit()
{
	for (int i = 0; i < MA_AUDIO_STREAM_COUNT; i++) {
		callback_userdata[i].channel_id = i;
	}

	acm_ready = true;
	return true;
}

void ACMClose()
{
	S_CDStop();
	for (int i = 0; i < MA_AUDIO_STREAM_COUNT; i++) {
		ma_device_uninit(&channels[i].device);
		ma_decoder_uninit(&channels[i].decoder);
	}
	acm_ready = false;
}

void ACMSetVolume()
{
	long volume;

	for (int i = 0; i < MA_AUDIO_STREAM_COUNT; i++) {
		float current_volume_float = (float)(channels[i].current_volume) / 100.0f;
		float master_volume_float = (float)(MusicVolume) / 100.0f;

		if (!MusicVolume || !channels[i].current_volume) {
			volume = -10000;
		} else {
			volume = (long)roundf(- 4000 * (1.0f - (current_volume_float * master_volume_float)));
		}

		ma_device_set_master_volume_db(&channels[i].device, (float)volume * 0.01f);
	}
}

void S_CDPlay(long track, long mode) {
	if (!new_audio_system || old_cd_trigger_mode) {
		play_track_on_stream_channel(0, track, (StreamMode)mode);

		IsAtmospherePlaying = track == CurrentAtmosphere;
	} else {
		if (mode == StreamMode::STREAM_LOOP) {
			play_track_on_stream_channel(0, track, StreamMode::STREAM_LOOP);
		} else {
			play_track_on_stream_channel(1, track, StreamMode::STREAM_ONESHOT_AND_SILENCE);
		}
	}
}

// TODO: restore should restore at the specific time of the original track
void S_CDPlayExt(unsigned char track_id, unsigned char channel_id, bool looping, bool restore_old_track) {
	if (IsUsingNewAudioSystem()) {
		if (channels[channel_id].current_track != track_id || !looping) {
			if (restore_old_track) {
				channels[channel_id].restore_track = channels[channel_id].current_track;
				channels[channel_id].restore_stream_mode = channels[channel_id].restore_stream_mode;
			}

			play_track_on_stream_channel(channel_id, track_id, looping ? StreamMode::STREAM_LOOP : StreamMode::STREAM_ONESHOT_AND_SILENCE);
		}
	} else {
		if (looping) {
			if (CurrentAtmosphere != track_id)
			{
				CurrentAtmosphere = (uchar)track_id;

				if (IsAtmospherePlaying)
					S_CDPlay(track_id, true);
			}
		}
		else {
			S_CDPlay(track_id, false);
		}
	}
}

void S_CDStop() {
	for (int i = 0; i < MA_AUDIO_STREAM_COUNT; i++) {
		channels[i].current_stream_active = false;
		stop_track_on_stream_channel(i);
	}
}

void S_CDStopExt(unsigned char channel_id) {
	if (IsUsingNewAudioSystem()) {
		stop_track_on_stream_channel(channel_id);
	}
	else {
		S_CDStop();
	}
}

void S_StartSyncedAudio(long track) {
	S_CDStop();
	S_CDPlay(track, 2);
}

void S_Reset() {
	new_audio_system = false;
	old_cd_trigger_mode = true;

	for (int i = 0; i < MA_AUDIO_STREAM_COUNT; i++) {
		channels[i].current_stream_length = 0;
		channels[i].current_stream_loops = false;
		channels[i].current_stream_paused = false;
		channels[i].current_stream_finished = false;
		channels[i].current_stream_mode = StreamMode::STREAM_ONESHOT_AND_RESTORE_ATMOSPHERE;
		channels[i].current_stream_active = false;
		channels[i].current_track = -1;
		channels[i].current_volume = 100;
	}

	ACMSetVolume();
}

void S_AudioUpdate() {
	for (int i = 0; i < MA_AUDIO_STREAM_COUNT; i++) {
		bool should_callback = false;
		ma_mutex_lock(&channels[i].device.startStopLock);
		{
			if (channels[i].current_stream_finished) {
				should_callback = true;
			}
		}
		ma_mutex_unlock(&channels[i].device.startStopLock);
		if (should_callback)
			track_complete_callback(i);
	}
}

void S_PauseAudio() {
	for (int i = 0; i < MA_AUDIO_STREAM_COUNT; i++) {
		if (channels[i].device.pContext) {
			ma_mutex_lock(&channels[i].device.startStopLock);
			{
				channels[i].current_stream_paused = true;
			}
			ma_mutex_unlock(&channels[i].device.startStopLock);
		} else {
			channels[i].current_stream_paused = true;
		}
	}
}

void S_CDSetChannelVolume(unsigned char volume, unsigned char channel) {
	if (IsUsingNewAudioSystem()) {
		channels[channel].current_volume = volume;
		ACMSetVolume();
	}
}

void S_UnpauseAudio() {
	for (int i = 0; i < MA_AUDIO_STREAM_COUNT; i++) {
		if (channels[i].device.pContext) {
			ma_mutex_lock(&channels[i].device.startStopLock);
			{
				channels[i].current_stream_paused = false;
			}
			ma_mutex_unlock(&channels[i].device.startStopLock);
		} else {
			channels[i].current_stream_paused = false;
		}
	}
}

void SetUsingNewAudioSystem(bool enabled) {
	new_audio_system = enabled;
}

void SetUsingOldTriggerMode(bool enabled) {
	old_cd_trigger_mode = enabled;
}

bool IsUsingNewAudioSystem() {
	return new_audio_system;
}

bool IsUsingOldTriggerMode() {
	return old_cd_trigger_mode;
}

void FillADPCMBuffer(char* p, long track)
{
	// Dummied out, kept around for now for frontend compatibility.
}

#endif