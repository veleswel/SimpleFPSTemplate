// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSLaunchPad.h"

#include "Components/BoxComponent.h"

#include "GameFramework/Character.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSLaunchPad::AFPSLaunchPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OverlapCmp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapCmp"));

	RootComponent = OverlapCmp;

	OverlapCmp->OnComponentBeginOverlap.AddDynamic(this, &AFPSLaunchPad::HandleOnComponentBeginOverlap);

	LaunchAngle = 45.f;
	LaunchStrength = 1500.f;
}

// Called when the game starts or when spawned
void AFPSLaunchPad::BeginPlay()
{
	Super::BeginPlay();
}

void AFPSLaunchPad::HandleOnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FRotator launchDirection = GetActorRotation();
	launchDirection.Pitch += LaunchAngle;
	FVector launchVelocity = launchDirection.Vector() * LaunchStrength;

	ACharacter* character = Cast<ACharacter>(OtherActor);
	if (character != nullptr)
	{
		character->LaunchCharacter(launchVelocity, true, true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, GetActorLocation());
	}
	else if (OtherComp != nullptr && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulse(launchVelocity, NAME_None, true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, GetActorLocation());
	}
}

// Called every frame
void AFPSLaunchPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

