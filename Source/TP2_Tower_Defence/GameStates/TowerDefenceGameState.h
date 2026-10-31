// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enum/EGamePhase.h"

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TowerDefenceGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPhaseChanged,EGamePhase,NewPhase);

UCLASS()
class TP2_TOWER_DEFENCE_API ATowerDefenceGameState : public AGameStateBase
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, Category = "Game")
	EGamePhase CurrentPhase = EGamePhase::PathSelection;
	
	
public:
	EGamePhase GetGamePhase() const {return CurrentPhase;};
	void SetGamePhase(EGamePhase NewPhase);
	
	FOnPhaseChanged OnPhaseChanged;
};
