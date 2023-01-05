// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/EditableText.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) { return false; }
	if (HostButton == nullptr) { return false; }

	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
	Cancel_IP_Button->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);
	IP_Button->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);
	return true;
}

void UMainMenu::SetMenuInterface(IMenuInterface* InMenuInterface)
{
	this->MenuInterface = InMenuInterface;
	UE_LOG(LogTemp, Warning, TEXT("MENU IS SET"));
}

void UMainMenu::HostServer()
{
	if (MenuInterface != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hosting"));
		MenuInterface->Host();
	}
}

void UMainMenu::Setup()
{
	this->AddToViewport();
	
	FInputModeUIOnly InputMode;
	this->bIsFocusable = true;
	InputMode.SetWidgetToFocus(this->TakeWidget());
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController != nullptr) { return; }
	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = true;
}

void UMainMenu::TearDown()
{
	this->RemoveFromViewport();

	FInputModeGameOnly InputMode;

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController != nullptr) { return; }
	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = false;
}

void UMainMenu::OpenJoinMenu()
{
	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::OpenMainMenu()
{
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::JoinServer()
{
	if (MenuInterface != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hosting"));
		FString text = InputText->GetText().ToString();
		MenuInterface->Join(text);
	}
}