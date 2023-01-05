// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MainMenu.generated.h"


/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMER_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public: 
	void SetMenuInterface(IMenuInterface* InMenuInterface);

	void Setup();
	void TearDown();

protected:

	bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* IP_Button;

	UPROPERTY(meta = (BindWidget))
	class UEditableText* InputText;

	UPROPERTY(meta = (BindWidget))
	class UButton* Cancel_IP_Button;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;

	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void OpenMainMenu();

	UFUNCTION()
	void JoinServer();
	
	IMenuInterface* MenuInterface;
};
