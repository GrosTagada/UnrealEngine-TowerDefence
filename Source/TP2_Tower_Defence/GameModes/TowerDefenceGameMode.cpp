// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerDefenceGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "TP2_Tower_Defence/GameStates/TowerDefenceGameState.h"

void ATowerDefenceGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	TowerDefenceGameState = GetGameState<ATowerDefenceGameState>();
	
	if (!IsValid(TowerDefenceGameState))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to get GameState"));
		return;
	}
	
	WaveManager = Cast<AWaveManager>(UGameplayStatics::GetActorOfClass(GetWorld(),AWaveManager::StaticClass()));

	if (!IsValid(WaveManager))
	{
		UE_LOG(LogTemp, Error, TEXT("Wave Manager not found in the level"));
		return;
	}
}

void ATowerDefenceGameMode::OnPathCompleted() const
{
	if (!TowerDefenceGameState)
		return;
	
	TowerDefenceGameState->SetGamePhase(EGamePhase::Preparation);
	
	StartWave();
}

void ATowerDefenceGameMode::OnEndOfPreparation() const
{
	if (!TowerDefenceGameState)
		return;
	
	TowerDefenceGameState->SetGamePhase(EGamePhase::WaveInProgress);
}

void ATowerDefenceGameMode::OnEndOfWave() const
{
	if (!TowerDefenceGameState)
		return;
	
	TowerDefenceGameState->SetGamePhase(EGamePhase::Preparation);
}

void ATowerDefenceGameMode::OnEndOfGame() const
{
	if (!TowerDefenceGameState)
		return;
	
	//TowerDefenceGameState->SetGamePhase()
}

void ATowerDefenceGameMode::StartWave() const
{
	if (TowerDefenceGameState->GetGamePhase() != EGamePhase::Preparation)
	{
		return;
	}

	if (!IsValid(WaveManager))
	{
		return;
	}
	
	TowerDefenceGameState->SetGamePhase(EGamePhase::WaveInProgress);
	
	WaveManager->StartWave();
}
