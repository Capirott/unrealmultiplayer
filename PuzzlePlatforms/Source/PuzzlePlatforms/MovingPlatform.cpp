#include "MovingPlatform.h"



AMovingPlatform::AMovingPlatform() 
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}


void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority()) 
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority()) 
	{
		FVector Location = GetActorLocation();
		FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
		Location += Speed * DeltaTime * Direction;
		SetActorLocation(Location);
		if (FVector::Distance(Location, GlobalStartLocation) >= FVector::Distance(GlobalStartLocation, GlobalTargetLocation))
		{
			FVector Swap = GlobalStartLocation;
			GlobalStartLocation = GlobalTargetLocation;
			GlobalTargetLocation = Swap;
		}
	}
}