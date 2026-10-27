// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerDefensePlayerController.h"
#include "Engine/LocalPlayer.h"
#include "DrawDebugHelpers.h"

void ATowerDefensePlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	SetInputMode(FInputModeGameAndUI());
	bShowMouseCursor = true;
	
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				InputSubsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}
}

void ATowerDefensePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (ClickAction)
		{
			EnhancedInput->BindAction(ClickAction,ETriggerEvent::Started,this,&ATowerDefensePlayerController::OnLeftClick);
		}
	}
}

void ATowerDefensePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ATowerDefensePlayerController::OnLeftClick()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Blue,TEXT("Left mouse click"));
	
	if (!GroundChannel)
		return;
	
	FHitResult HitResult;
	GetHitResultUnderCursorByChannel(GroundChannel,false,HitResult);
	
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Emerald,FString::Printf(TEXT("Hit point : %s"),*HitResult.ImpactPoint.ToString()));
	
	UWorld* World = GetWorld();
	if (World)
		DrawDebugLine(World,HitResult.TraceStart,HitResult.TraceEnd,FColor::Red,true,-1.0f,0,2.0f);
}
