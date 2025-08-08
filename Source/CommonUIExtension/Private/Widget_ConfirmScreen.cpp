// All rights reserved to Sphere Project


#include "Widget_ConfirmScreen.h"
#include "CommonTextBlock.h"
#include "ICommonInputModule.h"
#include "Components/DynamicEntryBox.h"
#include "UICommonButtonBase.h"
#include "UIConfirmScreenInfo.h"
#include "UITypes.h"

void UWidget_ConfirmScreen::InitConfirmScreen(FConfirmScreenInfo InScreenInfoObject,
                                              TFunction<void(EConfirmScreenButtonType)> ClickedButtonCallback)
{
	check(CommonTextBlock_Title && CommonTextBlock_Message && DynamicEntryBox_Buttons);
	
	CommonTextBlock_Title->SetText(InScreenInfoObject.ScreenTitle);

	CommonTextBlock_Message->SetText(InScreenInfoObject.ScreenMessage);
	
	//Checking if the entry box has old button created previously
	if (DynamicEntryBox_Buttons->GetNumEntries() != 0)
	{	
		/*
		*	Clearing the old buttons the entry box has. The widget type for the entry box
		*	is specifled in the child widget blueprint.
		*/

		DynamicEntryBox_Buttons->Reset<UUICommonButtonBase>(


			[](const UUICommonButtonBase& ExistingButton)
			{
				ExistingButton.OnClicked().Clear();
			}
		);
	}
	
	check(!InScreenInfoObject.AvailableScreenButtons.IsEmpty());
	
	for (const FConfirmScreenButtonInfo& AvailableButtonInfo : InScreenInfoObject.AvailableScreenButtons)
	{	
		FDataTableRowHandle InputActionRowHandle;
		switch (AvailableButtonInfo.ConfirmScreenButtonType)
		{
			case EConfirmScreenButtonType::Confirmed:
			
			InputActionRowHandle = ICommonInputModule::GetSettings().GetDefaultClickAction();
			break;

		case EConfirmScreenButtonType::Cancelled:
			
			InputActionRowHandle = ICommonInputModule::GetSettings().GetDefaultBackAction();
			break;

		case EConfirmScreenButtonType::Closed:
			
			InputActionRowHandle = ICommonInputModule::GetSettings().GetDefaultBackAction();
			break;
			
		default:
			break;
		}

		UUICommonButtonBase* AddedButton = DynamicEntryBox_Buttons->CreateEntry<UUICommonButtonBase>();

		AddedButton->SetButtonText(AvailableButtonInfo.ButtonTextToDisplay);
		AddedButton->SetTriggeredInputAction(InputActionRowHandle);
		AddedButton->OnClicked().AddLambda(
			[ClickedButtonCallback,AvailableButtonInfo,this]()
			{
				ClickedButtonCallback(AvailableButtonInfo.ConfirmScreenButtonType);
				DeactivateWidget();
			}
		);
	}

	if (DynamicEntryBox_Buttons->GetNumEntries() != 0)
	{	
		/*
		*	Set focus on the last button. So if there are two buttons, one is yes, one is no.
		*	Our gamepad will focus on the No button
		*/
		DynamicEntryBox_Buttons->GetAllEntries().Last()->SetFocus();
	}
}
