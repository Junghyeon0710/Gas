// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "GasPlayerState.generated.h"

/**
 * 
 */
class UAbilitySystemComponent;
class UGasAttributeSet;
UCLASS()
class GAS_API AGasPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGasPlayerState();
	//~ IAbilitySystemInterface 
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface
	UGasAttributeSet* GetAttributeSet() const  { return AttributeSet;}
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UGasAttributeSet> AttributeSet;

	
};
