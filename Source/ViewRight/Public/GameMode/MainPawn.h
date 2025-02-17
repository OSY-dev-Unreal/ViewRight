// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedPlayerInput.h"
#include "GameFramework/Pawn.h"
#include "MainPawn.generated.h"

UCLASS()
class VIEWRIGHT_API AMainPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMainPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//Camera movement and rotation
	void Move(const FInputActionValue& Value);
	void Rotation(const FInputActionValue& Value);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// Spring Arm Component
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="SpringArm")
	class USpringArmComponent* SpringArmComponent;

	// Camera Component
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	class UCameraComponent* CameraComponent;

	// Arrow Component
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Arrow")
	class UArrowComponent* ArrowComponent;


public:


	
	//Input mapping
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* MappingContext;
	//Move
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveAction;
	//Rotation
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* RotationAction;
	
};
