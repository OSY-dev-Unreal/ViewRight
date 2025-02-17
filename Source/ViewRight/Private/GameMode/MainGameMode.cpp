// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/MainGameMode.h"

#include "GameMode/MainHUD.h"
#include "GameMode/MainPawn.h"
#include "GameMode/MainPlayerController.h"

AMainGameMode::AMainGameMode()
{
	//Seting player
	//DefaultPawnClass = AMainPawn::StaticClass();
	ConstructorHelpers::FClassFinder<AMainPawn> PawnClass(TEXT("/Script/Engine.Blueprint'/Game/LB/GameMode/BP_MainPawn.BP_MainPawn_C'"));
	if (PawnClass.Class)
	{
		DefaultPawnClass = PawnClass.Class;
	}
	//Seting controller
	//PlayerControllerClass = AMainPlayerController::StaticClass();
	ConstructorHelpers::FClassFinder<AMainPlayerController> ControllerClass(TEXT("/Script/Engine.Blueprint'/Game/LB/GameMode/BP_MainPlayercontroller.BP_MainPlayercontroller_C'"));
	if (ControllerClass.Class)
	{
		PlayerControllerClass = ControllerClass.Class;
	}
	//Seting HUD
	HUDClass = AMainHUD::StaticClass();
}
