// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "GameFramework/Actor.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::ApplyDamage(float Damage)
{
	if (Damage <= 0.0f || CurrentHealth <= 0.0f)
	{
		return;
	}

	CurrentHealth = FMath::Max(0.0f, CurrentHealth - Damage);

	if (CurrentHealth <= 0.0f)
	{
		OnDeath.Broadcast();

		if (AActor* Owner = GetOwner())
		{
			Owner->Destroy();
		}
	}
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentHealth = MaxHealth;
}
