// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "TP2_Tower_Defence/GameModes/TowerDefenceGameMode.h"
#include "TP2_Tower_Defence/Ressources/ResourceManagerComponent.h"


// Sets default values
AEnemy::AEnemy()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	HealthComponent->OnDeath.AddDynamic(this,&AEnemy::HandleDeath);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!IsValid(GridComponent) || PathCoordinates.IsEmpty())
		return;

	// Vérifier si l'ennemi a atteint la fin du chemin
	if (CurrentPathIndex >= PathCoordinates.Num())
	{
		Destroy();
		return;
	}

	// Récupérer la position de la prochaine case
	const FVector TargetPosition = GridComponent->GridToWorld(PathCoordinates[CurrentPathIndex]);

	// Récupérer la position actuelle de l'ennemi
	const FVector CurrentPosition = GetActorLocation();

	// Déplacer progressivement l'ennemi vers la destination
	const FVector NewPosition = FMath::VInterpConstantTo(CurrentPosition,TargetPosition,DeltaTime,MovementSpeed);

	SetActorLocation(NewPosition);

	// Vérifier si l'ennemi est arrivé à destination
	if (FVector::DistSquared(NewPosition, TargetPosition) <= FMath::Square(ArrivalDistance))
	{
		// Corriger la position pour atteindre exactement le centre de la case
		SetActorLocation(TargetPosition);

		// Passer à la case suivante
		++CurrentPathIndex;
	}
}


void AEnemy::InitializeEnemy(const TArray<FIntPoint>& InPathCoordinates, UGridComponent* InGridComponent,UEnemyDataAsset* DataAsset)
{
	PathCoordinates = InPathCoordinates;
	
	GridComponent = InGridComponent;
	
	EnemyData = DataAsset;
	
	if (DataAsset->EnemyStaticMesh)
		Mesh->SetStaticMesh(DataAsset->EnemyStaticMesh.LoadSynchronous());
	
	if (DataAsset->Life)
		HealthComponent->InitializeHealth(DataAsset->Life);
}

void AEnemy::GiveReward()
{
	ATowerDefenceGameMode* GameMode = GetWorld()->GetAuthGameMode<ATowerDefenceGameMode>();

	if (!IsValid(GameMode))
		return;

	UResourceManagerComponent* ResourceManager =GameMode->GetResourceManager();

	if (!IsValid(ResourceManager))
		return;

	if (!IsValid(EnemyData))
		return;

	ResourceManager->AddResources(EnemyData->Reward);
}

void AEnemy::HandleDeath()
{
	if (bRewardGiven)
	{
		return;
	}

	bRewardGiven = true;

	GiveReward();
	
}
