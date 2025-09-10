// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "VGameplayTags.h"

namespace VGameplayTags
{

// Input Tags //
UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move")
UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look")
UE_DEFINE_GAMEPLAY_TAG(InputTag_Jump, "InputTag.Jump")
UE_DEFINE_GAMEPLAY_TAG(InputTag_PrimaryAttack, "InputTag.PrimaryAttack")
UE_DEFINE_GAMEPLAY_TAG(InputTag_AirAttack, "InputTag.AirAttack")

// Player Tags //
UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Jump, "Player.Ability.Jump")
UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Jump_Cooldown, "Player.Ability.Jump.Cooldown")

UE_DEFINE_GAMEPLAY_TAG(Player_Ability_PrimaryAttack, "Player.Ability.PrimaryAttack")
UE_DEFINE_GAMEPLAY_TAG(Player_Ability_AirSlash, "Player.Ability.AirSlash")

UE_DEFINE_GAMEPLAY_TAG(Player_Status_InAir, "Player.Status.InAir")
UE_DEFINE_GAMEPLAY_TAG(Player_Status_OnGround, "Player.Status.OnGround")
UE_DEFINE_GAMEPLAY_TAG(Player_Status_Attacking, "Player.Status.Attacking")

}