// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/MainPawn.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameMode/MainGameMode.h"
#include "GameMode/MainPlayerController.h"

// Sets default values
AMainPawn::AMainPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arr"));
	RootComponent = ArrowComponent;
	//ArrowComponent->SetupAttachment(RootComponent);
	// Create a SpringArmComponent
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	//Attached to the root component
	SpringArmComponent->SetupAttachment(ArrowComponent);
	//Set length
	SpringArmComponent->TargetArmLength = 1500.0f;
	// Rotate the arm based on the controller
	
	//Cancel camera collision
	SpringArmComponent->bDoCollisionTest = false;
	

	// Create a CameraComponent
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	//Attached to the SpringArmComponent
	CameraComponent->SetupAttachment(SpringArmComponent);
	// Camera Does not Rotate Relative to Arm
	CameraComponent->bUsePawnControlRotation = false;
	
	
}

// Called when the game starts or when spawned
void AMainPawn::BeginPlay()
{
	Super::BeginPlay();
	SpringArmComponent->SetRelativeRotation(FRotator(-45.0f,0.0f,0.0f));
}



// Called every frame
void AMainPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	auto controller = Cast<AMainPlayerController>(GetController());
	if (controller)
	{
		auto subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(controller->GetLocalPlayer());
		if (subsystem)
		{
			subsystem->AddMappingContext(MappingContext,0);
		}
	}
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent && MoveAction && RotationAction)
	{
		EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AMainPawn::Move);
		EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AMainPawn::Rotation);
	}

}

void AMainPawn::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	
	if (Controller)
	{
		AddMovementInput(GetActorForwardVector(),MovementVector.Y*10.0f);
		AddMovementInput(GetActorRightVector(),MovementVector.X*10.0f*-1.0f);
	}
}

void AMainPawn::Rotation(const FInputActionValue& Value)
{
	
}
