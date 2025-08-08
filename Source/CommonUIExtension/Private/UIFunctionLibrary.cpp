// All rights reserved to Sphere Project


#include "UIFunctionLibrary.h"

#include "UIDeveloperSettings.h"

TSoftClassPtr<UWidget_ActivatableBase> UUIFunctionLibrary::GetSoftWidgetClassByTag(FGameplayTag InWidgetTag)
{

	const UUIDeveloperSettings* FrontendDeveloperSettings = GetDefault<UUIDeveloperSettings>();
	
	checkf(FrontendDeveloperSettings->WidgetClassMap.Contains(InWidgetTag),TEXT("Could not find the corresponding widget under the tag %s"),*InWidgetTag.ToString());
	
	return FrontendDeveloperSettings->WidgetClassMap.FindRef(InWidgetTag);
}
