#include "BasePawn.h"

#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

// Sets default values
ABasePawn::ABasePawn() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh Component"));
	TurretComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh Component"));
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point Component"));
	DeathParticleSystem = CreateDefaultSubobject<UParticleSystem>(TEXT("Death Particle System"));

	RootComponent = CapsuleComponent;
	BaseMeshComponent->SetupAttachment(RootComponent);
	TurretComponent->SetupAttachment(BaseMeshComponent);
	ProjectileSpawnPoint->SetupAttachment(TurretComponent);
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay() {
	Super::BeginPlay();
}

void ABasePawn::RotateTurret(FVector TargetVector) {
	FVector LookAt = (TargetVector - TurretComponent->GetComponentTransform().GetLocation());
	float InterpolationSpeed = 20;

	FRotator Rotation = LookAt.Rotation();
	//conta solo lo 'Yaw' (rotazione lungo asse z)
	Rotation.Roll = 0;
	Rotation.Pitch = 0;
	FRotator InterpolatedRotation = FMath::RInterpTo(TurretComponent->GetComponentTransform().Rotator(),
	                                                 Rotation,
	                                                 GetWorld()->GetDeltaSeconds(), InterpolationSpeed);
	TurretComponent->SetWorldRotation(InterpolatedRotation);
}

// Called every frame
void ABasePawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void ABasePawn::Fire() {
	// DrawDebugSphere(GetWorld(),
	//                 ProjectileSpawnPoint->GetComponentTransform().GetLocation(),
	//                 10, 32, FColor::Emerald,
	//                 false, 1);

	const auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
	                                                            ProjectileSpawnPoint->GetComponentLocation(),
	                                                            ProjectileSpawnPoint->GetComponentRotation());
	Projectile->SetOwner(this);
	Projectile->IgnoreActor(this);
}

void ABasePawn::HandleDestruction() {
	if (DeathParticleSystem) {
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticleSystem, GetActorLocation(), GetActorRotation());
	}
	if (DeathSound) {
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}
}
