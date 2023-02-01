// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ability.generated.h"

UCLASS()
class UE5_AR_API AAbility : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbility();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(Category = "Variables", EditAnywhere, BlueprintReadWrite)
	float Damage;
	
	UPROPERTY(Category = "Variables", EditAnywhere, BlueprintReadWrite)
	float TimeElapsed;

	UPROPERTY(Category = "Variables", EditAnywhere, BlueprintReadWrite)
	float TimeToRun;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
