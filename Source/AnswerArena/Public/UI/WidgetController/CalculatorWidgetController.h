
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

protected:
	UFUNCTION(BlueprintCallable, Category = "Calculator")
	void BroadcastCalculatorData() const;
};
