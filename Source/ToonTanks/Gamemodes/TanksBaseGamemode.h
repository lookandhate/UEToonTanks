// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TanksBaseGamemode.generated.h"

class APawnTurret;
class APawnTank;
class APlayerControllerBase;

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATanksBaseGamemode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	void ActorDied(AActor* DiedActor);

private:
	void HandleGameStart();
	void HandleGameOver(bool IsPlayerWon);

	int64 CountTargetsToDestroy() const;
	
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool IsLocalPlayerWon);

	

private:
	APawnTank* m_PlayerTank;
	APlayerControllerBase* m_PlayerController;
	int32 m_TargetTurrets;
	

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Game Loop")
	int32 StartDelay = 3;
};
