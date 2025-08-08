// All rights reserved to Sphere Project


#include "Widget_PrimaryLayout.h"

UCommonActivatableWidgetContainerBase* UWidget_PrimaryLayout::FindWidgetStackByTag(const FGameplayTag& InTag) const
{
	checkf(RegisteredWidgetStack.Contains(InTag),TEXT("Can not find the widget stack by the tag %s"),*InTag.ToString());
	
	return RegisteredWidgetStack.FindRef(InTag);
}

void UWidget_PrimaryLayout::RegisterWidgetStack(FGameplayTag InStackTag, UCommonActivatableWidgetContainerBase* InStack)
{
	if (IsDesignTime())
	{
		return;
	}

	if (!RegisteredWidgetStack.Contains(InStackTag))
	{
		RegisteredWidgetStack.Add(InStackTag,InStack);
	}
}
