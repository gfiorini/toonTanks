// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "ToonTankGameMode.h"
#include "Kismet/GameplayStatics.h"


UHealthComponent::UHealthComponent() {
	PrimaryComponentTick.bCanEverTick = true;
	Health = MaxHealth;
}

// Called when the game starts
void UHealthComponent::BeginPlay() {
	Super::BeginPlay();
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	ToonTankGameMode = Cast<AToonTankGameMode>(UGameplayStatics::GetGameMode(this));
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                   AController* Controller, AActor* SourceActor) {
	if (Damage <= 0.f) {
		return;
	}
	Health -= Damage;
	if (Health <= 0) {
		UE_LOG(LogTemp, Log, TEXT("Health < 0 %s"), *DamagedActor->GetName());
		ToonTankGameMode->ActorDied(DamagedActor);
	}
}
