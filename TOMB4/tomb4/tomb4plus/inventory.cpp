#include "../../tomb4/pch.h"

#include "../../game/lara.h"
#include "../../game/objects.h"
#include "../../specific/function_stubs.h"
#include "../../game/health.h"

// TODO: there may be some missing types still needing support

int T4PlusGetInventoryCount(short object_number) {
	if (object_number >= PUZZLE_ITEM1_COMBO1 && object_number <= PUZZLE_ITEM8_COMBO2)
		return (lara.puzzleitemscombo >> (object_number - PUZZLE_ITEM1_COMBO1)) & 1;
	else if (object_number >= PUZZLE_ITEM1 && object_number <= PUZZLE_ITEM12)
		return lara.puzzleitems[object_number - PUZZLE_ITEM1];
	else if (object_number >= KEY_ITEM1_COMBO1 && object_number <= KEY_ITEM8_COMBO2)
		return (lara.keyitemscombo >> (object_number - KEY_ITEM1_COMBO1)) & 1;
	else if (object_number >= KEY_ITEM1 && object_number <= KEY_ITEM12)
		return (lara.keyitems >> (object_number - KEY_ITEM1)) & 1;
	else if (object_number >= PICKUP_ITEM1_COMBO1 && object_number <= PICKUP_ITEM4_COMBO2)
		return (lara.pickupitemscombo >> (object_number - PICKUP_ITEM1_COMBO1)) & 1;
	else if (object_number >= PICKUP_ITEM1 && object_number <= PICKUP_ITEM4)
		return (lara.pickupitems >> (object_number - PICKUP_ITEM1)) & 1;
	else if (object_number >= QUEST_ITEM1 && object_number <= QUEST_ITEM6)
		return (lara.questitems >> (object_number - QUEST_ITEM1)) & 1;
	else if (object_number == CROWBAR_ITEM)
		return lara.crowbar;
	else if (object_number == PISTOLS_ITEM)
		return lara.pistols_type_carried;
	else if (object_number == PISTOLS_AMMO_ITEM)
		return lara.num_pistols_ammo;
	else if (object_number == SHOTGUN_ITEM)
		return lara.shotgun_type_carried;
	else if (object_number == SHOTGUN_AMMO1_ITEM)
		return lara.num_shotgun_ammo1;
	else if (object_number == SHOTGUN_AMMO2_ITEM)
		return lara.num_shotgun_ammo2;
	else if (object_number == SIXSHOOTER_ITEM)
		return lara.sixshooter_type_carried;
	else if (object_number == SIXSHOOTER_AMMO_ITEM)
		return lara.num_revolver_ammo;
	else if (object_number == UZI_ITEM)
		return lara.uzis_type_carried;
	else if (object_number == UZI_AMMO_ITEM)
		return lara.num_uzi_ammo;
	else if (object_number == CROSSBOW_ITEM)
		return lara.crossbow_type_carried;
	else if (object_number == CROSSBOW_AMMO1_ITEM)
		return lara.num_crossbow_ammo1;
	else if (object_number == CROSSBOW_AMMO2_ITEM)
		return lara.num_crossbow_ammo2;
	else if (object_number == CROSSBOW_AMMO3_ITEM)
		return lara.num_crossbow_ammo3;
	else if (object_number == GRENADE_GUN_ITEM)
		return lara.grenade_type_carried;
	else if (object_number == GRENADE_GUN_AMMO1_ITEM)
		return lara.num_grenade_ammo1;
	else if (object_number == GRENADE_GUN_AMMO2_ITEM)
		return lara.num_grenade_ammo2;
	else if (object_number == GRENADE_GUN_AMMO3_ITEM)
		return lara.num_grenade_ammo3;
	else if (object_number == SMALLMEDI_ITEM)
		return lara.num_small_medipack;
	else if (object_number == BIGMEDI_ITEM)
		return lara.num_large_medipack;
	else if (object_number == FLARE_ITEM)
		return lara.num_flares;
	else if (object_number == BINOCULARS_ITEM)
		return lara.binoculars;
	else if (object_number == WATERSKIN1_EMPTY)
		return lara.small_water_skin == 1;
	else if (object_number == WATERSKIN1_1)
		return lara.small_water_skin == 2;
	else if (object_number == WATERSKIN1_2)
		return lara.small_water_skin == 3;
	else if (object_number == WATERSKIN1_3)
		return lara.small_water_skin == 4;
	else if (object_number == WATERSKIN2_EMPTY)
		return lara.big_water_skin == 1;
	else if (object_number == WATERSKIN2_1)
		return lara.big_water_skin == 2;
	else if (object_number == WATERSKIN2_2)
		return lara.big_water_skin == 3;
	else if (object_number == WATERSKIN2_3)
		return lara.big_water_skin == 4;
	else if (object_number == WATERSKIN2_4)
		return lara.big_water_skin == 5;
	else if (object_number == WATERSKIN2_5)
		return lara.big_water_skin == 6;
	else if (object_number == EXAMINE1)
		return lara.examine1;
	else if (object_number == EXAMINE2)
		return lara.examine2;
	else if (object_number == EXAMINE3)
		return lara.examine3;
	else
		Log(0, "T4PlusGetInventoryCount: unimplemented inventory item type!");

	return 0;
}

void T4PlusSetInventoryCount(short object_number, int count)
{
	if (object_number >= PUZZLE_ITEM1_COMBO1 && object_number <= PUZZLE_ITEM8_COMBO2) {
		if (count)
			lara.puzzleitemscombo |= (1 << (object_number - PUZZLE_ITEM1_COMBO1));
		else
			lara.puzzleitemscombo &= ~(1 << (object_number - PUZZLE_ITEM1_COMBO1));
	} else if (object_number >= PUZZLE_ITEM1 && object_number <= PUZZLE_ITEM12) {
		lara.puzzleitems[object_number - PUZZLE_ITEM1] = count;
	} else if (object_number >= KEY_ITEM1_COMBO1 && object_number <= KEY_ITEM8_COMBO2) {
		if (count)
			lara.keyitemscombo |= (1 << (object_number - KEY_ITEM1_COMBO1));
		else
			lara.keyitemscombo &= ~(1 << (object_number - KEY_ITEM1_COMBO1));
	} else if (object_number >= KEY_ITEM1 && object_number <= KEY_ITEM12) {
		if (count)
			lara.keyitems |= (1 << (object_number - KEY_ITEM1));
		else
			lara.keyitems &= ~(1 << (object_number - KEY_ITEM1));
	} else if (object_number >= PICKUP_ITEM1_COMBO1 && object_number <= PICKUP_ITEM4_COMBO2) {
		if (count)
			lara.pickupitemscombo |= (1 << (object_number - PICKUP_ITEM1_COMBO1));
		else
			lara.pickupitemscombo &= ~(1 << (object_number - PICKUP_ITEM1_COMBO1));
	} else if (object_number >= PICKUP_ITEM1 && object_number <= PICKUP_ITEM4) {
		if (count)
			lara.pickupitems |= (1 << (object_number - PICKUP_ITEM1));
		else
			lara.pickupitems &= ~(1 << (object_number - PICKUP_ITEM1));
	} else if (object_number >= QUEST_ITEM1 && object_number <= QUEST_ITEM6) {
		if (count)
			lara.questitems |= (1 << (object_number - QUEST_ITEM1));
		else
			lara.questitems &= ~(1 << (object_number - QUEST_ITEM1));
	}
	else if (object_number == CROWBAR_ITEM)
		lara.crowbar = count;
	else if (object_number == PISTOLS_ITEM)
		lara.pistols_type_carried = count;
	else if (object_number == PISTOLS_AMMO_ITEM)
		lara.num_pistols_ammo = count;
	else if (object_number == SHOTGUN_ITEM)
		lara.shotgun_type_carried = count;
	else if (object_number == SHOTGUN_AMMO1_ITEM)
		lara.num_shotgun_ammo1 = count;
	else if (object_number == SHOTGUN_AMMO2_ITEM)
		lara.num_shotgun_ammo2 = count;
	else if (object_number == SIXSHOOTER_ITEM)
		lara.sixshooter_type_carried = count;
	else if (object_number == SIXSHOOTER_AMMO_ITEM)
		lara.num_revolver_ammo = count;
	else if (object_number == UZI_ITEM)
		lara.uzis_type_carried = count;
	else if (object_number == UZI_AMMO_ITEM)
		lara.num_uzi_ammo = count;
	else if (object_number == CROSSBOW_ITEM)
		lara.crossbow_type_carried = count;
	else if (object_number == CROSSBOW_AMMO1_ITEM)
		lara.num_crossbow_ammo1 = count;
	else if (object_number == CROSSBOW_AMMO2_ITEM)
		lara.num_crossbow_ammo2 = count;
	else if (object_number == CROSSBOW_AMMO3_ITEM)
		lara.num_crossbow_ammo3 = count;
	else if (object_number == GRENADE_GUN_ITEM)
		lara.grenade_type_carried = count;
	else if (object_number == GRENADE_GUN_AMMO1_ITEM)
		lara.num_grenade_ammo1 = count;
	else if (object_number == GRENADE_GUN_AMMO2_ITEM)
		lara.num_grenade_ammo2 = count;
	else if (object_number == GRENADE_GUN_AMMO3_ITEM)
		lara.num_grenade_ammo3 = count;
	else if (object_number == SMALLMEDI_ITEM)
		lara.num_small_medipack = count;
	else if (object_number == BIGMEDI_ITEM)
		lara.num_large_medipack = count;
	else if (object_number == FLARE_ITEM)
		lara.num_flares = count;
	else if (object_number == BINOCULARS_ITEM)
		lara.binoculars = count;
	// TODO: check waterskin behaviour
	else if (object_number == WATERSKIN1_EMPTY)
		lara.small_water_skin = count;
	else if (object_number == WATERSKIN1_1)
		lara.small_water_skin = count;
	else if (object_number == WATERSKIN1_2)
		lara.small_water_skin = count;
	else if (object_number == WATERSKIN1_3)
		lara.small_water_skin = count;
	else if (object_number == WATERSKIN2_EMPTY)
		lara.big_water_skin = count;
	else if (object_number == WATERSKIN2_1)
		lara.big_water_skin = count;
	else if (object_number == WATERSKIN2_2)
		lara.big_water_skin = count;
	else if (object_number == WATERSKIN2_3)
		lara.big_water_skin = count;
	else if (object_number == WATERSKIN2_4)
		lara.big_water_skin = count;
	else if (object_number == WATERSKIN2_5)
		lara.big_water_skin = count;
	else if (object_number == EXAMINE1)
		lara.examine1 = count;
	else if (object_number == EXAMINE2)
		lara.examine2 = count;
	else if (object_number == EXAMINE3)
		lara.examine3 = count;
	else
		Log(0, "T4PlusSetInventoryCount: unimplemented inventory item type!");
}

void T4ShowObjectPickup(int object_number) {
	DISPLAYPU* pu;

	for (int i = 0; i < 8; i++)
	{
		pu = &pickups[i];

		if (pu->life < 0)
		{
			pu->life = 45;
			pu->object_number = object_number;
			break;
		}
	}
}