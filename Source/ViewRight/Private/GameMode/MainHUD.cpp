// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/MainHUD.h"
#include "LB/UMG/LB_MainUI.h"

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();
	//MainUI = Cast<ULB_MainUI>(LoadClass<ULB_MainUI>(NULL,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/LB/UMG/BP_MainUI.BP_MainUI_C'")));
	MainUI = CreateWidget<ULB_MainUI>(GetWorld()->GetFirstPlayerController(),LoadClass<ULB_MainUI>(NULL,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/LB/UMG/WBP_MainUI.WBP_MainUI_C'")));
	if (MainUI)
	{
		MainUI->AddToViewport();
	}
}
