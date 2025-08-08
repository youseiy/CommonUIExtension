// All rights reserved to Sphere Project

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "GameplayTagContainer.h"
#include "Widget_PrimaryLayout.generated.h"

class UCommonActivatableWidgetContainerBase;
/**
 * 
 */
UCLASS()
class  UWidget_PrimaryLayout : public UCommonUserWidget
{
	GENERATED_BODY()
public:
	UCommonActivatableWidgetContainerBase* FindWidgetStackByTag(const FGameplayTag& InTag) const;
protected:
	
	UFUNCTION(BlueprintCallable)
	void RegisterWidgetStack(UPARAM(meta = (Categories = "UI.WidgetStack")) FGameplayTag InStackTag, UCommonActivatableWidgetContainerBase* InStack);
private:
	UPROPERTY(Transient)
	TMap<FGameplayTag,TObjectPtr<UCommonActivatableWidgetContainerBase>> RegisteredWidgetStack;
	
};
