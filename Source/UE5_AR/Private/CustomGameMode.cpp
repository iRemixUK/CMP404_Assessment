// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameMode.h"
#include "CustomARPawn.h"
#include "CustomGameState.h"
#include "CustomActor.h"
#include "HelloARManager.h"
#include "ARPin.h"
#include "ARBlueprintLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "PlaceableActor.h"

ACustomGameMode::ACustomGameMode():
	SpawnedActor(nullptr)
{
	// Add this line to your code if you wish to use the Tick() function
	PrimaryActorTick.bCanEverTick = true;

	// Set the default pawn and gamestate to be our custom pawn and gamestate programatically
	DefaultPawnClass = ACustomARPawn::StaticClass();
	GameStateClass = ACustomGameState::StaticClass();

	EnemiesDefeated = 0;
	SpawnUI = false;
}


void ACustomGameMode::StartPlay() 
{
	SpawnInitialActors();
	
	// This function will transcend to call BeginPlay on all the actors 
	Super::StartPlay();
}


void ACustomGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

int ACustomGameMode::GetEnemiesDefeated()
{
	// Returns the amount of enemies defeated
	return EnemiesDefeated;
}

void ACustomGameMode::IncrementEnemiesDefeated()
{
	// If an enemy is killed increment enemies defeated
	EnemiesDefeated = EnemiesDefeated + 1;
}

void ACustomGameMode::HidePlane()
{
	// Hides the ARCore planes
	Manager->SetActorHiddenInGame(true);
	Manager->SetActorEnableCollision(false);
	Manager->SetActorTickEnabled(false);
	Manager->Config->bTrackSceneObjects = false;
	Manager->ResetARCoreSession();
}

void ACustomGameMode::SpawnInitialActors()
{
	// Spawn an instance of the HelloARManager class
	const FActorSpawnParameters SpawnInfo;
	const FRotator MyRot(0, 0, 0);
	const FVector MyLoc(0, 0, 0);

	Manager = GetWorld()->SpawnActor<AHelloARManager>(MyLoc, MyRot, SpawnInfo);
}


void ACustomGameMode::LineTraceSpawnActor(FVector ScreenPos)
{
	// Check if the placement phase is active. If so spawn and move the placeable actor if not do nothing.
	if(PlacementPhase == true)
	{
		//Basic variables for functionality
		APlayerController* playerController = UGameplayStatics::GetPlayerController(this, 0);
		FVector WorldPos;
		FVector WorldDir;

		//Gets the screen touch in world space and the tracked objects from a line trace from the touch
		UGameplayStatics::DeprojectScreenToWorld(playerController, FVector2D(ScreenPos), WorldPos, WorldDir);
		// Notice that this LineTrace is in the ARBluePrintLibrary - this means that it's exclusive only for objects tracked by ARKit/ARCore
		auto TraceResult = UARBlueprintLibrary::LineTraceTrackedObjects(FVector2D(ScreenPos), false, false, false, true);

		//Checks if the location is valid
		if (TraceResult.IsValidIndex(0))
		{
		// Get the first found object in the line trace - ignoring the rest of the array elements
			auto TrackedTF = TraceResult[0].GetLocalToWorldTransform();

			if (FVector::DotProduct(TrackedTF.GetRotation().GetUpVector(), WorldDir) < 0)
			{
			//Spawn the actor pin and get the transform
				UARPin* ActorPin = UARBlueprintLibrary::PinComponent(nullptr, TraceResult[0].GetLocalToWorldTransform(), TraceResult[0].GetTrackedGeometry());

				// Check if ARPins are available on your current device. ARPins are currently not supported locally by ARKit, so on iOS, this will always be "FALSE" 
				if (ActorPin)
				{
					//If the pin is valid 
					auto PinTF = ActorPin->GetLocalToWorldTransform();
					//Spawn a new Actor at the location if not done yet
					if (!SpawnedActor)
					{
						const FActorSpawnParameters SpawnInfo;
						const FRotator MyRot(0, 0, 0);
						const FVector MyLoc(0, 0, 0);
						SpawnedActor = GetWorld()->SpawnActor<APlaceableActor>(PlacableToSpawn, MyLoc, MyRot, SpawnInfo);
					}
					// Set the spawned actor location based on the Pin. Have a look at the code for Placeable Object to see how it handles the AR PIN passed on
					SpawnedActor->SetActorTransform(PinTF);
					SpawnedActor->PinComponent = ActorPin;
					SpawnUI = true;
				}
				// IF ARPins are Not supported locally (for iOS Devices) We will spawn the object in the location where the line trace has hit
				else
				{
					GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("ARPin is invalid"));
					//Spawn a new Actor at the location if not done yet
					if (!SpawnedActor)
					{
						const FActorSpawnParameters SpawnInfo;
						const FRotator MyRot(0, 0, 0);
						const FVector MyLoc(0, 0, 0);
						SpawnedActor = GetWorld()->SpawnActor<APlaceableActor>(PlacableToSpawn, MyLoc, MyRot, SpawnInfo);
					}
					SpawnedActor->SetActorTransform(TrackedTF);
					SpawnedActor->SetActorScale3D(FVector(0.2, 0.2, 0.2));
				}
			}
		}
	}
}

