#pragma once

#include "CoreMinimal.h"
#include "FWaveEnemyEntry.generated.h"

class UEnemyDataAsset;

USTRUCT(BlueprintType)
struct FWaveEnemyEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UEnemyDataAsset> EnemyData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Quantity = 1;
};