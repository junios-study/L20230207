// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyRocket.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;

UCLASS()
class L20230207_API AMyRocket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyRocket();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void ProcessBeginOverLap(AActor* OverlappedActor, AActor* OtherActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category="Components", BlueprintReadOnly)
	UBoxComponent* Box;

	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly)
	UStaticMeshComponent* Body;

	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly)
	UProjectileMovementComponent* Movement;

};
