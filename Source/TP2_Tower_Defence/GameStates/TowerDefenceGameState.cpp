#include "TowerDefenceGameState.h"

void ATowerDefenceGameState::SetGamePhase(EGamePhase NewPhase)
{
	CurrentPhase = NewPhase;
	
	OnPhaseChanged.Broadcast(NewPhase);
}
