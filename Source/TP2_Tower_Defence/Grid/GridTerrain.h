// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridComponent.h"
#include "GameFramework/Actor.h"
#include "GridTerrain.generated.h"

UCLASS()
class TP2_TOWER_DEFENCE_API AGridTerrain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridTerrain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Nombre de cases sur l'axe X
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid")
	int32 GridSizeX = 16;

	// Nombre de cases sur l'axe Y
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid")
	int32 GridSizeY = 16;

	// Taille d'une case en unites Unreal
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid")
	float CellSize = 100.0f;

	// Composant responsable de la grille
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Grid")
	TObjectPtr<UGridComponent> GridComponent;

	// Acces au composant
	UGridComponent* GetGridComponent() const
	{
		return GridComponent;
	}
};
