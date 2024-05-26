// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/GasCharacterBase.h"
#include "GasCharacter.generated.h"

class ABullet;

UCLASS(Blueprintable)
class AGasCharacter : public AGasCharacterBase
{
	GENERATED_BODY()

public:
	AGasCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;
	void InitAbilityInfoActor();

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
protected:
	virtual void BeginPlay() override;
private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABullet> Bullet;

	void OnBulletTimer();

	// Timer handle
	FTimerHandle BulletTimerHandle;
};
