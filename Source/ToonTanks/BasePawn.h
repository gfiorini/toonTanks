// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn {
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void RotateTurret(FVector LookAt);

protected:
	UPROPERTY(EditDefaultsOnly)
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BaseMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* TurretComponent;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category="Combat")
	TSubclassOf<UCameraShakeBase> DestroyCameraShake;

private:
	UPROPERTY(EditAnywhere)
	UParticleSystem* DeathParticleSystem;

	UPROPERTY(EditAnywhere, Category="Combat")
	USoundBase* DeathSound;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Fire();
	virtual void HandleDestruction();
};
