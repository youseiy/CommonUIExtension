// All rights reserved to Sphere Project

#pragma once

#include "CoreMinimal.h"
#include "Widget_ActivatableBase.h"
#include "Widget_ConfirmScreen.generated.h"

enum class EConfirmScreenButtonType : uint8;
struct FConfirmScreenInfo;
class UDynamicEntryBox;
class UCommonTextBlock;
/**
 * 
 */
UCLASS()
class  UWidget_ConfirmScreen : public UWidget_ActivatableBase
{
	GENERATED_BODY()

public:
	//Gets called outside of the class when this widget is contructed and before it's pushed to the modal stack
	void InitConfirmScreen(FConfirmScreenInfo InScreenInfoObject,TFunction<void(EConfirmScreenButtonType)> ClickedButtonCallback);
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> CommonTextBlock_Title;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> CommonTextBlock_Message;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UDynamicEntryBox> DynamicEntryBox_Buttons;
};
