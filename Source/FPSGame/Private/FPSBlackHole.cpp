// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSBlackHole.h"

#include "Components/SphereComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Engine/StaticMeshActor.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
AFPSBlackHole::AFPSBlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RootComponent = MeshComponent;

	DestroySphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("DestroySphereComponent"));
	DestroySphereComponent->SetupAttachment(MeshComponent);

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComponent"));
	RadialForceComponent->SetupAttachment(MeshComponent);
}

// Called when the game starts or when spawned
void AFPSBlackHole::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFPSBlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RadialForceComponent->FireImpulse();

	TArray<AActor*> overlappingActors;
	DestroySphereComponent->GetOverlappingActors(overlappingActors);

	for (AActor* actor : overlappingActors)
	{
		actor->Destroy();
	}
}

