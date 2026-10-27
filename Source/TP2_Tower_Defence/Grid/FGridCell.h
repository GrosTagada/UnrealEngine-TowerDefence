#pragma once

#include "CoreMinimal.h"
#include "FGridCell.generated.h"

USTRUCT(BlueprintType)
struct FGridCell
{
	GENERATED_BODY()
	
public:

	// Coordonnees de la case dans la grille
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid")
	FIntPoint Coordinates = FIntPoint::ZeroValue;

	// Indique si la case est occupee
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid")
	bool bIsOccupied = false;

	FGridCell()
	{
	}

	FGridCell(int32 X, int32 Y): Coordinates(X, Y)
	{
	}
};
