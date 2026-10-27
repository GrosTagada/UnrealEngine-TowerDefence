// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TowerDefensePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TP2_TOWER_DEFENCE_API ATowerDefensePlayerController : public APlayerController
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Inputs")
	TObjectPtr<UInputMappingContext> InputMappingContext;
	UPROPERTY(EditAnywhere, Category = "Inputs")
	TObjectPtr<UInputAction> ClickAction;
	
	UPROPERTY(EditAnywhere, Category = "RayTrace")
	TEnumAsByte<ETraceTypeQuery>GroundChannel;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;
	
	void OnLeftClick();
	
};
