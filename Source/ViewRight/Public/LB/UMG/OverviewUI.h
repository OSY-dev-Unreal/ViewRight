// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OverviewUI.generated.h"

/**
 * 
 */
UCLASS()
class VIEWRIGHT_API UOverviewUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	FString Workers;
	UPROPERTY(BlueprintReadWrite)
	FString GeographicalLocation;
	UPROPERTY(BlueprintReadWrite)
	FString PlotRatio;
	UPROPERTY(BlueprintReadWrite)
	FString BuildingDensity;
	UPROPERTY(BlueprintReadWrite)
	FString BuildingScale;
	UPROPERTY(BlueprintReadWrite)
	FString NumberOfParkingSpaces;
};
