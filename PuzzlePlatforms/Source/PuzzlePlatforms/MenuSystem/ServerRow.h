// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerRow.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UServerRow : public UUserWidget
{
	GENERATED_BODY()

private:
	
	UPROPERTY()
	class UMainMenu* Parent;
	
	uint32 Index;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* RowButton;

	UFUNCTION()
	void OnClicked();

public:

	UPROPERTY(BlueprintReadOnly)
	bool Selected = false;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ServerName;	

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HostUser;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ConnectionFraction;
	
	void Setup(class UMainMenu* Parent, uint32 Index);
};
