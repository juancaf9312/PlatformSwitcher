// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameWidget.generated.h"

/**
 * 
 */
class UTextBlock;

UCLASS()
class PLATFORMSWITCHER_API UGameWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Load();

	void OnGameOver(bool win);

	UPROPERTY()
		UTextBlock* MessageText;
	
	
};
