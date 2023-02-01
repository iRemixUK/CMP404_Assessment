// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomARPawn.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "ARBlueprintLibrary.h"
#include "Camera/CameraComponent.h"
#include "CustomGameMode.h"
#include "PlaceableActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACustomARPawn::ACustomARPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SceneComponent);

	// Set active ability
	ActiveAbility = "Lightning";
}

// Called when the game starts or when spawned
void ACustomARPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACustomARPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACustomARPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// If the player has touched the screen call the OnScreenTouch function
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ACustomARPawn::OnScreenTouch);
}

FVector ACustomARPawn::LineTraceMethod()
{
	// Do a line trace and return the hit position in world space
	FVector StartPoint = CameraComponent->GetComponentLocation();
	FVector EndPoint = (CameraComponent->GetForwardVector() * 20000.f) + StartPoint;
	FCollisionQueryParams Parameters;
	Parameters.AddIgnoredActor(this);
	FHitResult HitResult;
	bool isHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, ECC_Visibility, Parameters);

	return HitResult.Location;
}

void ACustomARPawn::SetActiveAbility(FString Ability)
{
	// Set the active ability 
	if (Ability == "Lightning")
	{
		ActiveAbility = Ability;
	}

	if (Ability == "Fire")
	{
		ActiveAbility = Ability;
	}

	if (Ability == "Acid")
	{
		ActiveAbility = Ability;
	}
}

FString ACustomARPawn::GetActiveAbility()
{
	// Get the active ability
	return ActiveAbility;
}

void ACustomARPawn::OnScreenTouch(const ETouchIndex::Type FingerIndex, const FVector ScreenPos)
{
	// Call line trace spawn actor when the screen has been touched
	auto Temp = GetWorld()->GetAuthGameMode();
	auto GM = Cast<ACustomGameMode>(Temp);
	
	if(GM)
	{
		GM->LineTraceSpawnActor(ScreenPos);
	}
}
