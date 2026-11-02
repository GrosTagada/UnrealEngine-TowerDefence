// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "TP2_Tower_Defence/Components/HealthComponent.h"

#include "CoreMinimal.h"
#include "DataAssets/EnemyDataAsset.h"
#include "GameFramework/Pawn.h"
#include "TP2_Tower_Defence/Path/PathManager.h"
#include "Enemy.generated.h"

UCLASS()
class TP2_TOWER_DEFENCE_API AEnemy : public APawn
{
	GENERATED_BODY()
	
	UPROPERTY()
	TArray<FIntPoint> PathCoordinates;
	
	int32 CurrentPathIndex = 1;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementSpeed = 300.0f;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float ArrivalDistance = 5.0f;
	
	UGridComponent* GridComponent;
	
public:
	// Sets default values for this pawn's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UHealthComponent> HealthComponent;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void InitializeEnemy(const TArray<FIntPoint>& InPathCoordinates, UGridComponent* InGridComponent, UEnemyDataAsset* DataAsset);
	
	UHealthComponent* GetHealthComponent() const {return HealthComponent;}
};
