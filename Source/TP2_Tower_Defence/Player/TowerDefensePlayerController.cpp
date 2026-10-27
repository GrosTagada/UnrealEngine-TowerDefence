// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerDefensePlayerController.h"

#include "Engine/LocalPlayer.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

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
	
	PathManager = Cast<APathManager>(UGameplayStatics::GetActorOfClass(GetWorld(),APathManager::StaticClass()));

	if (!IsValid(PathManager))
	{
		UE_LOG(LogTemp, Error, TEXT("PathManager not found in the level"));
		return;
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
	if (!GroundChannel)
		return;
	
	FHitResult HitResult;
	GetHitResultUnderCursorByChannel(GroundChannel,false,HitResult);
	
	PathManager->TrySelectCell(HitResult.ImpactPoint);
}
