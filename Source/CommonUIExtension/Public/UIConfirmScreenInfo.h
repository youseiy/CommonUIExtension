// All rights reserved to Sphere Project

#pragma once

#include "CoreMinimal.h"
#include "UITypes.h"
#include "UIConfirmScreenInfo.generated.h"

USTRUCT()
struct FConfirmScreenInfo
{
	GENERATED_BODY()

	static FConfirmScreenInfo CreateOKScreen(const FText& InScreenTitle,const FText& InScreenMsg);
	static FConfirmScreenInfo CreateYesNoScreen(const FText& InScreenTitle,const FText& InScreenMsg);
	static FConfirmScreenInfo CreateOkCancelScreen(const FText& InScreenTitle,const FText& InScreenMsg);
	
	UPROPERTY(Transient)
	FText ScreenTitle;
	
	UPROPERTY(Transient)
	FText ScreenMessage;

	UPROPERTY(Transient)
	TArray<FConfirmScreenButtonInfo> AvailableScreenButtons;
};