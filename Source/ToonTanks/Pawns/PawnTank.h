// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "PawnTank.generated.h"


class UCameraComponent;
class USpringArmComponent;

/**
 * 
 */
UCLASS()
class TOONTANKS_API APawnTank : public ABasePawn
{
	GENERATED_BODY()
private:


public:
	APawnTank();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void HandleDestruction() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool IsAlive() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", DisplayName ="Spring Arm",  meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* m_SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", DisplayName ="Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* m_CameraComponent;

	FVector m_MoveDirection;
	FQuat m_RotationDirection;

	APlayerController* m_PlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", DisplayName="Move speed", meta = (AllowPrivateAccess = "true"))
	float m_MoveSpeed = 1000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", DisplayName="Rotate Speed", meta = (AllowPrivateAccess = "true"))
	float m_RotateSpeed = 100.f;
	
	bool m_bIsAlive = true;

	
	
private:
	void CalculateMoveInput(float Value);
	void CalculateRotateInput(float Value);

	void Move();
	void Rotate();
	
};