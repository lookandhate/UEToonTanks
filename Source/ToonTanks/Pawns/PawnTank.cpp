// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


APawnTank::APawnTank()
{

	m_SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	m_SpringArm->SetupAttachment(RootComponent);
	
	m_CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_CameraComponent->SetupAttachment(m_SpringArm);
}

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();
	m_PlayerController = Cast<APlayerController>(GetController());
}

void APawnTank::HandleDestruction()
{
	Super::HandleDestruction();

	m_bIsAlive = false;

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);

	
	//Destroy();
}

void APawnTank::CalculateMoveInput(float Value)
{
	m_MoveDirection = FVector(Value * m_MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
}

void APawnTank::CalculateRotateInput(float Value)
{
	float fRotateAmount = Value * m_RotateSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator(0, fRotateAmount, 0);
	m_RotationDirection = FQuat(Rotation);
}

void APawnTank::Move()
{
	AddActorLocalOffset(m_MoveDirection, true);
}

void APawnTank::Rotate()
{
	 AddActorLocalRotation(m_RotationDirection, true);
}

void APawnTank::Fire()
{
	if(m_Shells <=0)
		return;
	m_Shells--;
	if(m_bDebugCombat)
	{
		GEngine->AddOnScreenDebugMessage(4, 4, FColor::Yellow, FString::Printf(TEXT("%d sheels left"), m_Shells));
	}
	
	OnFire();
	Super::Fire();

}


// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Rotate();
	Move();

	if(m_PlayerController)
	{
		FHitResult TraceHitResult;
		m_PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, TraceHitResult);

		FVector HitLoccation = TraceHitResult.ImpactPoint;
		RotateTurret(HitLoccation);
	}

}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotateInput);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnTank::Fire);
	
}

bool APawnTank::IsAlive() const
{
	return m_bIsAlive;
}

