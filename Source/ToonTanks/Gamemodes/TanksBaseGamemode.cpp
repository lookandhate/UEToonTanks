// Fill out your copyright notice in the Description page of Project Settings.


#include "TanksBaseGamemode.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"
#include "Kismet/GameplayStatics.h"

void ATanksBaseGamemode::BeginPlay()
{
	Super::BeginPlay();
	
	m_TargetTurrets = CountTargetsToDestroy();
	m_PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	
	HandleGameStart();
}

void ATanksBaseGamemode::ActorDied(AActor* DiedActor)
{
	UE_LOG(LogGameMode,Display, TEXT("Killing actor %s"), *DiedActor->GetName());

	// Check if died actor is player tank
	if(DiedActor == m_PlayerTank)
	{
		// If it is than Handle it's destruction and finish the game
		m_PlayerTank->HandleDestruction();
		HandleGameOver(false);

		if (m_PlayerController)
			m_PlayerController->SetPlayerEnableState(false);
	}
	// If died actor is turrent than 
	else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DiedActor))
	{
		DestroyedTurret->HandleDestruction();
		m_TargetTurrets -=1;
		if (m_TargetTurrets == 0)
			HandleGameOver(true);
	}

}

void ATanksBaseGamemode::HandleGameStart()
{
	m_PlayerController = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));
	GameStart();

	// In order to hide cursor during countdown, disable controller 
	if(m_PlayerController)
	{
		m_PlayerController->SetPlayerEnableState(false);

		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(m_PlayerController, &APlayerControllerBase::SetPlayerEnableState, true);

		GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);	
	}
}

void ATanksBaseGamemode::HandleGameOver(bool IsPlayerWon)
{
	GameOver(IsPlayerWon);
}

int64 ATanksBaseGamemode::CountTargetsToDestroy() const
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), Actors);
	return Actors.Num(); 
}

