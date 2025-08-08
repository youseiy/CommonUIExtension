// All rights reserved to Sphere Project

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UIFunctionLibrary.generated.h"

class UWidget_ActivatableBase;
/**
 * 
 */
UCLASS()
class  UUIFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintPure, Category = "UI Function Library")
	 static  TSoftClassPtr<UWidget_ActivatableBase> GetSoftWidgetClassByTag( UPARAM(meta = (Categories = "UI.Widget")) FGameplayTag InWidgetTag);
	
};
