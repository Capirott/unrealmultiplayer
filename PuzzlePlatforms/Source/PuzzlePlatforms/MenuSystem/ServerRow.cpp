// Fill out your copyright notice in the Description page of Project Settings.

#include "ServerRow.h"
#include "MainMenu.h"

#include "Components/Button.h"	

void UServerRow::Setup(UMainMenu *Parent, uint32 Index)
{
	if (!ensure(Parent != nullptr)) return;
	if (!ensure(RowButton != nullptr)) return;
	this->Parent = Parent;
	this->Index = Index;
	RowButton->OnClicked.AddDynamic(this, &UServerRow::OnClicked);
}

void UServerRow::OnClicked()
{
	if (!ensure(Parent != nullptr)) return;
	Parent->SelectIndex(Index);
}

