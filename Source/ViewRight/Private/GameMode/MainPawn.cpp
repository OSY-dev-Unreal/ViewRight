// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/MainPawn.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameMode/MainGameMode.h"
#include "GameMode/MainPlayerController.h"
#include "Kismet/KismetMathLibrary.h"

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
	SpringArmComponent->TargetArmLength = 15000.0f;
	// Rotate the arm based on the controller
	
	//Cancel camera collision
	SpringArmComponent->bDoCollisionTest = false;
	

	// Create a CameraComponent
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	//Attached to the SpringArmComponent
	CameraComponent->SetupAttachment(SpringArmComponent);
	// Camera Does not Rotate Relative to Arm
	CameraComponent->bUsePawnControlRotation = false;
	
	MoveSpeed_X = 1000.0f;
	MoveSpeed_Y = 1000.0f;
}

// Called when the game starts or when spawned
void AMainPawn::BeginPlay()
{
	Super::BeginPlay();
	SpringArmComponent->SetRelativeRotation(FRotator(-45.0f,0.0f,0.0f));

	NewArmLength = SpringArmComponent->TargetArmLength;
}



// Called every frame
void AMainPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SpringArmComponent->TargetArmLength = UKismetMathLibrary::FInterpTo(SpringArmComponent->TargetArmLength,NewArmLength,DeltaTime,3.0f);
	

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
		EnhancedInputComponent->BindAction(RotationAction,ETriggerEvent::Triggered,this,&AMainPawn::Rotation);
		EnhancedInputComponent->BindAction(LengthAction,ETriggerEvent::Triggered,this,&AMainPawn::ArmLength);
	}

}

void AMainPawn::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	
	if (Controller)
	{
		AddMovementInput(UKismetMathLibrary::GetRightVector(FRotator(0.0f,GetControlRotation().Yaw,GetControlRotation().Roll)),MovementVector.X*MoveSpeed_X);
		AddMovementInput(UKismetMathLibrary::GetForwardVector(FRotator(0.0f,GetControlRotation().Yaw,0.0f)),MovementVector.Y*MoveSpeed_Y);
	}
}

void AMainPawn::Rotation(const FInputActionValue& Value)
{
	FVector2D RotationVector = Value.Get<FVector2D>();
	if (Controller)
	{
		
		AddControllerYawInput(RotationVector.X);
		AddControllerPitchInput(RotationVector.Y);
	}
}

void AMainPawn::ArmLength(const FInputActionValue& Value)
{
	float LengthValue = Value.Get<float>();
	NewArmLength = UKismetMathLibrary::FClamp(SpringArmComponent->TargetArmLength+LengthValue*500.0f,50.0f,100000.0f);
	
}
