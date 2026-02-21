// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/CalculatorWidgetController.h"

#include "AAFunctionLibrary.h"
#include "Character/AACharacter.h"

void UCalculatorWidgetController::BroadcastCalculatorData() const
{
	const UCalculator* Calculator = UAAFunctionLibrary::GetCalculator(this);
	if (!Calculator) return;
	const FCalculatorData& CalculatorData = Calculator->GetCalculatorData();
	OnCalculatorChanged.Broadcast(CalculatorData);
}