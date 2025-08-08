// All rights reserved to Sphere Project

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UISubsystem.generated.h"

enum class EConfirmScreenButtonType : uint8;
enum class EConfirmScreenType : uint8;
class UWidget_ActivatableBase;
class UWidget_PrimaryLayout;

enum class EAsyncPushWidgetState : uint8
{
	OnCreatedBeforePush,
	AfterPush
};
/**
 * 
 */
UCLASS()
class  UUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	static UUISubsystem* Get(const UObject* WorldContextObject);
	


	//~ Begin USubsyem Interface
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	//~ End USubsyem Interface
	
	UFUNCTION(BlueprintCallable)
	
	void RegisterCreatedPrimaryLayoutWidget(UWidget_PrimaryLayout* InCreatedWidget);

	void PushSoftWidgetToStackAsync(const FGameplayTag& InWidgetStackTag,TSoftClassPtr<UWidget_ActivatableBase> InSoftWidgetClass,TFunction<void(EAsyncPushWidgetState,UWidget_ActivatableBase*)> AsyncPushStateCallback) const;

	void PushConfirmScreenToModalStackAynsc(EConfirmScreenType InScreenType,const FText& InScreenTitle,const FText& InScreenMsg,TFunction<void(EConfirmScreenButtonType)> ButtonClickedCallback);
	
	//Updates button description
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonDescriptionTextUpdatedDelegate,UUICommonButtonBase*,BroadcastingButton,FText,DescriptionText);
	UPROPERTY(BlueprintAssignable)
	FOnButtonDescriptionTextUpdatedDelegate OnButtonDescriptionTextUpdated;

	
private:
	UPROPERTY(Transient)
	TObjectPtr<UWidget_PrimaryLayout> CreatedPrimaryLayout;
};


