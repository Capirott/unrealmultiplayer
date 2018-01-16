// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameMenu.h"
#include "PuzzlePlatformsGameInstance.h"
#include "Button.h"

bool UInGameMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success)
	{
		return false;
	}

	if (!ensure(CancelButton != nullptr)) return false;
	if (!ensure(QuitButton!= nullptr)) return false;

	CancelButton->OnClicked.AddDynamic(this, &UInGameMenu::RemoveFromViewport);
	QuitButton->OnClicked.AddDynamic(this, &UInGameMenu::LoadMainMenu);

	return true;
}

void UInGameMenu::LoadMainMenu()
{
	if (MenuInterface != nullptr) {
		RemoveFromViewport();
		MenuInterface->LoadMainMenu();
	}
}
