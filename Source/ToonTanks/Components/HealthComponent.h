// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ToonTanks/Gamemodes/TanksBaseGamemode.h"

#include "HealthComponent.generated.h"

class ATanksBaseGamemode;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();
	
	UFUNCTION(BlueprintPure)
	float GetCurrentHealth() const;
	UFUNCTION(BlueprintPure)
	float GetMaxHealth() const;

	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

public:

private:
	UPROPERTY(EditAnywhere)
	float m_fDefaultHealth = 300.f;
	float m_fHealth = 0.f;

	
	ATanksBaseGamemode* GameModeRef;
		
};
