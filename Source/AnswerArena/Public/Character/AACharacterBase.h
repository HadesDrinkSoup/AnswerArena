#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AACharacterBase.generated.h"

class UAbilitySystemComponent;

UCLASS(Abstract)
class ANSWERARENA_API AAACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AAACharacterBase();

protected:
	virtual void BeginPlay() override;
	
};
