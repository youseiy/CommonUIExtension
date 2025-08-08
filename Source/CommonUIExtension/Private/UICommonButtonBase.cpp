// All rights reserved to Sphere Project


#include "UICommonButtonBase.h"

#include "CommonTextBlock.h"
#include "UISubsystem.h"

void UUICommonButtonBase::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetButtonText(ButtonDisplayText);
}

void UUICommonButtonBase::NativeOnCurrentTextStyleChanged()
{
	Super::NativeOnCurrentTextStyleChanged();

	if (CommonTextBlock_ButtonText && GetCurrentTextStyleClass())
	{
		CommonTextBlock_ButtonText->SetStyle(GetCurrentTextStyleClass());
	}
	
}

void UUICommonButtonBase::NativeOnHovered()
{
	Super::NativeOnHovered();

	if (!ButtonDescriptionText.IsEmpty())
	{
		if (UUISubsystem::Get(this))
		{
			UUISubsystem::Get(this)->OnButtonDescriptionTextUpdated.Broadcast(this,ButtonDescriptionText);
		}
	}
}

void UUICommonButtonBase::NativeOnUnhovered()
{
	Super::NativeOnUnhovered();

	if (UUISubsystem::Get(this))
	{
		UUISubsystem::Get(this)->OnButtonDescriptionTextUpdated.Broadcast(this,FText::GetEmpty());
	}
}

void UUICommonButtonBase::SetButtonText(FText InText)
{
	if (CommonTextBlock_ButtonText && !InText.IsEmpty())
	{
		CommonTextBlock_ButtonText->SetText(bUserUpperCaseForButtonText? InText.ToUpper() : InText);
	}
}
