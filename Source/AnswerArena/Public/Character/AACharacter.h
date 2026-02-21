// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AACharacterBase.h"
#include "AACharacter.generated.h"

class UCalculatorWidgetController;
class UCalculator;

UCLASS()
class ANSWERARENA_API AAACharacter : public AAACharacterBase
{
	GENERATED_BODY()
public:
	AAACharacter();
	
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintPure, Category = "Calculator")//纯函数
	UCalculator* GetCalculator();
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Calculator")
	TSubclassOf<UCalculator> CalculatorClass;
	
	UPROPERTY(BlueprintReadOnly, Category = "Calculator")
	TObjectPtr<UCalculator> Calculator;

private:
	void CreateCalculatorInstance();
	void InitCharacterInfo();
};
