// Fill out your copyright notice in the Description page of Project Settings.


#include "GridTerrain.h"

// Sets default values
AGridTerrain::AGridTerrain()
{
	PrimaryActorTick.bCanEverTick = false;

	// Cree le composant de grille
	GridComponent = CreateDefaultSubobject<UGridComponent>(TEXT("GridComponent"));
}

void AGridTerrain::BeginPlay()
{
	Super::BeginPlay();

	// Initialise la grille a partir des parametres du terrain
	GridComponent->InitializeGrid(GridSizeX,GridSizeY,CellSize,GetActorLocation());
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Emerald,
			FString::Printf(TEXT("Grid Initialized with : %d"),GridComponent->GetCellCount()));	
	}
	
	GridComponent->DrawDebugGrid();
}

// Called every frame
void AGridTerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

