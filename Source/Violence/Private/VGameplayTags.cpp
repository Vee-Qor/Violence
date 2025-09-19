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
UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Jump, "Player.Ability.Jump")
UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Jump_Cooldown, "Player.Ability.Jump.Cooldown")

UE_DEFINE_GAMEPLAY_TAG(Player_Ability_PrimaryAttack, "Player.Ability.PrimaryAttack")
UE_DEFINE_GAMEPLAY_TAG(Player_Ability_AirSlash, "Player.Ability.AirSlash")
UE_DEFINE_GAMEPLAY_TAG(Player_Ability_StanceShift, "Player.Ability.StanceShift")

UE_DEFINE_GAMEPLAY_TAG(Player_Ability_BloodPact, "Player.Ability.BloodPact")
UE_DEFINE_GAMEPLAY_TAG(Player_Ability_BloodPact_Cooldown, "Player.Ability.BloodPact.Cooldown")

UE_DEFINE_GAMEPLAY_TAG(Player_Status_Combat, "Player.Status.Combat")
UE_DEFINE_GAMEPLAY_TAG(Player_Status_Travel, "Player.Status.Travel")
UE_DEFINE_GAMEPLAY_TAG(Player_Status_InAir, "Player.Status.InAir")
UE_DEFINE_GAMEPLAY_TAG(Player_Status_OnGround, "Player.Status.OnGround")
UE_DEFINE_GAMEPLAY_TAG(Player_Status_Attacking, "Player.Status.Attacking")
UE_DEFINE_GAMEPLAY_TAG(Player_Status_StanceShifting, "Player.Status.StanceShifting")
UE_DEFINE_GAMEPLAY_TAG(Player_Status_BloodPactActivation, "Player.Status.BloodPactActivation")

UE_DEFINE_GAMEPLAY_TAG(Player_Event_SwordTrace, "Player.Event.SwordTrace")
UE_DEFINE_GAMEPLAY_TAG(Player_Event_StanceShift, "Player.Event.StanceShift")
UE_DEFINE_GAMEPLAY_TAG(Player_Event_BuffApplied, "Player.Event.BuffApplied")
UE_DEFINE_GAMEPLAY_TAG(Player_Event_CanAttack, "Player.Event.CanAttack")
UE_DEFINE_GAMEPLAY_TAG(Player_Event_ResetAttack, "Player.Event.ResetAttack")

// GameplayCue Tags //
UE_DEFINE_GAMEPLAY_TAG(GameplayCue_BloodPact_Bloody, "GameplayCue.BloodPact.BloodyBlades")
UE_DEFINE_GAMEPLAY_TAG(GameplayCue_Hit_CameraShake, "GameplayCue.Hit.CameraShake")
UE_DEFINE_GAMEPLAY_TAG(GameplayCue_Hit_Impact, "GameplayCue.Hit.Impact")
UE_DEFINE_GAMEPLAY_TAG(GameplayCue_Hit_React, "GameplayCue.Hit.React")

}