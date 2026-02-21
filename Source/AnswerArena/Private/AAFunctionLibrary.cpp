// Fill out your copyright notice in the Description page of Project Settings.


#include "AAFunctionLibrary.h"

#include "Character/AACharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AAPlayerState.h"
#include "UI/HUD/AAHUD.h"
#include "UI/WidgetController/AAWidgetController.h"

UOverlayWidgetController* UAAFunctionLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AAAHUD* AAHUD = Cast<AAAHUD>(PC->GetHUD()))
		{
			AAAPlayerState* PS = PC->GetPlayerState<AAAPlayerState>();
			const FWidgetControllerParams WidgetControllerParams (PC, PS);
			return AAHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

UCalculatorWidgetController* UAAFunctionLibrary::GetCalculatorWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AAAHUD* AAHUD = Cast<AAAHUD>(PC->GetHUD()))
		{
			AAAPlayerState* PS = PC->GetPlayerState<AAAPlayerState>();
			const FWidgetControllerParams WidgetControllerParams (PC, PS);
			return AAHUD->GetCalculatorWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

UCalculator* UAAFunctionLibrary::GetCalculator(const UObject* WorldContextObject)
{
	if (const APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AAACharacter* ACharacter = Cast<AAACharacter>(PC->GetCharacter()))
		{
			return ACharacter->GetCalculator();
		}
	}
	return nullptr;
}
