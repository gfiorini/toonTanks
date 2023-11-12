// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"

ATank::ATank() {
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArmComponent->SetupAttachment(RootComponent); //non va MeshComponent ?

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ATank::MoveForward);
	PlayerInputComponent->BindAxis("Turn", this, &ATank::Turn);
	PlayerInputComponent->BindAxis("RotateTurret", this, &ATank::RotateTurret);
}

void ATank::MoveForward(float Value) {
	FVector DeltaLocation = FVector();
	const UWorld* World = GetWorld();
	const float DeltaTime = World->GetDeltaSeconds();
	DeltaLocation.X = Value * MovementSpeed * DeltaTime;
	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value) {
	FRotator Rotation = FRotator();
	const UWorld* World = GetWorld();
	const float DeltaTime = World->GetDeltaSeconds();
	Rotation.Yaw = Value * RotationSpeed * DeltaTime;
	AddActorLocalRotation(Rotation);
}

void ATank::RotateTurret(float Value) {
	FRotator TurretRotation = FRotator();
	const UWorld* World = GetWorld();
	const float DeltaTime = World->GetDeltaSeconds();
	TurretRotation.Yaw = Value * TurretRotationSpeed * DeltaTime;
	TurretComponent->AddLocalRotation(TurretRotation);
}
