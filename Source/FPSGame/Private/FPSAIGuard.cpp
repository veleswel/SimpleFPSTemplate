// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAIGuard.h"

#include "Perception/PawnSensingComponent.h"

#include "DrawDebugHelpers.h"

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
}

void AFPSAIGuard::OnSeePawn(APawn* pawn)
{
	if (pawn != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("AFPSAIGuard::OnSeePawn"));
		DrawDebugSphere(GetWorld(), pawn->GetActorLocation(), 32.f, 12, FColor::Yellow, false, 10.f);
	}
}

void AFPSAIGuard::OnHearNoise(APawn* pawn, const FVector& location, float volume)
{
	UE_LOG(LogTemp, Log, TEXT("AFPSAIGuard::OnHearNoise"));
	DrawDebugSphere(GetWorld(), location, 32.f, 12, FColor::Red, false, 10.f);
}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
