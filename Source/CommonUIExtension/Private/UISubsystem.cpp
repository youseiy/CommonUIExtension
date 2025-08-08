// All rights reserved to Sphere Project


#include "UISubsystem.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "UIConfirmScreenInfo.h"
#include "UIFunctionLibrary.h"
#include "UIGameplayTags.h"
#include "UITypes.h"
#include "Widget_ActivatableBase.h"
#include "Widget_ConfirmScreen.h"
#include "Widget_PrimaryLayout.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

UUISubsystem* UUISubsystem::Get(const UObject* WorldContextObject)
{
	if (GEngine)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::Assert);
		
		return UGameInstance::GetSubsystem<UUISubsystem>(World->GetGameInstance());
	}
	return nullptr;
}





bool UUISubsystem::ShouldCreateSubsystem(UObject* Outer) const
{	
	if (!CastChecked<UGameInstance>(Outer)->IsDedicatedServerInstance())
	{	
		TArray<UClass*> FoundClasses;


		GetDerivedClasses(GetClass(),FoundClasses);
		
		return FoundClasses.IsEmpty();
	}
	return false;
}
void UUISubsystem::RegisterCreatedPrimaryLayoutWidget(UWidget_PrimaryLayout* InCreatedWidget)
{	
	check(InCreatedWidget);
	
	CreatedPrimaryLayout = InCreatedWidget;
}

void UUISubsystem::PushSoftWidgetToStackAsync(const FGameplayTag& InWidgetStackTag,
	TSoftClassPtr<UWidget_ActivatableBase> InSoftWidgetClass,
	TFunction<void(EAsyncPushWidgetState, UWidget_ActivatableBase*)> AsyncPushStateCallback) const
{
	check(!InSoftWidgetClass.IsNull());
	
	UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
		InSoftWidgetClass.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[InSoftWidgetClass,this,InWidgetStackTag,AsyncPushStateCallback]()
			{
				UClass* LoadedWidgetClass = InSoftWidgetClass.Get();
				
				check(LoadedWidgetClass && CreatedPrimaryLayout);
				
				UCommonActivatableWidgetContainerBase* FoundWidgetStack = CreatedPrimaryLayout->FindWidgetStackByTag(InWidgetStackTag);
				
				UWidget_ActivatableBase* CreatedWidget = FoundWidgetStack->AddWidget<UWidget_ActivatableBase>(
					LoadedWidgetClass,
					[AsyncPushStateCallback](UWidget_ActivatableBase& CreatedWidgetInstance)
					{
						AsyncPushStateCallback(EAsyncPushWidgetState::OnCreatedBeforePush,&CreatedWidgetInstance);
					}
				);
				AsyncPushStateCallback(EAsyncPushWidgetState::AfterPush,CreatedWidget);
			}
		)
	);
}

void UUISubsystem::PushConfirmScreenToModalStackAynsc(EConfirmScreenType InScreenType, const FText& InScreenTitle,
	const FText& InScreenMsg, TFunction<void(EConfirmScreenButtonType)> ButtonClickedCallback)
{
	FConfirmScreenInfo CreatedInfoObject;
	switch (InScreenType)
	{
	case EConfirmScreenType::Ok:
		CreatedInfoObject = FConfirmScreenInfo::CreateOKScreen(InScreenTitle,InScreenMsg);
		break;
	case EConfirmScreenType::YesNo:
		
		CreatedInfoObject = FConfirmScreenInfo::CreateYesNoScreen(InScreenTitle,InScreenMsg);
		break;
	case EConfirmScreenType::OKCancel:
		
		CreatedInfoObject = FConfirmScreenInfo::CreateOkCancelScreen(InScreenTitle,InScreenMsg);
		break;
	case EConfirmScreenType::Unknown:
		break;
	default:
		break;
	}


	PushSoftWidgetToStackAsync(
		UI::UI_WidgetStack_Modal,
		UUIFunctionLibrary::GetSoftWidgetClassByTag(	UI::UI_Widget_ConfirmScreen),
		[CreatedInfoObject,ButtonClickedCallback](EAsyncPushWidgetState InPushState, UWidget_ActivatableBase* PushedWidget)
		{
			if (InPushState == EAsyncPushWidgetState::OnCreatedBeforePush)
			{
				UWidget_ConfirmScreen* CreatedConfirmScreen = CastChecked<UWidget_ConfirmScreen>(PushedWidget);
				CreatedConfirmScreen->InitConfirmScreen(CreatedInfoObject,ButtonClickedCallback);
			}
		}
	);
}
