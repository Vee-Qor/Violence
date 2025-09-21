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
UE_DEFINE_GAMEPLAY_TAG(InputTag_StanceShift, "InputTag.StanceShift")
UE_DEFINE_GAMEPLAY_TAG(InputTag_AbilityOne, "InputTag.AbilityOne")

// Player Tags //
UE_DEFINE_GAMEPLAY_TAG(Player_Ability_AirSlash, "Player.Ability.AirSlash")
UE_DEFINE_GAMEPLAY_TAG(Player_Ability_BloodPact, "Player.Ability.BloodPact")
UE_DEFINE_GAMEPLAY_TAG(Player_Ability_BloodPact_Cooldown, "Player.Ability.BloodPact.Cooldown")

// Common Tags //
UE_DEFINE_GAMEPLAY_TAG(Common_Ability_PrimaryAttack, "Common.Ability.PrimaryAttack")
UE_DEFINE_GAMEPLAY_TAG(Common_Ability_StanceShift, "Common.Ability.StanceShift")
UE_DEFINE_GAMEPLAY_TAG(Common_Ability_Jump, "Common.Ability.Jump")
UE_DEFINE_GAMEPLAY_TAG(Common_Ability_Jump_Cooldown, "Common.Ability.Jump.Cooldown")

UE_DEFINE_GAMEPLAY_TAG(Common_Status_Combat, "Common.Status.Combat")
UE_DEFINE_GAMEPLAY_TAG(Common_Status_Travel, "Common.Status.Travel")
UE_DEFINE_GAMEPLAY_TAG(Common_Status_OnGround, "Common.Status.OnGround")
UE_DEFINE_GAMEPLAY_TAG(Common_Status_InAir, "Common.Status.InAir")
UE_DEFINE_GAMEPLAY_TAG(Common_Status_Attacking, "Common.Status.Attacking")
UE_DEFINE_GAMEPLAY_TAG(Common_Status_StanceShifting, "Common.Status.StanceShifting")
UE_DEFINE_GAMEPLAY_TAG(Common_Status_Casting, "Common.Status.Casting")

UE_DEFINE_GAMEPLAY_TAG(Common_Event_AttackTrace, "Common.Event.AttackTrace")
UE_DEFINE_GAMEPLAY_TAG(Common_Event_CanAttack, "Common.Event.CanAttack")
UE_DEFINE_GAMEPLAY_TAG(Common_Event_ResetAttack, "Common.Event.ResetAttack")
UE_DEFINE_GAMEPLAY_TAG(Common_Event_StanceShift, "Common.Event.StanceShift")
UE_DEFINE_GAMEPLAY_TAG(Common_Event_BuffApplied, "Common.Event.BuffApplied")

// GameplayCue Tags //
UE_DEFINE_GAMEPLAY_TAG(GameplayCue_BloodPact_Bloody, "GameplayCue.BloodPact.BloodyBlades")
UE_DEFINE_GAMEPLAY_TAG(GameplayCue_Hit_CameraShake, "GameplayCue.Hit.CameraShake")
UE_DEFINE_GAMEPLAY_TAG(GameplayCue_Hit_Impact, "GameplayCue.Hit.Impact")
UE_DEFINE_GAMEPLAY_TAG(GameplayCue_Hit_React, "GameplayCue.Hit.React")

}