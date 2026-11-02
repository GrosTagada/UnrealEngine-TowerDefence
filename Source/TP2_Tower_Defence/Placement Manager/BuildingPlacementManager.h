// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TP2_Tower_Defence/Grid/GridComponent.h"
#include "TP2_Tower_Defence/Tower/Tower.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TP2_Tower_Defence/Ressources/ResourceManagerComponent.h"
#include "TP2_Tower_Defence/Tower/DataAssets/TowerDataAsset.h"
#include "BuildingPlacementManager.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TP2_TOWER_DEFENCE_API UBuildingPlacementManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UBuildingPlacementManager();

	void InitializePlacement(UGridComponent* InGridComponent,APathManager* InPathManager);

	void SelectTower(UTowerDataAsset* TowerDataAsset);

	void UpdatePlacementPreview(const FVector& WorldPosition);

	void ConfirmPlacement();

protected:
	UPROPERTY()
	TObjectPtr<UGridComponent> GridComponent;

	UPROPERTY()
	TObjectPtr<APathManager> PathManager;
	
	UPROPERTY()
	TObjectPtr<UResourceManagerComponent> ResourceManager;
	
	UPROPERTY()
	TObjectPtr<UTowerDataAsset> SelectedTowerData;

	FIntPoint HoveredCoordinates = FIntPoint(-1, -1);

	bool bIsPlacementValid = false;
	
	UPROPERTY(EditDefaultsOnly, Category = "Placement")
	TSubclassOf<AActor> PreviewClass;

	UPROPERTY()
	TObjectPtr<AActor> PreviewActor;

	UPROPERTY(EditDefaultsOnly, Category = "Placement")
	TObjectPtr<UMaterialInterface> ValidMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "Placement")
	TObjectPtr<UMaterialInterface> InvalidMaterial;

	bool CanPlaceTower(const FIntPoint& Coordinates) const;

	ATower* PlaceTower(const FIntPoint& Coordinates);
	void CreatePreview();
	void UpdatePreviewMaterial();
};
