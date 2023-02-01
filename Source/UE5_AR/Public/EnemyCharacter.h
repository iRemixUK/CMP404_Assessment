// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class UE5_AR_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(Category = "Variables", EditAnywhere, BlueprintReadWrite)
		float Health;

	UPROPERTY(Category = "Variables", EditAnywhere, BlueprintReadWrite)
		FVector LocationToRun;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Functions to take damage from the abilities
	UFUNCTION(BlueprintCallable, Category = "TakeDamage")
		void TakeAbilityDamage(float Damage);
	
	void TickFire(float DeltaTime);
	
	void TickAcid(float DeltaTime);

	UPROPERTY(Category = "Variables", EditAnywhere, BlueprintReadWrite)
	bool StartAcid = false;
	
	UPROPERTY(Category = "Variables", EditAnywhere, BlueprintReadWrite)
	bool StartFire = false;

	float AcidStartTime = 0.f;
	float FireStartTime = 0.f;

private:
	
};
