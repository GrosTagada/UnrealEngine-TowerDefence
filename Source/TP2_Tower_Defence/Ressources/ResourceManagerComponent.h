// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ResourceManagerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnResourcesChanged,int32,NewAmount);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TP2_TOWER_DEFENCE_API UResourceManagerComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UResourceManagerComponent();

protected:
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Resources")
	int32 StartingResources = 500;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Resources")
	int32 CurrentResources = 0;

	UPROPERTY(BlueprintAssignable, Category="Resources")
	FOnResourcesChanged OnResourcesChanged;

	UFUNCTION(BlueprintCallable, Category="Resources")
	bool CanAfford(int32 Amount) const;

	UFUNCTION(BlueprintCallable, Category="Resources")
	bool TrySpendResources(int32 Amount);

	UFUNCTION(BlueprintCallable, Category="Resources")
	void AddResources(int32 Amount);

	UFUNCTION(BlueprintPure, Category="Resources")
	int32 GetCurrentResources() const;
};
