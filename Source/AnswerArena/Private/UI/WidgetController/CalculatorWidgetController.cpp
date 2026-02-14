// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/CalculatorWidgetController.h"

#include "Character/AACharacter.h"


void UCalculatorWidgetController::OnGenerateEquationClicked()
{
	if (!Calculator)
	{
		GetCalculatorFromCharacter();
		if (!Calculator) return;
	}
	Calculator->GenerateEquation();
	BroadcastLatestCalculatorData();
}

void UCalculatorWidgetController::GetCalculatorFromCharacter()
{
	if (!PlayerController) return;

	AAACharacter* AACharacter = Cast<AAACharacter>(PlayerController->GetCharacter());
	check(AACharacter);
	Calculator = AACharacter->GetCalculator();
	check(Calculator);
}

void UCalculatorWidgetController::BroadcastLatestCalculatorData() const
{
	if (!Calculator) return;
	const FCalculatorData& LatestData = Calculator->GetCalculatorData();
	OnCalculatorChanged.Broadcast(LatestData);
}
