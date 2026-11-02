// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TP2_Tower_Defence/Enemies/Enemy.h"
#include "EnemyDataAsset.generated.h"

/**
 * 
 */

class AEnemy;

UCLASS()
class TP2_TOWER_DEFENCE_API UEnemyDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	FString AssetName;
	
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UStaticMesh> EnemyStaticMesh;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AEnemy> EnemyClass;
	
	UPROPERTY(EditAnywhere)
	float Reward = 10.0f;
	
	UPROPERTY(EditAnywhere)
	float Life = 100.0f;
};
