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
	UGasAttributeSet();

	//값이 바뀌기전에 호출 하지만 에픽게임즈에서는 clamp만 하기를 권장 , 여기서 이벤트는 비추
	//값을 고정해도 이후에 변경되면 값이 또 바뀌기 때문에 이상적인 장소는 아님 post에서 수정당할 수 있음 그럼 거기서
	//다시 clamp를 해줘야함
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual  void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
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
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	
	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
};



