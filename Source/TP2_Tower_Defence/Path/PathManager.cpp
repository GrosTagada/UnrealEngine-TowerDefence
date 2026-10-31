// Fill out your copyright notice in the Description page of Project Settings.


#include "PathManager.h"
#include "DrawDebugHelpers.h"
#include "TP2_Tower_Defence/GameModes/TowerDefenceGameMode.h"

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
	
	PathCoordinates.Add(StartCoordinate);
	
	UWorld* World = GetWorld();
	
	if (!World)
		return;
	
	DrawDebugBox(World,GridComponent->GridToWorld(StartCoordinate),FVector(GridTerrain->CellSize/2),FColor::Green,true);
	DrawDebugBox(World,GridComponent->GridToWorld(EndCoordinate),FVector(GridTerrain->CellSize/2),FColor::Red,true);
}

bool APathManager::IsCellNextToCell(FIntPoint CellToTest, FIntPoint CellNext)
{
	const int32 DeltaX = FMath::Abs(CellToTest.X - CellNext.X);
	const int32 DeltaY = FMath::Abs(CellToTest.Y - CellNext.Y);
	
	return DeltaX + DeltaY == 1;
}

bool APathManager::CompletePath()
{
	if (PathCoordinates.Num() < 2)
	{
		return false;
	}
	
	if (PathCoordinates[0] != StartCoordinate || PathCoordinates.Last() != EndCoordinate)
	{
		return false;
	}
	
	for (int32 i = 1; i < PathCoordinates.Num(); ++i)
	{
		if (!IsCellNextToCell(PathCoordinates[i - 1],PathCoordinates[i]))
		{
			return false;
		}
	}
	
	bIsPathEditBlocked = true;

	UE_LOG(LogTemp, Log, TEXT("Path completed successfully"));

	return true;
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

void APathManager::TrySelectCell(FVector WorldPosition)
{
	if (bIsPathEditBlocked)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red,TEXT("Path edit is blocked"));
		return;
	}
	
	if (!IsValid(GridTerrain))
	{
		UE_LOG(LogTemp, Error, TEXT("GridTerrain is invalid"));
		return;
	}
	
	UGridComponent* GridComponent = GridTerrain->GetGridComponent();
	
	if (!IsValid(GridComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("GridComponent is invalid"));
		return;
	}
	
	if (PathCoordinates.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("Path has no starting cell"));
		return;
	}
	
	FIntPoint OutCoordinate;
	if (!GridComponent->WorldToGrid(WorldPosition,OutCoordinate))
	{
		//Show some UI
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red,TEXT("Failed to select cell"));
		return;
	}
	
	FGridCell* Cell = GridComponent->GetCell(OutCoordinate.X,OutCoordinate.Y);
	
	if (!Cell)
	{
		return;
	}
	
	const FIntPoint CellCoordinates = Cell->Coordinates;
	const FIntPoint PreviousCoordinate = PathCoordinates.Last();
	
	if (PathCoordinates.Contains(CellCoordinates))
	{
		UE_LOG(LogTemp, Warning, TEXT("Cell already belongs to the path"));
		return;
	}
	
	if (Cell->Coordinates == EndCoordinate)
	{
		if (!IsCellNextToCell(CellCoordinates, PreviousCoordinate))
		{
			UE_LOG(LogTemp, Warning, TEXT("End cell is not adjacent"));
			return;
		}
		
		PathCoordinates.Add(EndCoordinate);
		
		if (!CompletePath())
		{
			return;
		}
		
		bIsPathEditBlocked = true;
		
		//Show some UI
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Emerald,TEXT("Path completed"));
		
		UWorld* World = GetWorld();
		if (ATowerDefenceGameMode* GameMode = Cast<ATowerDefenceGameMode>(World->GetAuthGameMode()))
			GameMode->OnPathCompleted();
		return;
	}
	
	if (Cell->bIsOccupied)
	{
		//Show some UI
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red,TEXT("Cell is occupied"));
		return;
	}
	
	if (!IsCellNextToCell(CellCoordinates,PreviousCoordinate))
	{
		//Show some UI
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red,TEXT("Cell is not next to previous cell"));
		return;
	}
	
	Cell->bIsOccupied = true;
	PathCoordinates.Add(Cell->Coordinates);
	
	DrawDebugCell(Cell->Coordinates);
}

void APathManager::DrawDebugCell(FIntPoint CellCoordinate)
{
	UGridComponent* GridComponent = GridTerrain->GetGridComponent();
	
	UWorld* World = GetWorld();
	
	if (!World)
		return;
	
	DrawDebugBox(World,GridComponent->GridToWorld(CellCoordinate),FVector(GridTerrain->CellSize/2),FColor::Blue,true);
}


