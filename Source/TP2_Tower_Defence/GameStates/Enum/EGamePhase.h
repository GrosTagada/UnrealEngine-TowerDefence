#pragma once

UENUM(BlueprintType)
enum class EGamePhase : uint8
{
	PathSelection,
	Preparation,
	WaveInProgress
};
