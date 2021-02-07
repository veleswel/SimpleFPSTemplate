// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameState.h"
#include "FPSPlayerController.h"

#include "Kismet/GameplayStatics.h"

#include "EngineUtils.h"

void AFPSGameState::MulticastOnMissionCompleted_Implementation(APawn* InstigatorPawn, bool bMissionSuccess)
{
	for (TActorIterator<APlayerController> It(GetWorld()); It; ++It)
	{
		AFPSPlayerController* PlayerController = Cast<AFPSPlayerController>(*It);
		if (PlayerController != nullptr && PlayerController->IsLocalController())
		{
			PlayerController->OnMissionCompleted(InstigatorPawn, bMissionSuccess);

			APawn* Pawn = PlayerController->GetPawn();
			if (Pawn != nullptr)
			{
				Pawn->DisableInput(PlayerController);
			}

			if (PlayerController->SpectatingViewpointClass != nullptr)
			{
				TArray<AActor*> ActorsOfClass;

				UGameplayStatics::GetAllActorsOfClass(this, PlayerController->SpectatingViewpointClass, ActorsOfClass);

				if (ActorsOfClass.Num() > 0)
				{
					AActor* NewViewTarget = ActorsOfClass[0];
					PlayerController->SetViewTargetWithBlend(NewViewTarget, .5f, EViewTargetBlendFunction::VTBlend_Cubic);
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("SpectatingViewpointClass is nullptr!"));
			}
		}
	}
}