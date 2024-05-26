 // Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GasEnemyCharacter.h"

#include "AbilitySystemComponent.h"
#include "Abilities/AttributeSet/GasAttributeSet.h"

 AGasEnemyCharacter::AGasEnemyCharacter()
 {
 	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
 	AbilitySystemComponent->SetIsReplicated(true);
 	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal); // Mixed는 이펙트는 소유 클라  //미니멀은 이펙트는 복제 안됨 ex ) 적들은 속성값이 복제될표가없고 큐하고 태그만 되면됨 , Full 이펙트가 모든 클라

 	AttributeSet = CreateDefaultSubobject<UGasAttributeSet>("AttributeSet");
 }

 void AGasEnemyCharacter::BeginPlay()
 {
   Super::BeginPlay();

 	AbilitySystemComponent->InitAbilityActorInfo(this,this);

 	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAttributeSet()->GetHealthAttribute()).AddLambda(
 		[this](const FOnAttributeChangeData& Data)
 		{
 			GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Blue, FString::Printf(TEXT("Health = %f"),Data.NewValue));
 		});
 }
