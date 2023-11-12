// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"

ATank::ATank() {
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArmComponent->SetupAttachment(RootComponent); //non va MeshComponent ?

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ATank::MoveForward);
	PlayerInputComponent->BindAxis("Turn", this, &ATank::Turn);
}

void ATank::MoveForward(float Value) {
	FVector DeltaLocation = FVector();
	UWorld* world = GetWorld();
	float DeltaTime = world->GetDeltaSeconds();
	DeltaLocation.X = Value * MovementSpeed * DeltaTime;
	AddActorLocalOffset(DeltaLocation);
}

void ATank::Turn(float Value) {
	FRotator Rotation = FRotator();
	UWorld* world = GetWorld();
	float DeltaTime = world->GetDeltaSeconds();
	Rotation.Yaw = Value * RotationSpeed * DeltaTime;
	AddActorLocalRotation(Rotation);
}
