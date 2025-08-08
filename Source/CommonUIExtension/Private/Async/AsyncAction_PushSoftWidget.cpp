// All rights reserved to Sphere Project


#include "Async/AsyncAction_PushSoftWidget.h"
#include "Components/Widget.h"
#include "UISubsystem.h"
#include "Widget_ActivatableBase.h"

UAsyncAction_PushSoftWidget* UAsyncAction_PushSoftWidget::PushSoftWidget(const UObject* WorldContextObject,
                                                                         APlayerController* OwningPlayerController, TSoftClassPtr<UWidget_ActivatableBase> InSoftWidgetClass,
                                                                         FGameplayTag InWidgetStackTag, bool bFocusOnNewlyPushedWidget)
{
	checkf(!InSoftWidgetClass.IsNull(),TEXT("PushSoftWidgetToStack was passed a null soft widget class "));


	if (GEngine)
	{
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::LogAndReturnNull))
		{
			UAsyncAction_PushSoftWidget* Node = NewObject<UAsyncAction_PushSoftWidget>();
			Node->RegisterWithGameInstance(World);
			Node->CachedOwningWorld = World;
			Node->CachedOwningPC = OwningPlayerController;
			Node->CachedSoftWidgetClass = InSoftWidgetClass;
			Node->CachedWidgetStackTag = InWidgetStackTag;
			Node->bCachedFocusOnNewlyPushedWidget = bFocusOnNewlyPushedWidget;
			return Node;
		}
	}
	return nullptr;
}

void UAsyncAction_PushSoftWidget::Activate()
{
	Super::Activate();
	UUISubsystem* FrontendUISubsystem = UUISubsystem::Get(CachedOwningWorld.Get());
	
	FrontendUISubsystem->PushSoftWidgetToStackAsync(CachedWidgetStackTag,CachedSoftWidgetClass,
		[this](EAsyncPushWidgetState InPushState, UWidget_ActivatableBase* PushedWidget)
		{
			switch (InPushState)
			{
			case EAsyncPushWidgetState::OnCreatedBeforePush:
				{
					PushedWidget->SetOwningPlayer(CachedOwningPC.Get());

					OnWidgetCreatedBeforePush.Broadcast(PushedWidget);
				}
				break;
			case EAsyncPushWidgetState::AfterPush:
				{
					AfterPush.Broadcast(PushedWidget);
				
					if (bCachedFocusOnNewlyPushedWidget)
					{
						if (UWidget* WidgetToFocus = PushedWidget->GetDesiredFocusTarget())
						{
							WidgetToFocus->SetFocus();
						}
					}
					SetReadyToDestroy();
				}
				break;
			default:
				break;
			}
		}
	);
}
