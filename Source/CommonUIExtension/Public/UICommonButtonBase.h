// All rights reserved to Sphere Project

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "UICommonButtonBase.generated.h"

class UCommonTextBlock;
/**
 * 
 */
UCLASS()
class  UUICommonButtonBase : public UCommonButtonBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetButtonText(FText InText);

private:
	//~Begin UUserWidget Interface
	virtual void NativePreConstruct() override;
	//~End UUserWidget Interface

	//~Begin UCommonButtonBase
	virtual void NativeOnCurrentTextStyleChanged() override;
	virtual void NativeOnHovered() override;
	virtual void NativeOnUnhovered() override;
	//~End UCommonButtonBase

	
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UCommonTextBlock> CommonTextBlock_ButtonText;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI Button", meta = (AllowPrivateAccess = "true"))
	FText ButtonDisplayText;
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI Button", meta = (AllowPrivateAccess = "true"))
	bool bUserUpperCaseForButtonText = false;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI Button", meta = (AllowPrivateAccess = "true"))
	FText ButtonDescriptionText;
	
};
