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
		GameOver(false);
	} else {
		if (ATurret* Turret = Cast<ATurret>(Actor)) {
			NumTurrets--;
			Turret->HandleDestruction();
			if (NumTurrets == 0) {
				GameOver(true);
			}
		}
	}
}

void AToonTankGameMode::BeginPlay() {
	Super::BeginPlay();
	AToonTankGameMode::HandleGameStart();
	NumTurrets = GetNumTurrets();
	StartGame();
}

int AToonTankGameMode::GetNumTurrets() {
	TArray<AActor*> Turrets;
	UGameplayStatics::GetAllActorsOfClass(this, ATurret::StaticClass(), Turrets);
	return Turrets.Num();
}

void AToonTankGameMode::HandleGameStart() {
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	TankController = Cast<AToonTankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (TankController) {
		TankController->SetPlayerEnabledState(false);
		const FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(TankController,
		                                                                   &AToonTankPlayerController::SetPlayerEnabledState,
		                                                                   true);
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, Countdown, false);
	}
}
