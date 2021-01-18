// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAIGuard.h"

#include "Perception/PawnSensingComponent.h"

#include "DrawDebugHelpers.h"

#include "Kismet/KismetMathLibrary.h"

#include "FPSGameMode.h"
#include "FPSCharacter.h"

// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingCmp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingCmp"));

	PawnSensingCmp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnSeePawn);
	PawnSensingCmp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnHearNoise);
}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();

	OriginalOrientation = GetActorRotation();
}

void AFPSAIGuard::OnSeePawn(APawn* SeenPawn)
{
	if (SeenPawn == nullptr)
	{
		return;
	}

	AFPSCharacter* Player = Cast<AFPSCharacter>(SeenPawn);

	if (Player != nullptr)
	{
		DrawDebugSphere(GetWorld(), Player->GetActorLocation(), 32.f, 12, FColor::Yellow, false, 10.f);

		AFPSGameMode* GameMode = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->CompleteMission(Player, false);
		}
	}
}

void AFPSAIGuard::OnHearNoise(APawn* Pawn, const FVector& Location, float Volume)
{
	DrawDebugSphere(GetWorld(), Location, 32.f, 12, FColor::Red, false, 10.f);

	FRotator NewLookAt = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Location);
	NewLookAt.Normalize();

	NewLookAt.Pitch = 0.f;
	NewLookAt.Roll = 0.f;

	SetActorRotation(NewLookAt);

	GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrientation);
	GetWorldTimerManager().SetTimer(TimerHandle_ResetOrientation, this, &AFPSAIGuard::ResetOrientation, 3.f, false);
}

void AFPSAIGuard::ResetOrientation()
{
	SetActorRotation(OriginalOrientation);
}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
