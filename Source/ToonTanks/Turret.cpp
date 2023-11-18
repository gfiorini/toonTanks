// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

#include "Kismet/GameplayStatics.h"


bool ATurret::InFireRange() {
	if (PlayerPawn) {
		FVector Target = PlayerPawn->GetActorLocation();
		return GetDistanceTo(Target) <= Distance;
	}
	return false;
}

void ATurret::MoveTowerIfNeeded() {
	if (InFireRange()) {
		Super::RotateTurret(PlayerPawn->GetActorLocation());
	}
}

void ATurret::FireIfYouCan() {
	if (InFireRange()) {
		Super::Fire();
	}
}

void ATurret::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	MoveTowerIfNeeded();
}


float ATurret::GetDistanceTo(FVector Target) {
	const float DistanceTo = FVector::Distance(GetTransform().GetLocation(), Target);
	return DistanceTo;
}

void ATurret::BeginPlay() {
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATurret::FireIfYouCan, FireRate, true);
	PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
}

void ATurret::HandleDestruction() {
	Super::HandleDestruction();
	Destroy();
}
