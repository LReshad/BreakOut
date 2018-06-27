// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BreakOutGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BREAKOUT_API ABreakOutGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	

	virtual void BeginPlay()override;
	
	UPROPERTY(EditAnywhere, Category="Spawn")
	TSubclassOf<class AGroupBricks>GroupBricksBP;
	
	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<class ABrick>BrickBP;

	AGroupBricks * GroupBrickRef = nullptr;

	ABrick * Brick = nullptr;

	FVector SpawnLocation;
	FRotator SpawnRotation;

	int32 TotalBricks;

	void SpawnGroupOfBricks();

	int32 Spacing;

	ABrick * SpawnNewBrick(int32 X, int32 Y);


};
