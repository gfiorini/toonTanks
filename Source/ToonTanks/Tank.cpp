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

void ATank::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ATank::MoveForward);
	PlayerInputComponent->BindAxis("Turn", this, &ATank::Turn);
	PlayerInputComponent->BindAxis("RotateTurret", this, &ATank::RotateTurret);
}

void ATank::BeginPlay() {
	Super::BeginPlay();
	PlayerController = Cast<APlayerController>(GetController());
}

void ATank::MoveForward(float Value) {
	if (Value != 0) {
		FVector DeltaLocation = FVector();
		const UWorld* World = GetWorld();
		const float DeltaTime = World->GetDeltaSeconds();
		DeltaLocation.X = Value * MovementSpeed * DeltaTime;
		AddActorLocalOffset(DeltaLocation, true);
	}
}

void ATank::Turn(float Value) {
	if (Value != 0) {
		FRotator Rotation = FRotator();
		const UWorld* World = GetWorld();
		const float DeltaTime = World->GetDeltaSeconds();
		Rotation.Yaw = Value * RotationSpeed * DeltaTime;
		AddActorLocalRotation(Rotation);
	}
}

void ATank::RotateTurret(float Value) {
	if (Value != 0 && PlayerController) {
		FHitResult HitResult;
		bool bHit = PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
		if (bHit) {
			FVector ImpactPoint = HitResult.ImpactPoint;
			FTransform TurretTransform = TurretComponent->GetComponentTransform();
			DrawDebugSphere(GetWorld(), ImpactPoint, 25, 10, FColor::Red, false, -1);
			FVector TargetVector = FVector(ImpactPoint.X, ImpactPoint.Y, TurretTransform.GetLocation().Z);
			FVector LookAt = (TargetVector - TurretTransform.GetLocation());
			float InterpolationSpeed = 20;
			FRotator InterpolatedRotation = FMath::RInterpTo(TurretTransform.Rotator(), LookAt.Rotation(),
			                                                 GetWorld()->GetDeltaSeconds(), InterpolationSpeed);
			TurretComponent->SetWorldRotation(InterpolatedRotation);
		}
	}
}
