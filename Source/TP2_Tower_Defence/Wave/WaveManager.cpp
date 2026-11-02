// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManager.h"

#include "DataTable/FWaveData.h"
#include "DataTable/FWaveEnemyEntry.h"
#include "TP2_Tower_Defence/GameStates/TowerDefenceGameState.h"
#include "TP2_Tower_Defence/Enemies/DataAssets/EnemyDataAsset.h"
#include  "TP2_Tower_Defence/GameModes/TowerDefenceGameMode.h"

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


// Called every frame
void AWaveManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWaveManager::PrepareWave(const FWaveData* WaveData)
{
	if (!WaveData)
	{
		return;
	}

	EnemiesToSpawn.Empty();
	CurrentEnemyIndex = 0;
	bAllEnemiesSpawned = false;

	CurrentSpawnInterval = FMath::Max(0.1f, WaveData->SpawnInterval);

	for (const FWaveEnemyEntry& Entry : WaveData->Enemies)
	{
		if (!IsValid(Entry.EnemyData) || Entry.Quantity <= 0)
		{
			continue;
		}

		for (int32 i = 0; i < Entry.Quantity; ++i)
		{
			EnemiesToSpawn.Add(Entry.EnemyData);
		}
	}
}

void AWaveManager::StartWave()
{
	if (!IsValid(WavesDataTable))
	{
		UE_LOG(LogTemp, Error, TEXT("WavesDataTable is invalid"));
		return;
	}
	
	FString Wave = FString::Printf(TEXT("Wave_%d"),CurrentWaveNumber);
	
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Emerald,Wave);
	
	const FWaveData* WaveData = WavesDataTable->FindRow<FWaveData>(FName(Wave),TEXT("StartWave"));

	if (!WaveData)
	{
		UE_LOG(LogTemp, Error, TEXT("Wave not found"));
		return;
	}

	PrepareWave(WaveData);

	if (EnemiesToSpawn.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Wave is empty"));
		return;
	}
	
	CurrentWaveNumber +=1;
	
	SpawnNextEnemy();
	
	if (CurrentEnemyIndex < EnemiesToSpawn.Num())
	{
		GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle,this,&AWaveManager::SpawnNextEnemy,CurrentSpawnInterval,true);
	}
}

void AWaveManager::SpawnNextEnemy()
{
	if (CurrentEnemyIndex >= EnemiesToSpawn.Num())
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
		
		bAllEnemiesSpawned = true;

		CheckWaveCompletion();
		
		return;
	}

	UEnemyDataAsset* EnemyData = EnemiesToSpawn[CurrentEnemyIndex];

	if (!IsValid(EnemyData) )
	{
		++CurrentEnemyIndex;
		return;
	}

	const TArray<FIntPoint>& PathCoordinates = PathManager->GetPathCoordinates();

	UGridComponent* GridComponent = PathManager->GetGridComponent();

	if (!IsValid(GridComponent) || PathCoordinates.IsEmpty())
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
		return;
	}

	const FVector SpawnPosition = GridComponent->GridToWorld(PathCoordinates[0]);

	FActorSpawnParameters SpawnParameters;

	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AEnemy* Enemy = GetWorld()->SpawnActor<AEnemy>(EnemyData->EnemyClass.Get(),SpawnPosition,FRotator::ZeroRotator,SpawnParameters);

	if (IsValid(Enemy))
	{
		Enemy->InitializeEnemy(PathCoordinates, GridComponent,EnemyData);
		
		ActiveEnemies++;

		// On écoute la destruction de cet ennemi
		Enemy->OnDestroyed.AddDynamic(this,&AWaveManager::OnEnemyDestroyed);
	}

	++CurrentEnemyIndex;

	// Arrêter le Timer après le dernier ennemi
	if (CurrentEnemyIndex >= EnemiesToSpawn.Num())
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
		
		bAllEnemiesSpawned = true;

		CheckWaveCompletion();
	}
}

void AWaveManager::OnEnemyDestroyed(AActor* DestroyedActor)
{
	ActiveEnemies--;

	CheckWaveCompletion();
}

void AWaveManager::CheckWaveCompletion()
{
	if (bAllEnemiesSpawned && ActiveEnemies <= 0)
	{
		OnWaveCompleted();
	}
}

void AWaveManager::OnWaveCompleted()
{
	if (ATowerDefenceGameMode* GameMode = Cast<ATowerDefenceGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->OnEndOfWave();
	}
}
