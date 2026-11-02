// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerDefensePlayerController.h"

#include "Engine/LocalPlayer.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "TP2_Tower_Defence/GameStates/TowerDefenceGameState.h"
#include "TP2_Tower_Defence/GameStates/Enum/EGamePhase.h"

ATowerDefensePlayerController::ATowerDefensePlayerController()
{
	BuildingPlacementManager = CreateDefaultSubobject<UBuildingPlacementManager>(TEXT("BuildingPlacementManager"));
}

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
	
	if (IsValid(PathManager))
	{
		BuildingPlacementManager->InitializePlacement(PathManager->GetGridComponent(),PathManager);
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
	
	ATowerDefenceGameState* GameState = GetWorld()->GetGameState<ATowerDefenceGameState>();

	if (!IsValid(GameState))
	{
		return;
	}
	
	if (GameState->GetGamePhase() == EGamePhase::Preparation)
		ConfirmTowerPlacement();
	if (GameState->GetGamePhase() == EGamePhase::PathSelection)
		PathManager->TrySelectCell(HitResult.ImpactPoint);
}

void ATowerDefensePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!BuildingPlacementManager)
	{
		return;
	}

	FHitResult HitResult;

	if (GetHitResultUnderCursorByChannel(GroundChannel,false,HitResult))
	{
		BuildingPlacementManager->UpdatePlacementPreview(HitResult.Location);
	}
}

void ATowerDefensePlayerController::SelectTower(UTowerDataAsset* TowerDataAsset)
{
	BuildingPlacementManager->SelectTower(TowerDataAsset);
}

void ATowerDefensePlayerController::ConfirmTowerPlacement()
{
	ATowerDefenceGameState* GameState = GetWorld()->GetGameState<ATowerDefenceGameState>();

	if (!IsValid(GameState) || GameState->GetGamePhase() != EGamePhase::Preparation)
	{
		return;
	}
	BuildingPlacementManager->ConfirmPlacement();
}