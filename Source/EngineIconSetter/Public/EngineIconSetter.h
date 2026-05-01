// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"
#include "Styling/SlateBrush.h"

DECLARE_LOG_CATEGORY_EXTERN(LogEngineIconSetter, Log, All);

class FEngineIconSetterModule : public IModuleInterface
{
public:
#pragma region ModuleOverrides
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
#pragma endregion
};
