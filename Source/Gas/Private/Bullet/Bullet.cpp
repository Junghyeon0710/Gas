// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet/Bullet.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Gas/GasCharacter.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("RootComponent"));
	
	BulletActor = CreateDefaultSubobject<UStaticMeshComponent>("Bullet");
	BulletActor->SetupAttachment(RootComponent);
	
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(RootComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this,&ABullet::SpherOverlap);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::SpherOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ApplyEffectToTarget(OtherActor,GameplayEffectClass);
	AGasCharacter* Character = Cast<AGasCharacter>(OtherActor);
	Character->Destroy();
	Destroy();
}

void ABullet::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffect)
{
	if(IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(TargetActor))
	{
		checkf(GameplayEffectClass,TEXT("fill GameplayEffectClass"));
		UAbilitySystemComponent* ASC =  ASI->GetAbilitySystemComponent();

		if(ASC)
		{
			FGameplayEffectContextHandle GameplayEffectContext =  ASC->MakeEffectContext();
			GameplayEffectContext.AddSourceObject(this);
			const FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(GameplayEffect,1,GameplayEffectContext);
			ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
		}
	}
}