// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankGameMode.h"

#include "Tank.h"
#include "ToonTankPlayerController.h"
#include "Turret.h"
#include "Kismet/GameplayStatics.h"


void AToonTankGameMode::ActorDied(AActor* Actor) {
	if (Tank == Actor) {
		Tank->HandleDestruction();
		TankController->SetPlayerEnabledState(false);
	} else {
		if (ATurret* Turret = Cast<ATurret>(Actor)) {
			Turret->HandleDestruction();
		}
	}
}

void AToonTankGameMode::BeginPlay() {
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	TankController = Cast<AToonTankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
}
