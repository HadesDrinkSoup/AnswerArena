// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/CalculatorWidgetController.h"

#include "Character/AACharacter.h"


void UCalculatorWidgetController::OnGenerateEquationClicked()
{
	if (!Calculator)
	{
		Calculator = GetCalculatorFromCharacter();
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

UCalculator* UCalculatorWidgetController::GetCalculatorFromCharacter() const
{
	check(PlayerController);
	APawn* Pawn = PlayerController->GetCharacter();
	AAACharacter* AACharacter = Cast<AAACharacter>(Pawn);
	check(AACharacter);
	UCalculator* FoundCalculator = AACharacter->GetCalculator();
	check(FoundCalculator);
	return FoundCalculator;
}

void UCalculatorWidgetController::BroadcastCalculatorData() const
{
	if (!Calculator) return;
	const FCalculatorData& CalculatorData = Calculator->GetCalculatorData();
	OnCalculatorChanged.Broadcast(CalculatorData);
}