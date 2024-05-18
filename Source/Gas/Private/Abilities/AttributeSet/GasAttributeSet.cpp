// Fill out your copyright notice in the Description page of Project Settings.


#include <Gas/Public/Abilities/AttributeSet/GasAttributeSet.h>
#include "Net/UnrealNetwork.h"

void UGasAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UGasAttributeSet,Health,COND_None);
	
}

void UGasAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGasAttributeSet,Health,OldHealth);
}

void UGasAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGasAttributeSet,MaxHealth,OldMaxHealth);
}
