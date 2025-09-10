// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "NativeGameplayTags.h"

namespace VGameplayTags
{

// Input Tags //
UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Jump)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_PrimaryAttack)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_AirAttack)

// Player Tags //
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Jump)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Jump_Cooldown)

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_PrimaryAttack)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_AirSlash)

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_InAir)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_OnGround)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Attacking)

}