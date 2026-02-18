
#pragma once

#include "CoreMinimal.h"
#include "Calculator/Calculator.h"
#include "UI/WidgetController/AAWidgetController.h"
#include "CalculatorWidgetController.generated.h"

struct FCalculatorData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCalculatorChangedDelegate, const FCalculatorData&, CalculatorData);

UCLASS()
class ANSWERARENA_API UCalculatorWidgetController : public UAAWidgetController
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable, Category = "Calculator")
	FOnCalculatorChangedDelegate OnCalculatorChanged;
	
	UFUNCTION(BlueprintCallable, Category = "Calculator")
	void OnGenerateEquationClicked();
	
	UFUNCTION(BlueprintCallable, Category = "Calculator")
	FString GetEquationDisplayString() const;
	
	UFUNCTION(BlueprintCallable, Category = "Calculator")
	FString GetAnswerDisplayString() const;
	
	UFUNCTION(BlueprintCallable, Category = "Calculator")
	void BroadcastCalculatorData() const;

private:
	UPROPERTY()
	TObjectPtr<UCalculator> Calculator;
	
	UFUNCTION(BlueprintCallable, Category = "Calculator")
	UCalculator* GetCalculatorFromCharacter() const;
};
