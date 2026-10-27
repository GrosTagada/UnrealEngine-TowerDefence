// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TowerDefenseCameraPawn.generated.h"

UCLASS()
class TP2_TOWER_DEFENCE_API ATowerDefenseCameraPawn : public APawn
{
	GENERATED_BODY()
public:
	// Sets default values for this pawn's properties
	ATowerDefenseCameraPawn();

protected:
	
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> Camera;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
