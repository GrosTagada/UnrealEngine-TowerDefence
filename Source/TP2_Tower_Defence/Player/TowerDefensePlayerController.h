// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "TP2_Tower_Defence/Path/PathManager.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TP2_Tower_Defence/Placement Manager/BuildingPlacementManager.h"
#include "TP2_Tower_Defence/Tower/DataAssets/TowerDataAsset.h"
#include "TowerDefensePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TP2_TOWER_DEFENCE_API ATowerDefensePlayerController : public APlayerController
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Inputs")
	TObjectPtr<UInputMappingContext> InputMappingContext;
	UPROPERTY(EditAnywhere, Category = "Inputs")
	TObjectPtr<UInputAction> ClickAction;
	
	UPROPERTY(EditAnywhere, Category = "RayTrace")
	TEnumAsByte<ETraceTypeQuery>GroundChannel;
	
	UPROPERTY()
	TObjectPtr<APathManager> PathManager;

	
protected:
	ATowerDefensePlayerController();
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;
	
	void OnLeftClick();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UBuildingPlacementManager> BuildingPlacementManager;
	
public:
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void SelectTower(UTowerDataAsset* TowerDataAsset);
	void ConfirmTowerPlacement();
};
