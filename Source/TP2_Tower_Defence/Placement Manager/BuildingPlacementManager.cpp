#include "BuildingPlacementManager.h"

#include "Engine/World.h"
#include "TP2_Tower_Defence/GameModes/TowerDefenceGameMode.h"


UBuildingPlacementManager::UBuildingPlacementManager()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UBuildingPlacementManager::InitializePlacement(UGridComponent* InGridComponent,APathManager* InPathManager)
{
    GridComponent = InGridComponent;
    PathManager = InPathManager;
    
    ATowerDefenceGameMode* GameMode = GetWorld()->GetAuthGameMode<ATowerDefenceGameMode>();

    if (IsValid(GameMode))
    {
        ResourceManager = GameMode->GetResourceManager();
    }
}

void UBuildingPlacementManager::SelectTower(UTowerDataAsset* TowerData)
{
    if (!IsValid(TowerData))
    {
        return;
    }

    SelectedTowerData = TowerData;

    if (!IsValid(PreviewActor))
    {
        CreatePreview();
    }

    if (IsValid(PreviewActor))
    {
        PreviewActor->SetActorHiddenInGame(false);

        UStaticMeshComponent* PreviewMesh = PreviewActor->FindComponentByClass<UStaticMeshComponent>();

        if (IsValid(PreviewMesh))
        {
            PreviewMesh->SetStaticMesh(TowerData->TowerMesh.LoadSynchronous());
        }
    }
}

void UBuildingPlacementManager::UpdatePlacementPreview(const FVector& WorldPosition)
{
    if (!IsValid(PreviewActor) || !IsValid(GridComponent) || !SelectedTowerData)
    {
        return;
    }

    if (!GridComponent->WorldToGrid(WorldPosition,HoveredCoordinates))
    {
        bIsPlacementValid = false;
        PreviewActor->SetActorHiddenInGame(true);
        return;
    }

    FVector GridPosition = GridComponent->GridToWorld(HoveredCoordinates);

    PreviewActor->SetActorLocation(GridPosition);
    PreviewActor->SetActorHiddenInGame(false);
    bIsPlacementValid = CanPlaceTower(HoveredCoordinates);

    UpdatePreviewMaterial();
}

bool UBuildingPlacementManager::CanPlaceTower(const FIntPoint& Coordinates) const
{
    if (!IsValid(SelectedTowerData) ||!IsValid(GridComponent) ||!IsValid(ResourceManager))
        return false;

    if (!ResourceManager->CanAfford(SelectedTowerData->BuildCost))
        return false;
    
    return GridComponent->CanBuildAt(Coordinates);
}

void UBuildingPlacementManager::ConfirmPlacement()
{
    if (!bIsPlacementValid || !SelectedTowerData)
    {
        return;
    }
    
    if (!IsValid(ResourceManager) ||!IsValid(SelectedTowerData))
        return;

    const int32 Cost = SelectedTowerData->BuildCost;

    if (!ResourceManager->CanAfford(Cost))
        return;

    ATower* SpawnedTower = PlaceTower(HoveredCoordinates);
    
    if (!IsValid(SpawnedTower))
        return;
    
    ResourceManager->TrySpendResources(Cost);
}

ATower* UBuildingPlacementManager::PlaceTower(const FIntPoint& Coordinates)
{
    if (!CanPlaceTower(Coordinates))
    {
        return nullptr;
    }

    FVector SpawnPosition = GridComponent->GridToWorld(Coordinates);

    FActorSpawnParameters SpawnParameters;

    SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    ATower* Tower = GetWorld()->SpawnActor<ATower>(ATower::StaticClass(),SpawnPosition,FRotator::ZeroRotator,SpawnParameters);

    if (!IsValid(Tower))
    {
        return nullptr;
    }
    
    Tower->InitializeTower(SelectedTowerData);
    
    GridComponent->SetCellOccupied(Coordinates, true);
    
    return Tower;
}

void UBuildingPlacementManager::CreatePreview()
{
    if (PreviewActor || !PreviewClass)
    {
        return;
    }

    PreviewActor = GetWorld()->SpawnActor<AActor>(PreviewClass,FVector::ZeroVector,FRotator::ZeroRotator);

    if (IsValid(PreviewActor))
    {
        PreviewActor->SetActorHiddenInGame(true);
    }
}

void UBuildingPlacementManager::UpdatePreviewMaterial()
{
    if (!IsValid(PreviewActor))
    {
        return;
    }

    UStaticMeshComponent* MeshComponent = PreviewActor->FindComponentByClass<UStaticMeshComponent>();

    if (!IsValid(MeshComponent))
    {
        return;
    }

    UMaterialInterface* Material = bIsPlacementValid ? ValidMaterial : InvalidMaterial;

    if (IsValid(Material))
    {
        MeshComponent->SetMaterial(0, Material);
    }
}
