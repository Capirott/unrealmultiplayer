// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"



AMovingPlatform::AMovingPlatform() 
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}


void AMovingPlatform::Tick(float deltaTime) 
{
	Super::Tick(deltaTime);

	if (HasAuthority()) 
	{
		FVector location = GetActorLocation();
		location += FVector(speed * deltaTime, 0, 0);
		SetActorLocation(location);
	}
}