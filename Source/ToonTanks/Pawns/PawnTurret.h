// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "PawnTurret.generated.h"

/**
 * 
 */
DECLARE_LOG_CATEGORY_CLASS(LogTurret, Log, Log)
class APawnTank;


UCLASS()
class TOONTANKS_API APawnTurret : public ABasePawn
{
	GENERATED_BODY()
	
public:
	APawnTurret();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void HandleDestruction() override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	void CheckFireCondition();
	float DistanceToPlayer() const;


	// DEBUG METHODS
	void DrawLineToTank() const;
	void PrintDebugInfoAboutDistance() const;


private:
	FTimerHandle m_FireRateTimerHandle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat system", DisplayName="Fire Rate", meta = (AllowPrivateAccess = "true"))
	float m_fFireRate = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat system", DisplayName="Max Fire Distance", meta = (AllowPrivateAccess = "true"))
	float m_fFireDistance = 1000.f;
	
	APawnTank* m_PlayerPawn;

	//DEBUG

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Debug", DisplayName="Show debug info about player tank location", meta = (AllowPrivateAccess = "true"))
	bool m_TankLocationDebug = false;
};
