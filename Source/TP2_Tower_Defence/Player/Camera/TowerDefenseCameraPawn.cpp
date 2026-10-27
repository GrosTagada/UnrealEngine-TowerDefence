// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerDefenseCameraPawn.h"

// Sets default values
ATowerDefenseCameraPawn::ATowerDefenseCameraPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(Root);

	Camera->SetRelativeLocation(FVector(0.f, 0.f, 1200.f));
	Camera->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
}


// Called every frame
void ATowerDefenseCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATowerDefenseCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

