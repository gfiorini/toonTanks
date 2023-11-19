// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTankGameMode.generated.h"


/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTankGameMode : public AGameModeBase {
	GENERATED_BODY()

private:
	UPROPERTY()
	class ATank* Tank;

	UPROPERTY()
	class AToonTankPlayerController* TankController;

public:
	void ActorDied(AActor* actor);
	virtual void BeginPlay() override;
};
