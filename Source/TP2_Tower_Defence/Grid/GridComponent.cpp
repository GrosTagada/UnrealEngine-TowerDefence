// Fill out your copyright notice in the Description page of Project Settings.


#include "GridComponent.h"
#include "DrawDebugHelpers.h"

UGridComponent::UGridComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UGridComponent::InitializeGrid(int32 InSizeX,int32 InSizeY,float InCellSize,FVector InOrigin)
{
    // Evite les dimensions invalides
    SizeX = FMath::Max(1, InSizeX);
    SizeY = FMath::Max(1, InSizeY);
    CellSize = FMath::Max(1.0f, InCellSize);

    GridOrigin = InOrigin;

    // Reinitialise les cases
    Cells.Empty();
    Cells.Reserve(SizeX * SizeY);

    // Cree toutes les cases
    for (int32 Y = 0; Y < SizeY; Y++)
    {
        for (int32 X = 0; X < SizeX; X++)
        {
            Cells.Emplace(X, Y);
        }
    }
}

int32 UGridComponent::GetCellIndex(int32 X, int32 Y) const
{
    return X + Y * SizeX;
}

bool UGridComponent::IsValidCoordinate(int32 X, int32 Y) const
{
    return X >= 0 && X < SizeX
        && Y >= 0 && Y < SizeY;
}

FGridCell* UGridComponent::GetCell(int32 X, int32 Y)
{
    if (!IsValidCoordinate(X, Y))
    {
        return nullptr;
    }

    const int32 Index = GetCellIndex(X, Y);

    if (!Cells.IsValidIndex(Index))
    {
        return nullptr;
    }

    return &Cells[Index];
}

const FGridCell* UGridComponent::GetCell(int32 X,int32 Y) const
{
    if (!IsValidCoordinate(X, Y))
    {
        return nullptr;
    }

    const int32 Index = GetCellIndex(X, Y);

    if (!Cells.IsValidIndex(Index))
    {
        return nullptr;
    }

    return &Cells[Index];
}

bool UGridComponent::WorldToGrid(const FVector& WorldPosition,FIntPoint& OutCoordinates) const
{
    // Position relative a l'origine de la grille
    const FVector LocalPosition = WorldPosition - GridOrigin;

    // Conversion en coordonnees de grille
    const int32 X = FMath::FloorToInt(LocalPosition.X / CellSize);

    const int32 Y = FMath::FloorToInt(LocalPosition.Y / CellSize);

    if (!IsValidCoordinate(X, Y))
    {
        return false;
    }

    OutCoordinates = FIntPoint(X, Y);

    return true;
}

FVector UGridComponent::GridToWorld(const FIntPoint& Coordinates) const
{
    // Centre de la case
    const float WorldX = GridOrigin.X + (Coordinates.X + 0.5f) * CellSize;

    const float WorldY = GridOrigin.Y + (Coordinates.Y + 0.5f) * CellSize;

    return FVector(WorldX,WorldY,GridOrigin.Z);
}

bool UGridComponent::SetCellOccupied(const FIntPoint& Coordinates,bool bOccupied)
{
    FGridCell* Cell = GetCell(Coordinates.X,Coordinates.Y);

    if (Cell == nullptr)
    {
        return false;
    }

    Cell->bIsOccupied = bOccupied;

    return true;
}


void UGridComponent::DrawDebugGrid() const
{
    UWorld* World = GetWorld();

    if (!World)
    {
        return;
    }

    // Dessine les lignes verticales de la grille
    for (int32 X = 0; X <= SizeX; X++)
    {
        const FVector Start(GridOrigin.X + X * CellSize, GridOrigin.Y, GridOrigin.Z);

        const FVector End(GridOrigin.X + X * CellSize,GridOrigin.Y + SizeY * CellSize,GridOrigin.Z);

        DrawDebugLine(World,Start,End,FColor::Green,true,-1.0f,0,2.0f);
    }

    // Dessine les lignes horizontales de la grille
    for (int32 Y = 0; Y <= SizeY; Y++)
    {
        const FVector Start(GridOrigin.X,GridOrigin.Y + Y * CellSize,GridOrigin.Z);

        const FVector End(GridOrigin.X + SizeX * CellSize,GridOrigin.Y + Y * CellSize,GridOrigin.Z);

        DrawDebugLine(World,Start,End,FColor::Green,true,-1.0f,0,2.0f);
    }
}

void UGridComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UGridComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
