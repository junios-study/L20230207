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

	UPROPERTY(EditAnywhere, Category = "Data", BlueprintReadWrite)
	class UParticleSystem* ParticleTemplate;


	UPROPERTY(EditAnywhere, Category = "Data", BlueprintReadWrite)
	class USoundBase* ExplosionSound;

	UFUNCTION(BlueprintCallable, Category="Test")
	void PrintHelloWorld();

	UFUNCTION(BlueprintImplementableEvent) //기본 로직, BP에서 구현
	void CallToBP();

	UFUNCTION(BlueprintNativeEvent) //기본 C++, 추가로 BP에서 구현
	void CallToBPNative(); //engine BP, C++
	void CallToBPNative_Implementation(); //C++ 기본 구현
};
