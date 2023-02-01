// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "AIController.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Health = 100.f;
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(Health <= 0.f)
	{
		Destroy();
	}

	// Check if the enemy should take acid damage
	if (StartAcid == true)
	{
		// Apply acid damage over time
		AcidStartTime = AcidStartTime + DeltaTime;
		TickAcid(DeltaTime);

		if(AcidStartTime >= 7.0f)
		{
			AcidStartTime = 0.f;
			StartAcid = false;
		}
	}

	// Check if the enemy should take fire damage
	if (StartFire == true)
	{
		// Apply fire damage over time
		FireStartTime = FireStartTime + DeltaTime;
		TickFire(DeltaTime);

		if(FireStartTime >= 3.0f)
		{
			FireStartTime = 0.f;
			StartFire = false;
		}
	}
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemyCharacter::TakeAbilityDamage(float Damage)
{
	// Reduce health of enemy
	Health = Health - Damage;
}

void AEnemyCharacter::TickFire(float DeltaTime)
{
	// Reduce health of enemy over time
	Health = Health - (10 * DeltaTime);
}

void AEnemyCharacter::TickAcid(float DeltaTime)
{
	// Reduce health of enemy over time
	Health = Health - (15 * DeltaTime);
}


