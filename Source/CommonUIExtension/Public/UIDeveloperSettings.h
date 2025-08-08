// All rights reserved to Sphere Project

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DeveloperSettings.h"
#include "UIDeveloperSettings.generated.h"

class UWidget_ActivatableBase;
/**
 * 
 */

UCLASS(Config=Game,DefaultConfig,meta=(DisplayName="UI Settings"))
class  UUIDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UPROPERTY(Config,EditAnywhere,Category="Game Widgets",meta=(ForceInlineRow,Categories="UI.Widget"))
	TMap<FGameplayTag,TSoftClassPtr<UWidget_ActivatableBase>> WidgetClassMap;
};
