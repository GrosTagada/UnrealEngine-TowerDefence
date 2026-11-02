#include "ResourceManagerComponent.h"

UResourceManagerComponent::UResourceManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UResourceManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentResources = StartingResources;

	OnResourcesChanged.Broadcast(CurrentResources);
}

bool UResourceManagerComponent::CanAfford(int32 Amount) const
{
	return Amount > 0 && CurrentResources >= Amount;
}

bool UResourceManagerComponent::TrySpendResources(int32 Amount)
{
	if (!CanAfford(Amount))
	{
		return false;
	}

	CurrentResources -= Amount;

	OnResourcesChanged.Broadcast(CurrentResources);

	return true;
}

void UResourceManagerComponent::AddResources(int32 Amount)
{
	if (Amount <= 0)
	{
		return;
	}

	CurrentResources += Amount;

	OnResourcesChanged.Broadcast(CurrentResources);
}

int32 UResourceManagerComponent::GetCurrentResources() const
{
	return CurrentResources;
}
