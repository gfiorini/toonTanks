// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Turret.h"
#include "Tank.generated.h"


/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn {
	GENERATED_BODY()

public:
	ATank();

	virtual void Tick(float DeltaTime) override;
	virtual void HandleDestruction() override;
	APlayerController* GetPlayerController();
	bool IsAlive();

protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category="Movement")
	float MovementSpeed;

	UPROPERTY(EditAnywhere, Category="Movement")
	float RotationSpeed;

	UPROPERTY(EditDefaultsOnly)
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditDefaultsOnly)
	class UCameraComponent* CameraComponent;

	UPROPERTY()
	APlayerController* PlayerController;

	bool bAlive = true;

	void MoveForward(float Value);

	void Turn(float Value);

	void HandleTankTurret(float Value);
	virtual void Fire() override;
};
