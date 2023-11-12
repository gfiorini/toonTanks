// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"


/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn {
	GENERATED_BODY()

public:
	ATank();

protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere, Category="Movement")
	float MovementSpeed;

	UPROPERTY(EditAnywhere, Category="Movement")
	float RotationSpeed;

	UPROPERTY(EditAnywhere, Category="Movement")
	float TurretRotationSpeed;

	UPROPERTY(EditDefaultsOnly)
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditDefaultsOnly)
	class UCameraComponent* CameraComponent;

	void MoveForward(float Value);

	void Turn(float Value);
};
