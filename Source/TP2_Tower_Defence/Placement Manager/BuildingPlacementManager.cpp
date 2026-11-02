#include "BuildingPlacementManager.h"

#include "Engine/World.h"


UBuildingPlacementManager::UBuildingPlacementManager()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UBuildingPlacementManager::InitializePlacement(UGridComponent* InGridComponent,APathManager* InPathManager)
{
    GridComponent = InGridComponent;
    PathManager = InPathManager;
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
    return IsValid(GridComponent)&& GridComponent->CanBuildAt(Coordinates);
}

void UBuildingPlacementManager::ConfirmPlacement()
{
    if (!bIsPlacementValid || !SelectedTowerData)
    {
        return;
    }

    PlaceTower(HoveredCoordinates);
}

void UBuildingPlacementManager::PlaceTower(const FIntPoint& Coordinates)
{
    if (!CanPlaceTower(Coordinates))
    {
        return;
    }

    FVector SpawnPosition = GridComponent->GridToWorld(Coordinates);

    FActorSpawnParameters SpawnParameters;

    SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    ATower* Tower = GetWorld()->SpawnActor<ATower>(ATower::StaticClass(),SpawnPosition,FRotator::ZeroRotator,SpawnParameters);

    if (!IsValid(Tower))
    {
        return;
    }
    
    Tower->InitializeTower(SelectedTowerData);
    
    GridComponent->SetCellOccupied(Coordinates, true);
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
