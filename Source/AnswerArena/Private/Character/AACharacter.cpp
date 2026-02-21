// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AACharacter.h"

#include "Calculator/Calculator.h"
#include "Player/AAPlayerState.h"
#include "Player/AAPlayerController.h"
#include "UI/HUD/AAHUD.h"
#include "UI/WidgetController/CalculatorWidgetController.h"

AAACharacter::AAACharacter()
{
}

void AAACharacter::BeginPlay()
{
	Super::BeginPlay();
	InitCharacterInfo();
}

UCalculator* AAACharacter::GetCalculator()
{
	if (!Calculator)
	{
		CreateCalculatorInstance();
	}
	return Calculator;
}

void AAACharacter::CreateCalculatorInstance()
{
	if (CalculatorClass)
	{
		Calculator = NewObject<UCalculator>(this, CalculatorClass);
		UE_LOG(LogTemp, Display, TEXT("Calculator has been spawned"));
	}
	else
	{
		Calculator = NewObject<UCalculator>(this);
		UE_LOG(LogTemp, Warning, TEXT("CalculatorClass is not set in %s, using default UCalculator"), *GetName());
	}
}

void AAACharacter::InitCharacterInfo()
{
	AAAPlayerState* AAPlayerState = GetPlayerState<AAAPlayerState>();
	check(AAPlayerState)
	if (AAAPlayerController* AAPlayerController = Cast<AAAPlayerController>(GetController()))
	{
		if (AAAHUD* AAHUD = Cast<AAAHUD>(AAPlayerController->GetHUD()))
		{
			AAHUD->InitOverlay(AAPlayerController, AAPlayerState);
		}
	}
	CreateCalculatorInstance();
}
