// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnemyDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class TP2_TOWER_DEFENCE_API UEnemyDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	FString AssetName;
	
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UStaticMesh> EnemyStaticMesh;
};
