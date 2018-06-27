// Fill out your copyright notice in the Description page of Project Settings.

#include "Brick.h"
#include "PaperFlipbookComponent.h"
#include "Engine/World.h"
#include "PowerUp.h"


// Sets default values
ABrick::ABrick()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BrickFlipBook = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("BrickFlipBook"));
	RootComponent = BrickFlipBook;
}

// Called when the game starts or when spawned
void ABrick::BeginPlay()
{
	Super::BeginPlay();
	BrickFlipBook->OnComponentHit.AddDynamic(this, &ABrick::OnHit);
	
}

// Called every frame
void ABrick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	 
}


//Create a bool according to the percentage input value
bool ABrick::bChance(int32 Percentage)
{
	int32 iLuck = (FMath::RandRange(0, 100 / Percentage));
	if (iLuck == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}


///HitEvent
void ABrick::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	bRand = bChance(3);
	
	if (bRand)
	{
		auto World = GetWorld();
		//Spawn The power up Actor
		if (World)
		{
			FVector Location = GetActorLocation();
			FRotator Rotation = GetActorRotation();
			World->SpawnActor<APowerUp>(PowerUp_BP, Location, Rotation);
			Destroy();
		}
	}
	else
	{
		Destroy();
	}
	
	
}



