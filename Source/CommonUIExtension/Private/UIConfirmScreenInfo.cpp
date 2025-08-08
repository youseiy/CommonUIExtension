// All rights reserved to Sphere Project


#include "UIConfirmScreenInfo.h"

FConfirmScreenInfo FConfirmScreenInfo::CreateOKScreen(const FText& InScreenTitle, const FText& InScreenMsg)
{
	//todo: create constructor 
	FConfirmScreenInfo InfoObject;
	InfoObject.ScreenTitle = InScreenTitle;
	InfoObject.ScreenMessage = InScreenMsg;
	FConfirmScreenButtonInfo OKButtonInfo;
	
	OKButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Closed;
	OKButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("Ok"));
	InfoObject.AvailableScreenButtons.Add(OKButtonInfo);

	
	return InfoObject;
}

FConfirmScreenInfo FConfirmScreenInfo::CreateYesNoScreen(const FText& InScreenTitle, const FText& InScreenMsg)
{
	FConfirmScreenInfo InfoObject;
	InfoObject.ScreenTitle = InScreenTitle;
	InfoObject.ScreenMessage = InScreenMsg;
	FConfirmScreenButtonInfo YesButtonInfo;
	
	YesButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Confirmed;
	YesButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("Yes"));
	FConfirmScreenButtonInfo NoButtonInfo;
	NoButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Cancelled;
	NoButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("No"));
	InfoObject.AvailableScreenButtons.Add(YesButtonInfo);
	InfoObject.AvailableScreenButtons.Add(NoButtonInfo);
	
	return InfoObject;
}

FConfirmScreenInfo FConfirmScreenInfo::CreateOkCancelScreen(const FText& InScreenTitle, const FText& InScreenMsg)
{
	FConfirmScreenInfo InfoObject;
	InfoObject.ScreenTitle = InScreenTitle;
	InfoObject.ScreenMessage = InScreenMsg;
	

	FConfirmScreenButtonInfo OkButtonInfo;
	OkButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Confirmed;
	OkButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("Ok"));

	FConfirmScreenButtonInfo CancelButtonInfo;
	CancelButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Cancelled;
	CancelButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("Cancel"));
	
	InfoObject.AvailableScreenButtons.Add(OkButtonInfo);
	InfoObject.AvailableScreenButtons.Add(CancelButtonInfo);
	
	return InfoObject;
}
