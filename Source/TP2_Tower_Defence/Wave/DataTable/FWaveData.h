#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FWaveEnemyEntry.h"
#include "FWaveData.generated.h"

USTRUCT(BlueprintType)
struct FWaveData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FWaveEnemyEntry> Enemies;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpawnInterval = 1.5f;
};