// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/AAUserWidget.h"

void UAAUserWidget::SetWidgetController(UObject* WidgetController)
{
	MyWidgetController = WidgetController;
	WidgetControllerSet();
}
