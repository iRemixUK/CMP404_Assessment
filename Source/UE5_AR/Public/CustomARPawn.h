// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "CustomARPawn.generated.h"

class UCameraComponent;

UCLASS()
class UE5_AR_API ACustomARPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACustomARPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnScreenTouch(const ETouchIndex::Type FingerIndex, const FVector ScreenPos);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadWrite)
		USceneComponent* SceneComponent;

	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadWrite)
		UCameraComponent* CameraComponent;
	
	UFUNCTION(BlueprintCallable, Category = "LineTrace")
	FVector LineTraceMethod();
	
	UFUNCTION(BlueprintCallable, Category = "ActiveAbility")
	void SetActiveAbility(FString Ability);
	
	UPROPERTY(Category = "ActiveAbility", VisibleAnywhere, BlueprintReadWrite)
	FString ActiveAbility;

	UFUNCTION(BlueprintCallable, Category = "ActiveAbility")
	FString GetActiveAbility();
};





