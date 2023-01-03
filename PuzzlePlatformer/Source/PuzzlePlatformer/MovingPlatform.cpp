// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (HasAuthority())
	{
		MovePlatform(DeltaTime);
	}
	
}

void AMovingPlatform::AddActiveTrigger()
{
	ActiveTriggers++;
}

void AMovingPlatform::RemoveActiveTrigger()
{
	if (ActiveTriggers > 0)
	{
		ActiveTriggers--;
	}
}


void AMovingPlatform::MovePlatform(float inDeltaTime)
{
	if (ActiveTriggers >= 1)
	{
		FVector location = GetActorLocation();
		float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
		float JourneyTravelled = (location - GlobalStartLocation).Size();

		if (JourneyTravelled >= JourneyLength)
		{
			FVector swap = GlobalStartLocation;
			GlobalStartLocation = GlobalTargetLocation;
			GlobalTargetLocation = swap;
		}

		FVector direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
		location += direction * MovementSpeed * inDeltaTime;
		SetActorLocation(location);
	}
}

