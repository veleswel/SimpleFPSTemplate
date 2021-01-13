// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSExtractionZone.h"

#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"

// Sets default values
AFPSExtractionZone::AFPSExtractionZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OverlapCmp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapCmp"));
	OverlapCmp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapCmp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	OverlapCmp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Overlap);
	OverlapCmp->SetBoxExtent(FVector(200.f));

	RootComponent = OverlapCmp;

	OverlapCmp->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractionZone::HandleOnComponentBeginOverlap);

	DecalCmp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalCmp"));
	DecalCmp->DecalSize = FVector(200.f);

	DecalCmp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AFPSExtractionZone::BeginPlay()
{
	Super::BeginPlay();
}

void AFPSExtractionZone::HandleOnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("Extraction zone overlapped!"));
}

// Called every frame
void AFPSExtractionZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
