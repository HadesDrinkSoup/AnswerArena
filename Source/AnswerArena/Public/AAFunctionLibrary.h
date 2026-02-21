// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AAFunctionLibrary.generated.h"

class UCalculator;
class UCalculatorWidgetController;
class UOverlayWidgetController;

UCLASS()
class ANSWERARENA_API UAAFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "WidgetController")
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintPure, Category = "WidgetController")
	static UCalculatorWidgetController* GetCalculatorWidgetController(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintPure, Category = "Calculator")
	static UCalculator* GetCalculator(const UObject* WorldContextObject);
};
