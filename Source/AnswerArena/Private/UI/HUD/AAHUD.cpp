// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/AAHUD.h"
#include "UI/Widget/AAUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

void AAAHUD::InitOverlay(APlayerController* PC, APlayerState* PS)
{
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass未设置，请在BP_AuraHUD设置OverlayWidgetClass"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass未设置，请在BP_AuraHUD设置OverlayWidgetControllerClass"));
	
	UUserWidget* UserWidget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAAUserWidget>(UserWidget);
	const FWidgetControllerParams WidgetControllerParams(PC, PS);
	UOverlayWidgetController* OverlayWidgetController = GetOverlayWidgetController(WidgetControllerParams);
	OverlayWidget->SetWidgetController(OverlayWidgetController);
	OverlayWidgetController->BroadcastInitialValues();
	UserWidget->AddToViewport();
}

UOverlayWidgetController* AAAHUD::GetOverlayWidgetController(const FWidgetControllerParams& WidgetControllerParams)
{
	if (m_OverlayWidgetController == nullptr)
	{
		m_OverlayWidgetController = NewObject<UOverlayWidgetController>(this,OverlayWidgetControllerClass);
		m_OverlayWidgetController->SetWidgetControllerParams(WidgetControllerParams);
		m_OverlayWidgetController->BindCallBacks();
		return m_OverlayWidgetController;
	}
	return nullptr;
}
