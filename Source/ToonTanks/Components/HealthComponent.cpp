// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "ToonTanks/Gamemodes/TanksBaseGamemode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	m_fHealth = m_fDefaultHealth;
	GameModeRef = Cast<ATanksBaseGamemode>(UGameplayStatics::GetGameMode(GetWorld()));
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

float UHealthComponent::GetCurrentHealth() const
{
	return m_fHealth;
}
float UHealthComponent::GetMaxHealth() const
{
	return m_fDefaultHealth;
}




void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if(Damage == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("%s took 0 damage from %s(Causer=%s)"), GetOwner(), *InstigatedBy->GetName(), *DamageCauser->GetName())
		return;
	}

	UE_LOG(LogTemp, Display, TEXT("%s taking damage %f points from %s(Causer=%s), DamageType is %s"),
							      *GetOwner()->GetName(), Damage,
							      InstigatedBy ? *InstigatedBy->GetName() : TEXT("InstigatedBy=nullptr"),
							      DamageCauser ? *DamageCauser->GetName():  TEXT("DamageCauser=nullptr"),
							      DamageType ? *DamageType->GetName() :  TEXT("DamageType=nullptr")
							      )
	m_fHealth = FMath::Clamp(m_fHealth - Damage, 0.0f, m_fDefaultHealth);

	if(m_fHealth <= 0) // Check if health below zero.
	{
		if(GameModeRef)
		{
			GameModeRef->ActorDied(GetOwner()); // Killing actor
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("No valid GameModeRef in HealthComponent"));
			return;
		}
	}
}

