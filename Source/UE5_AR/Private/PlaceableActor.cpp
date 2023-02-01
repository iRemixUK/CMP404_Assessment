// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaceableActor.h"
#include "ARPin.h"
#include "ARBlueprintLibrary.h"
#include "CustomARPawn.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlaceableActor::APlaceableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	// Set health
	Health = 100.f;

	// Set initial scale and rotation
	PlaceableScale = FVector(0.02f,0.02f, 0.02f);
	PlaceableRotation = FRotator(0.f,0.f,0.f);
	
}

// Called when the game starts or when spawned
void APlaceableActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlaceableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Making sure the actor remains on the ARPin that has been found.
	if(PinComponent)
	{
		auto TrackingState = PinComponent->GetTrackingState();
		
		switch (TrackingState)
		{
		case EARTrackingState::Tracking:
			SceneComponent->SetVisibility(true);
			SetActorTransform(PinComponent->GetLocalToWorldTransform());

			// Set placeable actor scale and rotation
			SetActorScale3D(PlaceableScale);
			SetActorRotation(PlaceableRotation);
			
			break;

		case EARTrackingState::NotTracking:
			PinComponent = nullptr;   

			break;

		}
	}
}

void APlaceableActor::TakeDamageFromEnemy()
{
	// Take damage from enemy when enemy reaches the placeable actor's location
	Health = Health - 10.f;
}




