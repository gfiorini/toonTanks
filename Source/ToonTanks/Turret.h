// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATurret : public ABasePawn {
	GENERATED_BODY()

public:
	void MoveTowerIfNeeded();
	
	bool InFireRange();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category="Combat")
	float Distance = 0.;
	UPROPERTY()
	APawn* PlayerPawn;

	FTimerHandle TimerHandle;

	float FireRate = 2.;

	void FireIfYouCan();

	float GetDistanceTo(FVector target);
};
