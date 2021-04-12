// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

DECLARE_LOG_CATEGORY_CLASS(LogProjectile, Log, All);

class UProjectileMovementComponent;
class UParticleSystem;
class UParticleSystemComponent;

UCLASS()
class TOONTANKS_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", DisplayName ="Movement component", meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* m_ProjectileMovement;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", DisplayName ="Projectile mesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* m_ProjectileMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", DisplayName ="Projectile TrailParticle", meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* m_ProjectileTrailParticle;
	UPROPERTY(EditDefaultsOnly, Category = "Damage", DisplayName ="Damage Type")
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement", DisplayName ="Projectile Movement speed", meta = (AllowPrivateAccess = "true"))
	float m_fMovementSpeed = 13000.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Damage", DisplayName ="Projectile damage", meta = (AllowPrivateAccess = "true"))
	float m_fDamage = 50.f;

	UPROPERTY(EditAnywhere, Category="VisualEffects")
	UParticleSystem* m_ProjectileHitParticle;
	

private:
	void ProjectileSpawnDebug();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
