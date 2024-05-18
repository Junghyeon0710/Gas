// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "GasCharacter.generated.h"

UCLASS(Blueprintable)
class AGasCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AGasCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UAbilitySystemComponent* Test;



private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
};

#define ASAEEQ(PropertyName) \
FORCEINLINE void Set##PropertyName(float NewVal) \
{ \
UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent(); \
if (ensure(AbilityComp)) \
{ \
AbilityComp->GetSpawnedAttributes() \
}; \
}