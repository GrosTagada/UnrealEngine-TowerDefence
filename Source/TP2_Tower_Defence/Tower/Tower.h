// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/TowerDataAsset.h"
#include "GameFramework/Actor.h"
#include "TP2_Tower_Defence/Enemies/Enemy.h"
#include "Tower.generated.h"

UCLASS()
class TP2_TOWER_DEFENCE_API ATower : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleInstanceOnly, Category = "Tower")
	float AttackRange = 500.0f;

	UPROPERTY(VisibleInstanceOnly, Category = "Tower")
	float AttackDamage = 10.0f;

	UPROPERTY(VisibleInstanceOnly, Category = "Tower")
	float AttackInterval = 1.0f;

	UPROPERTY()
	TObjectPtr<AEnemy> CurrentTarget;
	
	UPROPERTY(EditAnywhere, Category = "Tower")
	TObjectPtr<UTowerDataAsset> TowerData;
	
	FTimerHandle AttackTimerHandle;
	
public:	
	// Sets default values for this actor's properties
	ATower();
	void InitializeTower(UTowerDataAsset* InTowerData);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	void FindTarget();
	bool CanAttack() const;
	void Attack();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
