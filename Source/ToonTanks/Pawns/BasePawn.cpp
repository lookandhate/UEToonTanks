// Fill out your copyright notice in the Description page of Project Settings.
#include "ToonTanks/Pawns/BasePawn.h"
#include "ToonTanks/Actors/ProjectileBase.h"

#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystem.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	
	RootComponent = m_Capsule;

	m_BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base mesh"));
	m_BaseMesh->SetupAttachment(RootComponent);

	m_TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret mesh"));
	m_TurretMesh->SetupAttachment(m_BaseMesh);

	m_ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile spawn point"));
	m_ProjectileSpawnPoint->SetupAttachment(m_TurretMesh);
}

void ABasePawn::Fire()
{
	if(!ProjectileClass)
	{
		UE_LOG(LogTemp, Error, TEXT("No projectile class was found"))
		return;
	}
	FVector SpawnLocation = m_ProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotator = m_ProjectileSpawnPoint->GetComponentRotation();
	
	AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, Rotator);
	TempProjectile->SetOwner(this);
	
}


void ABasePawn::RotateTurret(FVector TargetToLookAt)
{
	FVector CleanedTargetLookAt = FVector(TargetToLookAt.X, TargetToLookAt.Y, m_TurretMesh->GetComponentLocation().Z);
	FVector StartLocation = m_TurretMesh->GetComponentLocation();

	FRotator TurretRotation = FVector(CleanedTargetLookAt - StartLocation).Rotation();
	m_TurretMesh->SetWorldRotation(TurretRotation);
}

void ABasePawn::HandleDestruction()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_DeathParticle, GetActorLocation());
}


