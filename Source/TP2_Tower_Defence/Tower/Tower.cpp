// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

#include "Kismet/GameplayStatics.h"

ATower::ATower()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

void ATower::InitializeTower(UTowerDataAsset* InTowerData)
{
	if (!IsValid(InTowerData))
	{
		return;
	}

	TowerData = InTowerData;
	
	if (TowerData->TowerMesh)
		Mesh->SetStaticMesh(TowerData->TowerMesh.LoadSynchronous());
	
	if (TowerData->AttackDamage)
		AttackDamage = TowerData->AttackDamage;
	
	if (TowerData->AttackInterval)
		AttackInterval = TowerData->AttackInterval;
	
	if (TowerData->AttackRange)
		AttackRange = TowerData->AttackRange;
	
}

void ATower::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle,this,&ATower::Attack,FMath::Max(AttackInterval, 0.1f),true,0.0f);
}


void ATower::FindTarget()
{
	TArray<AActor*> FoundEnemies;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AEnemy::StaticClass(),FoundEnemies);

	CurrentTarget = nullptr;

	float ClosestDistance = AttackRange * AttackRange;

	for (AActor* Actor : FoundEnemies)
	{
		AEnemy* Enemy = Cast<AEnemy>(Actor);

		if (!IsValid(Enemy))
		{
			continue;
		}

		float DistanceSquared = FVector::DistSquared(GetActorLocation(),Enemy->GetActorLocation());

		if (DistanceSquared < ClosestDistance)
		{
			ClosestDistance = DistanceSquared;
			CurrentTarget = Enemy;
			
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Cyan,TEXT("Target found"));
		}
	}
}

bool ATower::CanAttack() const
{
	if (!IsValid(CurrentTarget))
	{
		return false;
	}

	float DistanceSquared = FVector::DistSquared(GetActorLocation(),CurrentTarget->GetActorLocation());

	return DistanceSquared <= FMath::Square(AttackRange);
}

void ATower::Attack()
{
	FindTarget();

	if (!CanAttack())
	{
		return;
	}

	UHealthComponent* HealthComponent = CurrentTarget->GetHealthComponent();

	if (!IsValid(HealthComponent))
	{
		return;
	}

	HealthComponent->ApplyDamage(AttackDamage);
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
