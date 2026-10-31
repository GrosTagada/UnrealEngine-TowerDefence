// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TP2_Tower_Defence/Enemies/Enemy.h"
#include "TP2_Tower_Defence/Path/PathManager.h"
#include "WaveManager.generated.h"

UCLASS()
class TP2_TOWER_DEFENCE_API AWaveManager : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditInstanceOnly, Category="Path")
	TObjectPtr<APathManager> PathManager;
	
	UPROPERTY(EditDefaultsOnly, Category = "Enemies")
	TSubclassOf<AEnemy> EnemyClass;
	
	
public:	
	// Sets default values for this actor's properties
	AWaveManager();
	
	void InitializeWaveManager(UGridComponent* InGridComponent, TObjectPtr<APathManager> InPathManager);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void SpawnEnemy();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void StartWave();

};
