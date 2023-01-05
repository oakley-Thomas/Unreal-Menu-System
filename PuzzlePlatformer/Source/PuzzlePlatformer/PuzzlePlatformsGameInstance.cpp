// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
#include "Engine/Engine.h"
#include <Kismet/GameplayStatics.h>
#include "Blueprint/UserWidget.h"
#include "MainMenu.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MainMenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (MainMenuBPClass.Class == nullptr) { return; }
	MainMenuClass = MainMenuBPClass.Class;
	UE_LOG(LogTemp, Warning, TEXT("%s"), *MainMenuClass->GetName());
}

void UPuzzlePlatformsGameInstance::Init()
{
	
}

void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if (MainMenuClass == nullptr) { return; }
	MainMenu = CreateWidget<UMainMenu>(this, MainMenuClass);
	if (MainMenu == nullptr) { return; }
	MainMenu->SetMenuInterface(this);
	MainMenu->Setup();
}

void UPuzzlePlatformsGameInstance::Host()
{
	if (MainMenu != nullptr)
	{
		MainMenu->TearDown();
	}
	
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