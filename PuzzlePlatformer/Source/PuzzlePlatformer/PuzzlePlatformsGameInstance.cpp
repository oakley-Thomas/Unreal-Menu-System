// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
#include "Engine/Engine.h"
#include <Kismet/GameplayStatics.h>

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{

}

void UPuzzlePlatformsGameInstance::Init()
{

}

void UPuzzlePlatformsGameInstance::Host()
{
	UEngine* engine = GetEngine();
	if (engine == nullptr) { return; }
	engine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("HOSTING"));

	UWorld* World = GetWorld();
	if (World == nullptr) { return; }
	World->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen"); 
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
	UEngine* engine = GetEngine();
	if (engine == nullptr) { return; }
	engine->AddOnScreenDebugMessage(-1, 5, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));
	
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController != nullptr) { return; }
	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}