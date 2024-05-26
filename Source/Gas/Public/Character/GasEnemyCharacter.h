// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/GasCharacterBase.h"
#include "GasEnemyCharacter.generated.h"

class ABullet;
/**
 * 
 */
UCLASS()
class GAS_API AGasEnemyCharacter : public AGasCharacterBase
{
	GENERATED_BODY()
public:
	AGasEnemyCharacter();

	virtual void BeginPlay() override;


};
