// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/MainPlayerController.h"

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//show Mouse
	bShowMouseCursor = true;
}

void AMainPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
