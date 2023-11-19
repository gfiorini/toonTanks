// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "HealthComponent.h"
#include "Tank.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AProjectile::AProjectile() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh Component"));
	RootComponent = BaseMeshComponent;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(
		TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->InitialSpeed = 10;
	ProjectileMovementComponent->MaxSpeed = 100;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay() {
	Super::BeginPlay();
	//PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

	BaseMeshComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame 
void AProjectile::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                        FVector NormalImpulse, const FHitResult& Hit) {
	AActor* ProjectileOwner = GetOwner();
	if (ProjectileOwner == nullptr) {
		return;
	}
	if (OtherActor && OtherActor != ProjectileOwner) {
		UGameplayStatics::ApplyDamage(OtherActor, Damage, ProjectileOwner->GetInstigatorController(),
		                              ProjectileOwner,
		                              UDamageType::StaticClass());
		UGameplayStatics::SpawnEmitterAtLocation(this, ParticleSystem,
		                                         GetActorLocation(), GetActorRotation());
		Destroy();
	}
}

void AProjectile::IgnoreActor(ABasePawn* APawn) {
	BaseMeshComponent->IgnoreActorWhenMoving(APawn, true);
}
