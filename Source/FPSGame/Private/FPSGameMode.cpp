// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"

#include "Kismet/GameplayStatics.h"

#include "UObject/ConstructorHelpers.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();

	bIsMissionEnded = false;
}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn, bool bMissionSuccess)
{
	if (bIsMissionEnded)
	{
		return;
	}

	if (InstigatorPawn == nullptr)
	{
		return;
	}

	InstigatorPawn->DisableInput(nullptr);

	APlayerController* playerController = Cast<APlayerController>(InstigatorPawn->GetController());
	if (playerController == nullptr)
	{
		return;
	}

	if (SpectatingViewpointClass != nullptr)
	{
		TArray<AActor*> actorsOfClass;

		UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpointClass, actorsOfClass);

		if (actorsOfClass.Num() > 0)
		{
			AActor* newViewTarget = actorsOfClass[0];
			playerController->SetViewTargetWithBlend(newViewTarget, .5f, EViewTargetBlendFunction::VTBlend_Cubic);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SpectatingViewpointClass is nullptr!"));
	}

	bIsMissionEnded = true;

	OnMissionCompleted(InstigatorPawn, bMissionSuccess);
}