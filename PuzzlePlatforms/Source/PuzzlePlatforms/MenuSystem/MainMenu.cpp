#include "MainMenu.h"

#include "Button.h"
#include "WidgetSwitcher.h"
#include "EditableTextBox.h"


void UMainMenu::Setup()
{
	this->AddToViewport();

	UWorld *World = GetWorld();
	if (!ensure(World != nullptr)) return;
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = true;
}

void UMainMenu::NativeDestruct()
{
	Super::NativeDestruct();
	APlayerController* PlayerController = GetOwningPlayer();
	if (!ensure(PlayerController != nullptr)) return;
	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->bShowMouseCursor = false;
}

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success)
	{
		return false;
	}

	if (!ensure(HostButton != nullptr)) return false;
	if (!ensure(JoinButton != nullptr)) return false;

	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
	CancelJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);
	ConfirmServerButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);
	return true;
}

void UMainMenu::SetMenuInterface(IMenuInterface *MenuInterface)
{
	this->MenuInterface = MenuInterface;
}

void UMainMenu::HostServer()
{
	if (MenuInterface != nullptr)
	{
		MenuInterface->Host();
	}
}

void UMainMenu::JoinServer()
{
	if (MenuInterface != nullptr && IpAddressField != nullptr)
	{
		MenuInterface->Join(IpAddressField->Text.ToString());
	}
}

void UMainMenu::OpenJoinMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);	
}

void UMainMenu::OpenMainMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(MainMenu);
}