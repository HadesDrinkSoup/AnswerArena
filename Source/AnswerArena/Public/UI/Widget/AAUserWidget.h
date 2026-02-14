
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AAUserWidget.generated.h"

UCLASS()
class ANSWERARENA_API UAAUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> MyWidgetController;
	
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* WidgetController);

protected:
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerController> PlayerController;
    
	// 玩家状态引用 - 包含玩家特定的游戏数据
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerState> PlayerState;
	
	UFUNCTION(BlueprintImplementableEvent, Category="Widget")
	void WidgetControllerSet();
};
