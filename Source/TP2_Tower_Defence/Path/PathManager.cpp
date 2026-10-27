// Fill out your copyright notice in the Description page of Project Settings.


#include "PathManager.h"
#include "DrawDebugHelpers.h"

// Sets default values
APathManager::APathManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APathManager::BeginPlay()
{
	Super::BeginPlay();
	
	if (!GridTerrain)
	{
		UE_LOG(LogTemp, Error, TEXT("The variable GridTerrain is null"));
		return;
	}
	
	UGridComponent* GridComponent = GridTerrain->GridComponent;
	if (!IsValid(GridComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("GridComponent is invalid"));
		return;
	}
	
	//Définir la grille de départ et la grille d'arrivé
	int32 GridSizeX = GridTerrain->GridSizeX;
	int32  GridSizeY = GridTerrain->GridSizeY;
	
	
	FGridCell* StartCell = GridComponent->GetCell(GridSizeX/2,0);
	FGridCell* EndCell = GridComponent->GetCell(GridSizeX/2, GridSizeY-1);
	
	if (!StartCell || !EndCell)
	{
		UE_LOG(LogTemp,Error,TEXT("Failed to retrieve Start and End Cells"));
		return;
	}
	
	StartCell->bIsOccupied = true; //To prevent player building
	EndCell->bIsOccupied = true; //To prevent player building
	
	StartCoordinate = StartCell->Coordinates;
	EndCoordinate = EndCell->Coordinates;
	
	UWorld* World = GetWorld();
	
	if (!World)
		return;
	
	DrawDebugBox(World,GridComponent->GridToWorld(StartCoordinate),FVector(GridTerrain->CellSize/2),FColor::Blue,true);
	DrawDebugBox(World,GridComponent->GridToWorld(EndCoordinate),FVector(GridTerrain->CellSize/2),FColor::Blue,true);
}

// Called every frame
void APathManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APathManager::DrawDebugPath()
{
	UWorld* World = GetWorld();
	
	if (!World)
		return;
	
}

