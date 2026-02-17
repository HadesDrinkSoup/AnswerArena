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
	
}

FString UCalculatorWidgetController::GetEquationDisplayString() const
{
	if (!Calculator) return TEXT("");
	return Calculator->GetCurrentEquation();
}

FString UCalculatorWidgetController::GetAnswerDisplayString() const
{
	if (!Calculator) return TEXT("");
	return Calculator->GetCurrentAnswerString();
}

void UCalculatorWidgetController::GetCalculatorFromCharacter()
{
	if (!PlayerController) return;

	AAACharacter* AACharacter = Cast<AAACharacter>(PlayerController->GetCharacter());
	check(AACharacter);
	Calculator = AACharacter->GetCalculator();
	check(Calculator);
}

void UCalculatorWidgetController::BroadcastCalculatorData() const
{
	if (!Calculator) return;
	const FCalculatorData& CalculatorData = Calculator->GetCalculatorData();
	OnCalculatorChanged.Broadcast(CalculatorData);
}