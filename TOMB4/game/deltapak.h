#pragma once
#include "../global/types.h"

void handle_cutseq_triggering(long name);
void do_new_cutscene_camera();
void InitPackNodes(NODELOADHEADER* lnode, PACKNODE* pnode, char* packed, long numnodes);
void DecodeAnim(PACKNODE* node, long num_nodes, long frame, long flags);
short DecodeTrack(char* packed, RTDECODE* decode);
short GetTrackWord(long off, char* packed, long packmethod);
void fix_lara_for_cutseq();
void updateAnimFrame(PACKNODE* node, int flags, short* frame);
void* cutseq_malloc(long size);
void finish_cutseq();
void DrawCutSeqActors();
void CalcActorLighting(ITEM_INFO* item, OBJECT_INFO* obj, short* rot);
void GetJointAbsPositionCutSeq(ITEM_INFO* item, OBJECT_INFO* obj, short* rot, PHD_VECTOR* pos);
void CalculateObjectLightingLaraCutSeq();
void third_cutseq_control();
void fourth_cutseq_init();
void fourth_cutseq_control();
void fourth_cutseq_end();
void fifth_cutseq_control();
void fifth_cutseq_end();
void sixth_cutseq_init();
void sixth_cutseq_control();
void sixth_cutseq_end();
void seventh_cutseq_init();
void seventh_control();
void eighth_control();
void ninth_cutseq_init();
void ninth_control();
void tenth_cutseq_init();
void tenth_cutseq_control();
void tenth_cutseq_end();
void eleventh_cutseq_init();
void eleventh_cutseq_control();
void twelth_cutseq_init();
void twelth_cutseq_end();
void thirteen_end();
void fourteen_end();
void fourteen_control();
void fifteen_init();
void fifteen_control();
void fifteen_end();
void sixteen_init();
void sixteen_control();
void sixteen_end();
void seventeen_control();
void seventeen_end();
void eighteen_init();
void eighteen_control();
void eighteen_end();
void nineteen_init();
void nineteen_control();
void nineteen_end();
void twenty_control();
void twenty_end();
void twentyone_init();
void twentyone_end();
void twentythree_init();
void twentythree_control();
void twentythree_end();
void twentyfour_init();
void twentyfour_control();
void twentyfour_end();
void twentyfive_control();
void twentyfive_end();
void twentyfive_init();
void twentysix_control();
void twentyseven_init();
void twentyseven_control();
void twentyseven_end();
void twentytwo_init();
void twentytwo_end();
void do_spade_meshswap();
void do_key_meshswap();
void cutseq_shoot_pistols(long left_or_right);
void trigger_weapon_dynamics(long left_or_right);
void deal_with_pistols();
void cutseq_kill_item(long num);
ITEM_INFO* cutseq_restore_item(long num);
long Load_and_Init_Cutseq(long num);
void init_cutseq_actors(char* data, long resident);
void init_voncroy_meshbits(long num);
void DelsHandyTeleportLara(long x, long y, long z, long yrot);
void nail_intelligent_object(short num);
void handle_lara_chatting(short* _ranges);
void handle_actor_chatting(long speechslot, long node, long slot, long objslot, short* _ranges);
void trigger_item_in_room(long room_number, long object_number);
void untrigger_item_in_room(long room_number, long object_number);
ITEM_INFO* find_an_item_with_object_type(long object_number);
void special2_end();
void special2_init();
void special3_end();
void special3_control();
void special1_init();
void special1_end();
void times_init();
void times_control();

extern long cutseq_trig;
extern long cutseq_num;
extern long GLOBAL_playing_cutseq;
extern long GLOBAL_cutseq_frame;
