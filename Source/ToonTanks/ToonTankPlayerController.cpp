// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankPlayerController.h"

void AToonTankPlayerController::SetPlayerEnabledState(bool bEnabled) {
	if (bEnabled) {
		GetPawn()->EnableInput(this);
	} else {
		GetPawn()->DisableInput(this);
	}
	bShowMouseCursor = bEnabled;
}
