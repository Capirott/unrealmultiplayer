#include "MainMenu.h"

#include "Button.h"
#include "WidgetSwitcher.h"
#include "EditableTextBox.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/TextBlock.h"

#include "ServerRow.h"

UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> ServerRowBPClass(TEXT("/Game/MenuSystem/WBP_ServerRow"));
	if (!ensure(ServerRowBPClass.Class != nullptr)) return;
	ServerRowClass = ServerRowBPClass.Class;
}

void UMainMenu::SetServerList(TArray<FServerData> ServerNames)
{
	UWorld* World = this->GetWorld();
	if (!ensure(World != nullptr)) return;

	ServerList->ClearChildren();

	uint32 i = 0;

	for (const FServerData& ServerName : ServerNames) 
	{
		UServerRow* Row = CreateWidget<UServerRow>(World, ServerRowClass);
		if (!ensure(Row != nullptr)) return;

		Row->ServerName->SetText(FText::FromString(ServerName.Name));
		Row->HostUser->SetText(FText::FromString(ServerName.HostUserName));
		Row->ConnectionFraction->SetText(FText::FromString(FString::FromInt(ServerName.CurrentPlayers) + "/" + FString::FromInt(ServerName.MaxPlayers)));

		Row->Setup(this, i);
		++i;
		ServerList->AddChild(Row);
	}
}

void UMainMenu::SelectIndex(uint32 Index)
{
	SelectedIndex = Index;
	UpdateChildren();
	UServerRow* Child = Cast<UServerRow>(ServerList->GetChildAt(Index));
	if (Child != nullptr)
	{
		Child->Selected = true;
	}
}

void UMainMenu::UpdateChildren()
{
	if (!ensure(ServerList != nullptr)) return;

	for (int32 i = 0; i < ServerList->GetChildrenCount(); ++i)
	{
		UServerRow* Child = Cast<UServerRow>(ServerList->GetChildAt(i));
		if (Child != nullptr)
		{
			Child->Selected = false;
		}
	}
}

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success)
	{
		return false;
	}

	if (!ensure(HostButton != nullptr)) return false;
	if (!ensure(CancelHostMenuButton!= nullptr)) return false;
	if (!ensure(ConfirmHostMenuButton != nullptr)) return false;
	if (!ensure(JoinButton != nullptr)) return false;
	if (!ensure(CancelJoinMenuButton != nullptr)) return false;
	if (!ensure(ConfirmServerButton != nullptr)) return false;
	if (!ensure(ExitButton != nullptr)) return false;

	HostButton->OnClicked.AddDynamic(this, &UMainMenu::OpenHostMenu);
	CancelHostMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);
	ConfirmHostMenuButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
	CancelJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);
	ConfirmServerButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);
	ExitButton->OnClicked.AddDynamic(this, &UMainMenu::ExitGame);
	return true;
}

void UMainMenu::ExitGame() 
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	PlayerController->ConsoleCommand("quit");
}

void UMainMenu::HostServer()
{
	if (MenuInterface != nullptr)
	{
		FString ServerName = ServerHostName->GetText().ToString();
		MenuInterface->Host(ServerName);
	}
}

void UMainMenu::JoinServer()
{
	if (SelectedIndex.IsSet() && MenuInterface != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected Index %d"), SelectedIndex.GetValue());
		MenuInterface->Join(SelectedIndex.GetValue());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected Index Not Set"));
	}
}

void UMainMenu::OpenJoinMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);	
	if (MenuInterface != nullptr)
	{
		MenuInterface->RefreshServerList();
	}
}

void UMainMenu::OpenHostMenu()
{
	MenuSwitcher->SetActiveWidget(HostMenu);
}

void UMainMenu::OpenMainMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(MainMenu);
}