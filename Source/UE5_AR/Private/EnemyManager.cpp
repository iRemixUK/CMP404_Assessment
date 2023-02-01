// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"
#include "EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyManager::AEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();

	// Call spawn enemy function on begin play
	CallSpawnEnemies();
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyManager::SpawnEnemy()
{
	// Spawn an enemy
	const FActorSpawnParameters SpawnInfo;
	const FRotator MyRot(0, 0, 0);
	const FVector MyLoc = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z );
	
	Enemy = GetWorld()->SpawnActor<AEnemyCharacter>(EnemyToSpawn, MyLoc, MyRot, SpawnInfo);
	Enemy->SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z ));
}

void AEnemyManager::CallSpawnEnemies()
{
	// Spawn an enemy every 1 - 4 seconds
	float RandomSpawnTime = FMath::RandRange(1, 4);
	GetWorldTimerManager().SetTimer(Ticker, this, &AEnemyManager::SpawnEnemy, RandomSpawnTime, true, 0.0f);
}
