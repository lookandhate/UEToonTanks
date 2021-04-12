// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "PawnTank.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

APawnTurret::APawnTurret()
{
	
}


// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(m_FireRateTimerHandle,this, &APawnTurret::CheckFireCondition, m_fFireRate, true);
	
	m_PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
}

void APawnTurret::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

float APawnTurret::DistanceToPlayer() const
{
	if(!m_PlayerPawn)
	{
		return -1.f;
	}

	// Could Use GetDistanceTo(m_PlayerPawn);
	return FVector::Dist(m_PlayerPawn->GetActorLocation(), GetActorLocation());	
}

void APawnTurret::CheckFireCondition()
{
	// Fire only if player is valid
	if(!m_PlayerPawn)
	{
		UE_LOG(LogTurret, Error, TEXT("PlayerPawn was not found"));
		return;
	}

	// Check if player is Alive
	if(!m_PlayerPawn->IsAlive())
	{
		UE_LOG(LogTurret, Display, TEXT("Player pawn is not alive"));
		return;
	}
	
	// Check if player in fire range
	if(DistanceToPlayer()  > m_fFireDistance)
	{
		if(m_TankLocationDebug)
			UE_LOG(LogTurret, Display, TEXT("Distance to Player more than Max fire Distance (%f > %f)"), DistanceToPlayer(), m_fFireDistance);
		return;
	}
	if(m_TankLocationDebug)
		UE_LOG(LogTurret, Display, TEXT("All fire checks Passed, CAN FIRE Distance is %f"), DistanceToPlayer());
	Fire();
}


void APawnTurret::DrawLineToTank() const
{
	FColor color = DistanceToPlayer() <= m_fFireDistance ? FColor::Green : FColor::Red;
	DrawDebugLine(GetWorld(), GetActorLocation(), m_PlayerPawn->GetActorLocation(), color, false, 5, ECC_WorldDynamic, 5);
}

void APawnTurret::PrintDebugInfoAboutDistance() const
{
	int32 id = GetUniqueID();
	GEngine->AddOnScreenDebugMessage(id, 1, FColor::Blue,
    FString::Printf(TEXT("Distance From %s to tank is %f"), *GetName(),DistanceToPlayer()));
}


void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!m_PlayerPawn)
		return;
	
	if(m_TankLocationDebug)
	{
		PrintDebugInfoAboutDistance();
		DrawLineToTank();
	}
	// Rotating turret to look at player
	RotateTurret(m_PlayerPawn->GetActorLocation());
}
