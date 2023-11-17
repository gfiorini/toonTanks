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
	PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

	BaseMeshComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame 
void AProjectile::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                        FVector NormalImpulse, const FHitResult& Hit) {
	AActor* ProjectileOwner = GetOwner();
	if (ProjectileOwner) {
		AController* InstigatorController = ProjectileOwner->GetInstigatorController();
		if (OtherActor && OtherActor != this && OtherActor != ProjectileOwner) {
			// quale attore ho colpito
			UE_LOG(LogTemp, Log, TEXT("OtherActor %s"), *OtherActor->GetName());
			UHealthComponent* HealthComponent = OtherActor->GetComponentByClass<UHealthComponent>();
			if (HealthComponent) {
				UE_LOG(LogTemp, Warning, TEXT("HealthComponent TROVATO!"));
			}
			const TSubclassOf<UDamageType> ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
			UGameplayStatics::ApplyDamage(OtherActor, Damage, InstigatorController, ProjectileOwner,
			                              ValidDamageTypeClass);
		}
	}


	// TODO explode
	GetWorld()->DestroyActor(this);
}
