// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GasPlayerState.h"

#include "AbilitySystemComponent.h"

AGasPlayerState::AGasPlayerState()
{
	NetPriority = 100.f; // 스테이트는 기본적으로 매우낮은값으로 설정되어있어서 100이 적당, 1초에 100번 클라이언트에 값을 보냄

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed); // Mixed는 이펙트는 소유 클라  //미니멀은 이펙트는 복제 안됨 ex ) 적들은 속성값이 복제될표가없고 큐하고 태그만 되면됨 , Full 이펙트가 모든 클라

	AttributeSet = CreateDefaultSubobject<UAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AGasPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
