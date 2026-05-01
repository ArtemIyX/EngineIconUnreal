// Copyright Epic Games, Inc. All Rights Reserved.

#include "EngineIconSetter.h"

#include "Interfaces/IPluginManager.h"
#include "Styling/AppStyle.h"
#include "Styling/SlateStyle.h"

#define LOCTEXT_NAMESPACE "FEngineIconSetterModule"

DEFINE_LOG_CATEGORY(LogEngineIconSetter);

void FEngineIconSetterModule::StartupModule()
{
	if (FSlateStyleSet* styleSet = const_cast<FSlateStyleSet*>(static_cast<const FSlateStyleSet*>(&FAppStyle::Get())))
	{
		if (const TSharedPtr<IPlugin> plugin = IPluginManager::Get().FindPlugin(TEXT("EngineIconSetter")))
		{
			const FString iconPath = plugin->GetBaseDir() / TEXT("Resources/Icon.svg");
			styleSet->Set("AppIcon", new FSlateVectorImageBrush(iconPath, FVector2D(48.0f, 48.0f)));
		}
		else
		{
			UE_LOG(LogEngineIconSetter, Error, TEXT("EngineIconSetter plugin was not found"));
		}
	}
	else
	{
		UE_LOG(LogEngineIconSetter, Error, TEXT("StyleSet is null"));
	}
}

void FEngineIconSetterModule::ShutdownModule() {}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FEngineIconSetterModule, EngineIconSetter)
