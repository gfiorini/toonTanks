// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

#include "Kismet/GameplayStatics.h"


void ATurret::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (PlayerPawn) {
		FVector Target = PlayerPawn->GetTransform().GetLocation();
		if (GetDistanceTo(Target) <= Distance) {
			Super::RotateTurret(Target);
		}
	}
}

float ATurret::GetDistanceTo(FVector Target) {
	const float DistanceTo = FVector::Distance(GetTransform().GetLocation(), Target);
	return DistanceTo;
}

void ATurret::BeginPlay() {
	Super::BeginPlay();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
}
