// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "PlaceableActor.generated.h"

class UARPin;

UCLASS()
class UE5_AR_API APlaceableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlaceableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(Category = "Variables", VisibleAnywhere, BlueprintReadWrite)
	float Health;

	UFUNCTION(BlueprintCallable, Category = "TakeDamage")
		void TakeDamageFromEnemy();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadWrite)
		USceneComponent* SceneComponent;

	UARPin*PinComponent;

	UPROPERTY(Category = "Variables", EditAnywhere, BlueprintReadWrite)
		FVector PlaceableScale;

	UPROPERTY(Category = "Variables", EditAnywhere, BlueprintReadWrite)
		FRotator PlaceableRotation;

	//void StopTracking();
	
};
