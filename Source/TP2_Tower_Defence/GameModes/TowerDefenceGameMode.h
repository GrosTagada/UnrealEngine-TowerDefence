// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TP2_Tower_Defence/GameStates/TowerDefenceGameState.h"
#include "TP2_Tower_Defence/Ressources/ResourceManagerComponent.h"
#include "TP2_Tower_Defence/Wave/WaveManager.h"
#include "TowerDefenceGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TP2_TOWER_DEFENCE_API ATowerDefenceGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	ATowerDefenceGameState* TowerDefenceGameState;
	
	UPROPERTY(VisibleAnywhere, Category="Waves")
	AWaveManager* WaveManager; // could be a component
	
	UPROPERTY(VisibleAnywhere, Category="Resources")
	TObjectPtr<UResourceManagerComponent> ResourceManager;
	
protected:
	ATowerDefenceGameMode();
	virtual void BeginPlay() override;
	
public:
	void OnPathCompleted() const;
	void OnEndOfPreparation() const;
	void OnEndOfWave() const;
	void OnEndOfGame() const;
	
	UFUNCTION(BlueprintCallable)
	void StartWave() const;
	
	UFUNCTION(BlueprintCallable)
	UResourceManagerComponent* GetResourceManager() const{return ResourceManager;}
};
