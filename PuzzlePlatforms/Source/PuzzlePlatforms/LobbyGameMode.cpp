// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyGameMode.h"

void ALobbyGameMode::PostLogin(APlayerController *NewPlayer)
{
	if (!ensure(NewPlayer != nullptr)) return;
	NumberOfPlayers++;
	UE_LOG(LogTemp, Warning, TEXT("Player %s connected!"), *NewPlayer->GetName());
	if (NumberOfPlayers == MaxNumberOfPlayers)
	{
		UE_LOG(LogTemp, Warning, TEXT("Number of max players reached!"));
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
