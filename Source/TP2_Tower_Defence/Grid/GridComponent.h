// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FGridCell.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GridComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TP2_TOWER_DEFENCE_API UGridComponent : public UActorComponent
{
	GENERATED_BODY()
	
	int32 SizeX = 16;
	int32 SizeY = 16;
	float CellSize = 100.0f;
	FVector GridOrigin = FVector::ZeroVector;
	
	UPROPERTY()
	TArray<FGridCell> Cells;

	// Convertit les coordonnees 2D en index du tableau
	int32 GetCellIndex(int32 X, int32 Y) const;
	
public:	
	UGridComponent();
	
	void InitializeGrid(int32 InSizeX,int32 InSizeY,float InCellSize,FVector InOrigin);
	
	FGridCell* GetCell(int32 X, int32 Y);
	const FGridCell* GetCell(int32 X, int32 Y) const;
	
	bool WorldToGrid(const FVector& WorldPosition,FIntPoint& OutCoordinates) const;
	FVector GridToWorld(const FIntPoint& Coordinates) const;
	
	bool SetCellOccupied(const FIntPoint& Coordinates,bool bOccupied);
	
	bool IsValidCoordinate(int32 X, int32 Y) const;
	
	int32 GetSizeX() const { return SizeX; }
	int32 GetSizeY() const { return SizeY; }
	float GetCellSize() const { return CellSize; }
	int GetCellCount() const { return Cells.Num();}
	
	void DrawDebugGrid() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
};
