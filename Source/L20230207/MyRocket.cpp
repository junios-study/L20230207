// Fill out your copyright notice in the Description page of Project Settings.


#include "MyRocket.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyRocket::AMyRocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Box->SetBoxExtent(FVector(30, 10, 10));
	Box->SetGenerateOverlapEvents(true);

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Box);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Rocket(TEXT("/Script/Engine.StaticMesh'/Game/P38/Meshes/SM_Rocket.SM_Rocket'"));
	if (SM_Rocket.Succeeded())
	{
		Body->SetStaticMesh(SM_Rocket.Object);
	}
	Body->SetRelativeRotation(FRotator(-90.0f, 0, 0));

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->ProjectileGravityScale = 0.0f;
	Movement->InitialSpeed = 2000.0f;
}

// Called when the game starts or when spawned
void AMyRocket::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(3.0f);

	OnActorBeginOverlap.AddDynamic(this, &AMyRocket::ProcessBeginOverLap);
	
}

void AMyRocket::ProcessBeginOverLap(AActor* OverlappedActor, AActor* OtherActor)
{
	//CallToBP();
	CallToBPNative();

	UE_LOG(LogTemp, Warning, TEXT("Rocket %s"), *OtherActor->GetName());
	Destroy();

	if (ParticleTemplate)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
			ParticleTemplate,
			GetActorLocation(),
			FRotator::ZeroRotator);
	}
	if (ExplosionSound)
	{
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(),
			ExplosionSound,
			GetActorLocation());
	}
}

// Called every frame
void AMyRocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyRocket::PrintHelloWorld()
{
	UE_LOG(LogTemp, Error, TEXT("Hello World"));
}

void AMyRocket::CallToBPNative_Implementation()
{
	UE_LOG(LogClass, Warning, TEXT("이건 블루프린트 네이티브"));
}

