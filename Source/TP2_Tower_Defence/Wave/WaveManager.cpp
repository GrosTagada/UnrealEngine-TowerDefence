// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManager.h"

#include "TP2_Tower_Defence/GameStates/TowerDefenceGameState.h"


// Sets default values
AWaveManager::AWaveManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


// Called when the game starts or when spawned
void AWaveManager::BeginPlay()
{
	Super::BeginPlay();
}

void AWaveManager::SpawnEnemy()
{
	if (!IsValid(EnemyClass) || !IsValid(PathManager))
		return;

	const TArray<FIntPoint>& PathCoordinates = PathManager->GetPathCoordinates();

	UGridComponent* GridComponent = PathManager->GetGridComponent();

	if (!IsValid(GridComponent) || PathCoordinates.IsEmpty())
		return;
	

	const FVector SpawnPosition = GridComponent->GridToWorld(PathCoordinates[0]);

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AEnemy* Enemy = GetWorld()->SpawnActor<AEnemy>(EnemyClass,SpawnPosition,FRotator::ZeroRotator,SpawnParameters);

	if (!IsValid(Enemy))
		return;

	Enemy->InitializeEnemy(PathCoordinates, GridComponent);
}

// Called every frame
void AWaveManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWaveManager::StartWave()
{
	SpawnEnemy();
}

