// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyGameMode.h"
#include "PuzzlePlatformsGameInstance.h"

void ALobbyGameMode::PostLogin(APlayerController *NewPlayer)
{
	if (!ensure(NewPlayer != nullptr)) return;
	NumberOfPlayers++;
	UE_LOG(LogTemp, Warning, TEXT("Player %s connected!"), *NewPlayer->GetName());
	if (NumberOfPlayers >= NumberOfPlayersToStart)
	{
		GetWorldTimerManager().SetTimer(GameStartTimer, this, &ALobbyGameMode::StartGame, 30);
	}
	Super::PostLogin(NewPlayer);
}

void ALobbyGameMode::Logout(AController * Exiting)
{
	if (!ensure(Exiting != nullptr)) return;
	UE_LOG(LogTemp, Warning, TEXT("Player %s disconnected!"), *Exiting->GetName());
	if (NumberOfPlayers > 0)
	{
		NumberOfPlayers--;
	}
	Super::Logout(Exiting);
}

void ALobbyGameMode::StartGame()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	bUseSeamlessTravel = true;
	World->ServerTravel("/Game/PuzzlePlatforms/Maps/Game");	
	UPuzzlePlatformsGameInstance* GameInstance =  Cast<UPuzzlePlatformsGameInstance>(GetGameInstance());
	if (!ensure(GameInstance != nullptr)) return;
	GameInstance->StartSession();
}
