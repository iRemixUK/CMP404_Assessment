// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "HelloARManager.h"
#include "CustomGameMode.generated.h"

//Forward Declarations
class APlaceableActor;

/**
 * 
 */

UCLASS()
class UE5_AR_API ACustomGameMode : public AGameModeBase
{
	GENERATED_BODY()
private:

	FTimerHandle Ticker;
	APlaceableActor* SpawnedActor;

public:
	ACustomGameMode();
	virtual ~ACustomGameMode() = default;


	virtual void StartPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;

	/**
	 * @brief Perform a line trace at the screen position provided and place a default Placeable actor on it.
	 * Create another actor class that inherits from APlaceableActor and is spawned here instead of the default one. Make sure this new object is placed on the Plane rather than halfway through a plane
	 * @param ScreenPos Pass the Screen Position as an FVector
	 */
	virtual void LineTraceSpawnActor(FVector ScreenPos);
	

	/**
	 * @brief This function is virtual - you can inherit this class to override this function
	 * Each level can have their own unique spawned actors but with similar base qualities using inheritance
	 */
	virtual void SpawnInitialActors();

	 UPROPERTY(Category="Placeable",EditAnywhere, BlueprintReadWrite)
	 TSubclassOf<APlaceableActor> PlacableToSpawn;

	UPROPERTY(Category = "EnemiesDefeated",EditAnywhere,BlueprintReadWrite)
		int EnemiesDefeated;

	UFUNCTION(BlueprintCallable, Category="EnemiesDefeated")
		int GetEnemiesDefeated();

	UFUNCTION(BlueprintCallable, Category="EnemiesDefeated")
		void IncrementEnemiesDefeated();

	UFUNCTION(BlueprintCallable, Category="Manager")
		void HidePlane();

	UPROPERTY(Category = "SpawnUI",EditAnywhere,BlueprintReadWrite)
	bool SpawnUI;

	AHelloARManager* Manager;

	UPROPERTY(Category = "Variable", EditAnywhere, BlueprintReadWrite)
	bool PlacementPhase = false;
};
