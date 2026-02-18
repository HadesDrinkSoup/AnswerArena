// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/HUD/AAHUD.h"
#include "UI/Widget/AAUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/WidgetController/CalculatorWidgetController.h"

void AAAHUD::InitOverlay(APlayerController* PC, APlayerState* PS)
{
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass未设置，请在BP_AuraHUD设置OverlayWidgetClass"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass未设置，请在BP_AuraHUD设置OverlayWidgetControllerClass"));
	
	UUserWidget* OverlayUserWidget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAAUserWidget>(OverlayUserWidget);
	const FWidgetControllerParams OverlayWidgetControllerParams(PC, PS);
	OverlayWidgetController = GetOverlayWidgetController(OverlayWidgetControllerParams);
	OverlayWidget->SetWidgetController(OverlayWidgetController);
	OverlayWidgetController->BroadcastInitialValues();
	OverlayUserWidget->AddToViewport();
}

UOverlayWidgetController* AAAHUD::GetOverlayWidgetController(const FWidgetControllerParams& WidgetControllerParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WidgetControllerParams);
		OverlayWidgetController->BindCallBacks();
		return OverlayWidgetController;
	}
	return OverlayWidgetController;
}

UCalculatorWidgetController* AAAHUD::GetCalculatorWidgetController(const FWidgetControllerParams& WidgetControllerParams)
{
	if (CalculatorWidgetController == nullptr)
	{
		CalculatorWidgetController = NewObject<UCalculatorWidgetController>(this, CalculatorWidgetControllerClass);
		CalculatorWidgetController->SetWidgetControllerParams(WidgetControllerParams);
		CalculatorWidgetController->BindCallBacks();
		return CalculatorWidgetController;
	}
	return CalculatorWidgetController;
}