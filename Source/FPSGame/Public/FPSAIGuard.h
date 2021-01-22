// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"

class UPawnSensingComponent;

UENUM(BlueprintType)
enum class EAIGuardState : uint8
{
	Idle,

	Suspicious,

	Alerted
};

UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PawnSensingCmp;

	UFUNCTION()
	void OnSeePawn(APawn* pawn);

	UFUNCTION()
	void OnHearNoise(APawn* pawn, const FVector& location, float volume);

	UFUNCTION()
	void ResetOrientationAndState();

	FRotator OriginalOrientation;
	FTimerHandle TimerHandle_ResetOrientation;

	EAIGuardState GuardState;

	void SetGuardState(EAIGuardState NewState);

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void OnAIStateChanged(EAIGuardState NewState);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
