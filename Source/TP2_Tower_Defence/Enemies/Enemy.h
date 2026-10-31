// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void InitializeEnemy(const TArray<FIntPoint>& InPathCoordinates, UGridComponent* InGridComponent);
};
