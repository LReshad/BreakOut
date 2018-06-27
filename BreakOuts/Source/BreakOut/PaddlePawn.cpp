// Fill out your copyright notice in the Description page of Project Settings.

#include "PaddlePawn.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "BreakOutMovementComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
// Sets default values
APaddlePawn::APaddlePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(FName(FName("RooTComponent")));
	//BoxCollision = CreateDefaultSubobject<UBoxComponent>(FName("BoxCollisiion"));
	PaddleFlipBook = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("PaddleFlipBook"));
	PaddleFlipBook->SetupAttachment(RootComponent);
	//BoxCollision->SetupAttachment(PaddleFlipBook);
	MovementComponent = CreateDefaultSubobject<UBreakOutMovementComponent>(FName("MovementComponent"));


	PaddleFlipBook->SetSimulatePhysics(true);
	PaddleFlipBook->SetEnableGravity(true);
	PaddleFlipBook->SetLinearDamping(0.0f);

	PaddleFlipBook->SetConstraintMode(EDOFMode::SixDOF);
	PaddleFlipBook->GetBodyInstance()->bLockXRotation = true;
	PaddleFlipBook->GetBodyInstance()->bLockYRotation = true;
	PaddleFlipBook->GetBodyInstance()->bLockZRotation = true;
	PaddleFlipBook->GetBodyInstance()->bLockXTranslation = false;
	PaddleFlipBook->GetBodyInstance()->bLockYTranslation = true;
	PaddleFlipBook->GetBodyInstance()->bLockZTranslation = true;
}

// Called when the game starts or when spawned
void APaddlePawn::BeginPlay()
{
	Super::BeginPlay();

	PaddleFlipBook->SetAngularDamping(0.0f);



}

// Called every frame
void APaddlePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto MovementInput = GetPendingMovementInputVector();
	auto Transform = PaddleFlipBook->GetRelativeTransform();
	Transform.AddToTranslation(MovementInput*DeltaTime*80.0f);
	PaddleFlipBook->SetRelativeTransform(Transform, true);

	

}

// Called to bind functionality to input
void APaddlePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Move", this, &APaddlePawn::Move);
}

void APaddlePawn::Move(float AxisValue)
{
	AxisValue = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
	FVector Direction = FVector(10.0f, 0.0f, 0.0f);
	MovementComponent->ConsumeInputVector();
	AddMovementInput(Direction, AxisValue);
	Velocity = (AxisValue* 150.0f);

}

float APaddlePawn::GetVelocityfromPaddle()
{
	return Velocity;
}

