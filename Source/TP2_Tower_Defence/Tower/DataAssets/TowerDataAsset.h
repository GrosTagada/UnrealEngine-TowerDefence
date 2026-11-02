#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TowerDataAsset.generated.h"

UCLASS()
class TP2_TOWER_DEFENCE_API UTowerDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	FString TowerName;
	
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UStaticMesh> TowerMesh;
	
	UPROPERTY(EditAnywhere, Category = "Tower")
	float AttackRange = 500.0f;

	UPROPERTY(EditAnywhere, Category = "Tower")
	float AttackDamage = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Tower")
	float AttackInterval = 1.0f;
};
