// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"

#include "MyPawn.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UArrowComponent;
class UFloatingPawnMovement;

UCLASS()
class L20230207_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void RotatePropeller(UStaticMeshComponent* Where);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Rotation(const FInputActionValue& Value);

	void Fire(const FInputActionValue& Value);

	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly)
	UBoxComponent* Box;

	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly)
	UStaticMeshComponent* Body;

	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly)
	UStaticMeshComponent* Left;

	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly)
	UStaticMeshComponent* Right;

	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly)
	UArrowComponent* Arrow;

	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly)
	UFloatingPawnMovement* Movement;


	UPROPERTY(EditAnywhere, Category = "Input", BlueprintReadWrite)
	class UInputMappingContext* InputContext;


	UPROPERTY(EditAnywhere, Category = "Input", BlueprintReadWrite)
	class UInputAction* RotationAction;

	UPROPERTY(EditAnywhere, Category = "Input", BlueprintReadWrite)
	class UInputAction* FireAction;

	UPROPERTY(EditAnywhere, Category = "Data", BlueprintReadWrite)
	TSubclassOf<class AMyRocket> RocketTemplate;
};
