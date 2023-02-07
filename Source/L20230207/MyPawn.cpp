// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ArrowComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MyRocket.h"

#include "Kismet/GameplayStatics.h"




// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Box);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Body(TEXT("/Script/Engine.StaticMesh'/Game/P38/Meshes/SM_P38_Body.SM_P38_Body'"));
	if (SM_Body.Succeeded())
	{
		Body->SetStaticMesh(SM_Body.Object);
	}


	Left = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left"));
	Left->SetupAttachment(Body);

	Right = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right"));
	Right->SetupAttachment(Body);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Propeller(TEXT("/Script/Engine.StaticMesh'/Game/P38/Meshes/SM_P38_Propeller.SM_P38_Propeller'"));
	if (SM_Propeller.Succeeded())
	{
		Left->SetStaticMesh(SM_Propeller.Object);
		Right->SetStaticMesh(SM_Propeller.Object);
	}

	Left->SetRelativeLocation(FVector(37.0f, -21.0f, 1.3f));
	Right->SetRelativeLocation(FVector(37.0f, 21.0f, 1.3f));

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Box);
	Arrow->SetRelativeLocation(FVector(300, 0, 0));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Box);
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	Movement->MaxSpeed = 400.0f;


	static ConstructorHelpers::FObjectFinder<UInputAction> IA_Rotation(TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprints/Input/IA_Rotation.IA_Rotation'"));
	if (IA_Rotation.Succeeded())
	{
		RotationAction = IA_Rotation.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_Fire(TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprints/Input/IA_Fire.IA_Fire'"));
	if (IA_Fire.Succeeded())
	{
		FireAction = IA_Fire.Object;
	}

	//static ConstructorHelpers::FObjectFinder<UDataAsset> IMC_Input(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Blueprints/Input/IMC_Input.IMC_Input'"));
	//if (IMC_Input.Succeeded())
	//{
	//	InputContext = IMC_Input.Object;
	//}
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	//APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC && InputContext)
	{
		UEnhancedInputLocalPlayerSubsystem* System = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
		if (System)
		{
			System->AddMappingContext(InputContext, 0);
		}
	}
}



// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddMovementInput(GetActorForwardVector(), 1.0f);

	//Left->AddLocalRotation(FRotator(0, 0, 3600 * DeltaTime));
	//Right->AddLocalRotation(FRotator(0, 0, 3600 * DeltaTime));
	RotatePropeller(Left);
	RotatePropeller(Right);

}

void AMyPawn::RotatePropeller(UStaticMeshComponent* Where)
{
	Where->AddLocalRotation(FRotator(0, 0, 3600 * UGameplayStatics::GetWorldDeltaSeconds(GetWorld())));
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	UEnhancedInputComponent* EInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EInputComponent)
	{
		EInputComponent->BindAction(RotationAction, ETriggerEvent::Triggered, this, &AMyPawn::Rotation);

		EInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &AMyPawn::Fire);
	}
}

void AMyPawn::Rotation(const FInputActionValue& Value)
{

}

void AMyPawn::Fire(const FInputActionValue& Value)
{
	GetWorld()->SpawnActor<AMyRocket>(AMyRocket::StaticClass(), Arrow->K2_GetComponentToWorld());
}

