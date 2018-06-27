// Fill out your copyright notice in the Description page of Project Settings.

#include "BreakOutGameModeBase.h"
#include "Engine/World.h"
#include "GroupBricks.h"
#include "Brick.h"



void ABreakOutGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SpawnLocation = FVector(-130.0f, 0.0f, 200.0f);
	SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
	TotalBricks = 80;//80.0f;
	Spacing = 25.0f;
	
	SpawnGroupOfBricks();
 
}

void ABreakOutGameModeBase::SpawnGroupOfBricks()
{
	auto World = GetWorld();
	if (World)
	{
		GroupBrickRef = World->SpawnActor<AGroupBricks>(GroupBricksBP, SpawnLocation, SpawnRotation);

		if (GroupBrickRef)
		{
			for (int32 index = 0; index < TotalBricks; ++index)
			{
				int32 HorizontalBricks = index % 20;
				int32 VerticalBricks = index / 20;
				Brick = SpawnNewBrick(HorizontalBricks, VerticalBricks);
				Brick->SetFlipBookEvent(VerticalBricks);
				Brick->AttachToActor(GroupBrickRef, FAttachmentTransformRules::KeepRelativeTransform);
			}
		}
		
	}

}

ABrick * ABreakOutGameModeBase::SpawnNewBrick(int32 X, int32 Y)
{
	float DirectionX = X;
	float DirectionY = Y;
	FVector Location = FVector(DirectionX, 0.0f, DirectionY);

	FVector StartLocation = (Location*Spacing) + SpawnLocation;
	auto Bricks = GetWorld()->SpawnActor<ABrick>(BrickBP, StartLocation, SpawnRotation);
	return Bricks;
}

