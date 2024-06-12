// Fill out your copyright notice in the Description page of Project Settings.


#include <Gas/Public/Abilities/AttributeSet/GasAttributeSet.h>
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"

UGasAttributeSet::UGasAttributeSet()
{
	InitHealth(100.f);
	InitMaxHealth(100.f);
}


void UGasAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if(Attribute == GetHealthAttribute())
	{
		NewValue =  FMath::Clamp(NewValue,0.f,GetMaxHealth());
	}
}

void UGasAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if(Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(),0.f,GetMaxHealth()));
	}
}

void UGasAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UGasAttributeSet,Health,COND_None,REPNOTIFY_Always);
	
}

void UGasAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	//예측을 사용하기때문에 롤백할 수 있는 매크로를 사용
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGasAttributeSet,Health,OldHealth);
}

void UGasAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGasAttributeSet,MaxHealth,OldMaxHealth);
	
}
  