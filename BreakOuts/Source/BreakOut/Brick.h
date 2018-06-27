// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Brick.generated.h"

UCLASS()
class BREAKOUT_API ABrick : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABrick();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "BrickFlipBook")
	class UPaperFlipbookComponent * BrickFlipBook = nullptr;

	UFUNCTION(BlueprintImplementableEvent,Category="SetFlipBook")
	void SetFlipBookEvent(int32 Index);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	bool bRand;

	bool bChance(int32 Percentage);

	UPROPERTY(EditAnywhere, Category="Spawn")
	TSubclassOf<class APowerUp>PowerUp_BP;
	
	
};
