// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMER_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AMovingPlatform();
	void BeginPlay() override;
	void MovePlatform(float inDeltaTime);
	void Tick(float DeltaTime) override;

	void AddActiveTrigger();
	void RemoveActiveTrigger();

private:
	UPROPERTY(EditAnywhere)
		float MovementSpeed = 50.0;
	UPROPERTY(VisibleAnywhere)
		FVector GlobalStartLocation;
	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
		FVector TargetLocation;
	FVector GlobalTargetLocation;

	UPROPERTY(EditAnywhere)
		int ActiveTriggers = 1;
	
};
