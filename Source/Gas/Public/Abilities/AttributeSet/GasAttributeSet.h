// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GasAttributeSet.generated.h"

/** 이 매크로를 사용하면 알아서 함수를 만들어줌
 *  매크로는 치환을 해주기 때문
 *  ex) ATTRIBUTE_ACCESSORS(UGasAttributeSet, MaxHealth)
 *  GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) == GAMEPLAYATTRIBUTE_VALUE_GETTER(MaxHealth)
*
*  GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)매크로 들어가면
*  
*  #define GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	FORCEINLINE float Get##PropertyName() const \
	{ \
		return PropertyName.GetCurrentValue(); \
	}
    들어간 매크로 아래처럼 치환되는거임
#define GAMEPLAYATTRIBUTE_VALUE_GETTER(MaxHealth) \
	FORCEINLINE float GetMaxHealth() const \
	{ \
		return MaxHealth.GetCurrentValue(); \
	}
* 이렇게 서로 치환 해주므로 자동으로 함수를 만들어주는 매크로
*/

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)



UCLASS()
class GAS_API UGasAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UGasAttributeSet, Health)
	
	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UGasAttributeSet, MaxHealth)

	UPROPERTY()
	UAbilitySystemComponent* AbilitySystemComponent;

	
protected:
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);
	
	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
};



