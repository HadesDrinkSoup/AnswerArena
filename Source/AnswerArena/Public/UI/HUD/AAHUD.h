// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AAHUD.generated.h"

struct FWidgetControllerParams;
class UOverlayWidgetController;
class UAAUserWidget;
class UCalculatorWidgetController;

UCLASS()
class ANSWERARENA_API AAAHUD : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TObjectPtr<UAAUserWidget> OverlayWidget;
	

	UPROPERTY()
	TObjectPtr<UAAUserWidget> CalculatorWidget;
	
	void InitOverlay(APlayerController* PC, APlayerState* PS);
	
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WidgetControllerParams);
	
	UCalculatorWidgetController* GetCalculatorWidgetController(const FWidgetControllerParams& WidgetControllerParams);

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAAUserWidget> OverlayWidgetClass;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
	
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	
	
	
	UPROPERTY(EditDefaultsOnly, Category = "Calculator UI")
	TSubclassOf<UAAUserWidget> CalculatorWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Calculator UI")
	TSubclassOf<UCalculatorWidgetController> CalculatorWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UCalculatorWidgetController> CalculatorWidgetController;
};