// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TP2_Tower_Defence/Grid/GridTerrain.h"
#include "PathManager.generated.h"

UCLASS()
class TP2_TOWER_DEFENCE_API APathManager : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditInstanceOnly, Category="Grid")
	TObjectPtr<AGridTerrain> GridTerrain;
	
	FIntPoint StartCoordinate;
	FIntPoint EndCoordinate;
	
	TArray<FIntPoint> PathCoordinates;
	
	bool bIsPathEditBlocked = false;
public:
	// Sets default values for this actor's properties
	APathManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	bool IsCellNextToCell(FIntPoint CellToTest,FIntPoint CellNext);
	bool CompletePath();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void DrawDebugPath();
	void TrySelectCell(FVector WorldPosition);
	
	void DrawDebugCell(FIntPoint CellCoordinate);
};
