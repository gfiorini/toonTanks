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

public:
	void ActorDied(AActor* Actor);
	virtual void BeginPlay() override;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWon);

	UPROPERTY(BlueprintReadWrite)
	float Countdown = 4.f;

	UFUNCTION(BlueprintCallable)
	void PlayTickSound();

private:
	UPROPERTY()
	class ATank* Tank;

	UPROPERTY()
	class AToonTankPlayerController* TankController;

	UPROPERTY(EditAnywhere)
	USoundBase* TickSound;

	int NumTurrets = 0;

	int GetNumTurrets();

	virtual void HandleGameStart();
};
