// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformTrigger.h"
#include "Components/BoxComponent.h"
#include "MovingPlatform.h"

// Sets default values
APlatformTrigger::APlatformTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create and Set Box Trigger as Root
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("TriggerVolume");
	if (BoxComponent == nullptr) { return; }
	RootComponent = BoxComponent;

	

}

// Called when the game starts or when spawned
void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapEnd);
}

// Called every frame
void APlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlatformTrigger::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	for (int i = 0; i < ControlledPlatforms.Num(); i++)
	{
		AMovingPlatform* platform = ControlledPlatforms[i];
		platform->AddActiveTrigger();
	}
}

void APlatformTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	for (int i = 0; i < ControlledPlatforms.Num(); i++)
	{
		AMovingPlatform* platform = ControlledPlatforms[i];
		platform->RemoveActiveTrigger();
	}
}

