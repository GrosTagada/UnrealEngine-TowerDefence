// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"


// Sets default values
AEnemy::AEnemy()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
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

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemy::InitializeEnemy(const TArray<FIntPoint>& InPathCoordinates, UGridComponent* InGridComponent)
{
	PathCoordinates = InPathCoordinates;
	
	GridComponent = InGridComponent;
}

