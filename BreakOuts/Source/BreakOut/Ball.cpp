// Fill out your copyright notice in the Description page of Project Settings.

#include "Ball.h"
#include "PaperSpriteComponent.h"
#include "PaddlePawn.h"
#include "Engine/World.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Ball = CreateDefaultSubobject<UPaperSpriteComponent>(FName("Ball"));

	Ball->SetSimulatePhysics(true);
	Ball->SetEnableGravity(false);
	Ball->SetNotifyRigidBodyCollision(true);
	//Ball->SetLinearDamping(0.0f);
	//Ball->SetAngularDamping(0.0f);
	Ball->SetConstraintMode(EDOFMode::SixDOF);
	Ball->GetBodyInstance()->bLockXRotation = true;
	Ball->GetBodyInstance()->bLockYRotation = true;
	Ball->GetBodyInstance()->bLockZRotation = true;
	Ball->GetBodyInstance()->bLockXTranslation = false;
	Ball->GetBodyInstance()->bLockYTranslation = true;
	Ball->GetBodyInstance()->bLockZTranslation = false;

	Velocity = 0.0f;
	

}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();

	Ball->SetEnableGravity(false);
	Direction = FVector(0.0f, 0.0f, -1.0f);
	Velocity = 450.0f;
	Time = 0.0f;

	//Get the Location of the Ball at Begin play
	Location = Ball->GetComponentLocation();

	Ball->OnComponentBeginOverlap.AddDynamic(this, &ABall::BeginOverlap);
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Time += DeltaTime;
	//Move the ball after 2 seconds
	if (Time >2)
	{
		MoveBall();
	}
	

	

}

void ABall::NotifyHit(UPrimitiveComponent * MyComp, AActor * Other, UPrimitiveComponent * OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult & Hit)
{
	Ball->SetAllPhysicsAngularVelocity(FVector(0.0f, 0.0f, 0.0f));
	Ball->SetAllPhysicsLinearVelocity(FVector(0.0f, 0.0f, 0.0f));

	//Move to the Mirror direction
	Direction = Direction.MirrorByVector(HitNormal);

	auto Name = Other->GetName();

	

	if (Name == "PaddlePawn_BP_C_0")
	{
		APaddlePawn * PaddlePawn = (APaddlePawn*)Other;
		//Get Velocity from paddle to the Direction
		Direction.X += (PaddlePawn->GetVelocityfromPaddle() / Velocity);
		
	}
}


//Moving the Ball in every frame
void ABall::MoveBall()
{
	auto DeltaTime = GetWorld()->DeltaTimeSeconds;
	auto Transform = Ball->GetRelativeTransform();
	Transform.AddToTranslation(Direction*DeltaTime* Velocity);
	Ball->SetRelativeTransform(Transform, true);
	

}


//Overlapping event
void ABall::BeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	auto Name = OtherActor->GetName();
	if (Name== "Cube4_Blueprint")
	{
		
		Ball->SetWorldLocation(Location);
		Direction.Set(0.0f, 0.0f, -1.0f);
		Time = 0.0f;
		
	}
}

