// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = m_ProjectileMesh;

	m_ProjectileTrailParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ProjectileTrail"));
	m_ProjectileTrailParticle->SetupAttachment(RootComponent);

	m_ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement component"));

	m_ProjectileMovement->InitialSpeed = m_fMovementSpeed;
	m_ProjectileMovement->MaxSpeed = m_fMovementSpeed;

	InitialLifeSpan = 5.f;
	
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	m_ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	
}

void AProjectileBase::ProjectileSpawnDebug()
{
	if(!GEngine)
		return;
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red,
		FString::Printf(TEXT("Projectile %s spawned with speed %f"),
			*GetName(), m_ProjectileMovement->InitialSpeed)
		);	
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* OwnerOfTheComponent = GetOwner();
	auto InstigatorController = OwnerOfTheComponent->GetInstigatorController();
	
	// Check if Owner and other Actor are valid
	if(!OwnerOfTheComponent)
		return;
	// Check if other actor is owner
	if(!OtherActor || OtherActor == this || OtherActor == OwnerOfTheComponent)
		return;

	UE_LOG(LogProjectile, Display, TEXT("Applying damage to %s. Damage is: %f. Destroying projectile"), *OtherActor->GetName(), m_fDamage);


	UGameplayStatics::ApplyDamage(OtherActor, m_fDamage, InstigatorController, this, DamageType);
	UGameplayStatics::SpawnEmitterAtLocation(this, m_ProjectileHitParticle, GetActorLocation());
	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCamShake);
	
	Destroy();
}
